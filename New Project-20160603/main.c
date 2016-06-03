#include <stdio.h>

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;

typedef struct pktBuf_s {
    uint16 size;
    uint8 *frame_info;
    uint8 *pkt_cputag;
	uint8 *pkt_vlantag;
    uint8 *pkt_head;
    uint8 *l2;
    uint8 *l3;
    uint8 *l4;
    uint8 l2fmt;          /* Layer 2 Format */
    uint8 l3fmt;          /* Layer 3 Format */
    uint8 l4fmt;          /* Layer 4 Format */

    uint8  spa;             /* Rx port */

    uint8  tx_chksum_mode;  /* Check sum config for NIC tx function */
    uint8  tx_dport_mode;   /* Tx packet mode. please reference to tx_pkt_mode_t */
    uint32 tx_dst_pmsk;
    uint8  inner_tag_mode;  /* InnerTagMode of TX pkt */
    uint8  outer_tag_mode;  /* InnerTagMode of TX pkt */
    uint32 inner_tag;       /* Inner tag of rx pkt / Inner tag of tx pkt */
    uint32 outer_tag;       /* Outer tag of rx pkt / Outer tag of tx pkt */

    uint8  tx_trunk_support; /* Send pacekt to represent port in trunk or all member port */
} pktBuf_t;

typedef struct eth_addr_s {
    uint8 addr[6];
} eth_addr_t;

typedef struct eth_hdr_s {
    struct eth_addr_s dst_mac;
    struct eth_addr_s src_mac;
    uint16 ether_type;
} eth_hdr_t;

typedef	struct ip_hdr_s {

    uint8  version:4;      /* version */
    uint8  hdr_len:4;      /* header length */

    uint8  tos;            /* type of service */
    uint16 length;         /* total length */

    uint16 id_number;      /* identification */
    uint16 frag_offset;    /* fragment offset field */

    uint8  ttl;            /* time to live */
    uint8  proto;          /* protocol */
    uint16 chksum;         /* checksum */

    uint8  src_ip[4];      /* source IP address */
    uint8  dst_ip[4];      /* destination IP address */
} ip_hdr_t;

typedef	struct icmp_hdr_s {
    uint8  type;       /* Type */
    uint8  cod;
//    uint8  code;       /* reserved keyword in 8051 C language */
    uint16 chksum;     /* Checksum */

    uint16 identifier; /* Id Number */
    uint16 seq_number; /* Sequence */
} icmp_hdr_t;


typedef struct ping_pktbuf_t
{
    eth_hdr_t Eth_hdr;
    ip_hdr_t Ip_hdr;                             
    icmp_hdr_t Icmp_hdr;
    
}ping_pktbuf_t;


int main()
{
    pktBuf_t  Buf_Reply;
    pktBuf_t  *pBuf_Reply = &Buf_Reply;
    
    ping_pktbuf_t  ping_pktbuf;
    ping_pktbuf_t* pPing_pktbuf = &ping_pktbuf;
    
    eth_hdr_t *pEthHdr = pPing_pktbuf;
    *pEthHdr = ping_pktbuf.Eth_hdr;
    
    //ip_hdr_t *pIpHdr = pEthHdr + 14;
    ip_hdr_t *pIpHdr = pEthHdr + 1;
    *pIpHdr = ping_pktbuf.Ip_hdr;
    
    //icmp_hdr_t *pIcmpHdr = pIpHdr + 20;
    icmp_hdr_t *pIcmpHdr = pIpHdr + 1;
    *pIcmpHdr = ping_pktbuf.Icmp_hdr; 
    
    pBuf_Reply->l4 = pIcmpHdr;
    pBuf_Reply->l3 = pBuf_Reply->l4 - sizeof(ip_hdr_t);
    
    
    
    printf("-----addr pBuf_Reply->l4 =%x\n",pBuf_Reply->l4);
    printf("--pBuf_Reply->l3 (L4-20) =%x\n",pBuf_Reply->l3);
    printf("--reply-l3 - base        =%x\n",pBuf_Reply->l4 - pBuf_Reply->l3);
    printf("--piphdr   - base        =%x\n",(ip_hdr_t*)pBuf_Reply->l4 - pIpHdr);
    
    printf("-----addr of ping_pktbuf =%x\n",pPing_pktbuf);
    printf("-----addr of    pIcmpHdr =%x\n",pIcmpHdr);
    printf("-----addr of      pIpHdr =%x\n",pIpHdr);
    printf("-----addr of     pEthHdr =%x\n",pEthHdr);
    
    printf("-----addr of head =%x\n",pPing_pktbuf);
    printf("-----addr of   l4 =%x\n",pIpHdr + 20);
    printf("-----addr of   l3 =%x\n",pEthHdr + 14);
    printf("-----addr of   l2 =%x\n",pEthHdr);
    
    printf("-----sizeof(icmp_pktbuf_t)=%d\n",sizeof(ping_pktbuf_t));
    printf("-----sizeof(eth_hdr_t)=%d\n",sizeof(eth_hdr_t));
    printf("-----sizeof(ip_hdr_t)=%d\n",sizeof(ip_hdr_t));
    pIcmpHdr->type=8;
    
    printf("-----pIcmpHdr->type=%d\n",pIcmpHdr->type=8);
    return 0;
}


