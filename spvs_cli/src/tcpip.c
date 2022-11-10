#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

/* 12 byte header to calculate tcp header checksum */
struct pseudo_header {
	uint32_t source_addr;
	uint32_t dest_addr;
	uint8_t placeholder;
	uint8_t protocol;
	uint16_t tcp_length;
};

unsigned short Checksum (unsigned short * ptr, int num_bytes) {
	register long sum;
	unsigned short oddbyte;
	register short answer;

	sum = 0;
	while (num_bytes > 1) {
		sum += *ptr++;
		num_bytes -= 2;
	}

	if (num_bytes == 1) {
		oddbyte = 0;
		*((u_char*)&oddbyte) = *(u_char*)ptr;
		sum += oddbyte;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum = sum + (sum >> 16);
	answer = (short)~sum;

	return(answer);
}

/* Creates raw socket, needs to be chaged to usable function */
int main() {
	int s = socket (PF_INET, SOCK_RAW, IPPROTO_TCP);
	
	if (s < 0) {
		perror("socket");
		exit(1);
	}

	char datagram[4096];
	char source_ip[32];
	char * data;
	char * pseudogram;

	memset(datagram, 0, 4096);

	struct iphdr * ip_header = (struct iphdr *)datagram;
	
	struct tcphdr * tcp_header = (struct tcphdr *)(datagram + sizeof(struct ip));
	struct sockaddr_in sin;
	struct pseudo_header psh;

	data = datagram + sizeof(struct iphdr) + sizeof(struct tcphdr);
	strcpy(data, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");

	strcpy(source_ip, "127.0.0.1");
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80);
	sin.sin_addr.s_addr = inet_addr("1.2.3.4");

	ip_header->ihl = 5;
	ip_header->version = 4;
	ip_header->tos = 0;
	ip_header->tot_len = sizeof(struct iphdr) + sizeof(struct tcphdr) + strlen(data);
	ip_header->id = htonl(54321);
	ip_header->frag_off = 0;
	ip_header->ttl = 255;
	ip_header->protocol = IPPROTO_TCP;
	ip_header->check = 0;
	ip_header->saddr = inet_addr(source_ip);
	ip_header->daddr = sin.sin_addr.s_addr;
	ip_header->check = Checksum((unsigned short *)datagram, ip_header->tot_len);

	tcp_header->source = htons(1234);
	tcp_header->dest = htons(80);
	tcp_header->seq = 0;
	tcp_header->ack_seq = 0;
	tcp_header->doff = 5;
	tcp_header->fin = 0;
	tcp_header->syn = 1;
	tcp_header->rst = 0;
	tcp_header->psh = 0;
	tcp_header->ack = 0;
	tcp_header->urg = 0;
	tcp_header->window = htons(5840);
	tcp_header->check = 0;
	tcp_header->urg_ptr = 0;

	psh.source_addr = inet_addr(source_ip);
	psh.dest_addr = sin.sin_addr.s_addr;
	psh.placeholder = 0;
	psh.protocol = IPPROTO_TCP;
	psh.tcp_length = htons(sizeof(struct tcphdr) + strlen(data));

	int psize = sizeof(struct pseudo_header) + sizeof(struct tcphdr) + strlen(data);
	pseudogram = malloc(psize);

	memcpy(pseudogram, (char *) &psh, sizeof(struct pseudo_header));
	memcpy(pseudogram + sizeof(struct pseudo_header), tcp_header, sizeof(struct tcphdr) + strlen(data));

	tcp_header->check = Checksum((unsigned short *)pseudogram, psize);

	int one = 1;
	const int *val = &one;

	if (setsockopt (s, IPPROTO_IP, IP_HDRINCL, val, sizeof(one)) < 0) {
		perror("Error setting IP_HDRINCL");
		exit(1);
	}

	/* Send Packet */
	if (sendto(s, datagram, ip_header->tot_len, 0, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("Sento failed");
		exit(1);
	} else {
		printf("Packet Send. Length: %d\n", ip_header->tot_len);
	}

	return 0;
}

