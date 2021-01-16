/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:00:39 by adstuder          #+#    #+#             */
/*   Updated: 2021/01/16 12:17:21 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
 #define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

typedef int SOCKET;
typedef void (*sighandler_t)(int);

#define PACKET_SIZE 64


typedef struct s_packet
{
    struct icmphdr hdr;
    char msg[PACKET_SIZE - sizeof(struct icmphdr)];
} t_packet;

typedef struct s_params
{
    int flag_v;
    int flag_h;
    char *address;
    char *ipv4;
    char *rdns;
    SOCKET sock;
    struct sockaddr_in *target;
    t_packet packet;
    struct msghdr msg;
    int received;
    struct timeval start;
    struct timeval end;
    int error_cnt;

} t_params;

extern t_params params;

void init_params();
char *ft_strdup(const char *s1);
void init_hints(struct addrinfo *hints);
t_packet set_packet();
void set_params();
void usage();
void get_flags(int argc, char **argv);
int main(int argc, char **argv);
void print_line(struct iphdr *ip, struct icmphdr *icmp, float time);
void terminate();
void send_ping();
unsigned short checksum(void *data, int len);
void print_error(char *str);
char *ft_gai_strerror(int status);
void free_all();
char *ft_strdup(const char *s1);
void ft_bzero(void *s, size_t n);
char *reverse_dns_lookup();
char *ntop(unsigned int naddr);
void ft_freeaddrinfo(struct addrinfo *res);
void get_target(char *address);
/*
struct addrinfo {
    int              ai_flags;
    int              ai_family;
    int              ai_socktype;
    int              ai_protocol;
    size_t           ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;
    struct addrinfo *ai_next;
};

struct sockaddr {
    sa_family_t sa_family;
    char        sa_data[14];
}


struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};
*/

// struct icmphdr
// {
//   u_int8_t type;                /* message type */
//   u_int8_t code;                /* type sub-code */
//   u_int16_t checksum;
//   union
//   {
//     struct
//     {
//       u_int16_t        id;
//       u_int16_t        sequence;
//     } echo;                        /* echo datagram */
//     u_int32_t        gateway;        /* gateway address */
//     struct
//     {
//       u_int16_t        __unused;
//       u_int16_t        mtu;
//     } frag;                        /* path mtu discovery */
//   } un;
// };

#endif