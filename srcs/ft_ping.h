/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 16:00:39 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/07 16:16:19 by adstuder         ###   ########.fr       */
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

typedef struct s_ping
{
	int flag_v;
	int flag_h;
} t_ping;

typedef struct s_packet 
{ 
    struct icmphdr hdr; 
    char msg[PACKET_SIZE - sizeof(struct icmphdr)];
}	t_packet;

typedef struct s_params
{
    char *ipv4;
    SOCKET sock;
    struct sockaddr_in *target;
    t_packet packet;
    struct msghdr msg;
    int received;
    struct timeval start;
    struct timeval end;
}             t_params;

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