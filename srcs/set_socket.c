/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_socket.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 14:07:23 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/02 14:53:37 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void ft_bzero(void *s, size_t n)
{
    int i;
    char *str;

    i = 0;
    str = (char *)s;
    while (n > 0)
    {
        str[i] = 0;
        i++;
        n--;
    }
}

void fill_packet(t_packet *packet)
{
}

unsigned short checksum(void *data, int len)
{
    /* Compute Internet Checksum for "count" bytes
            *         beginning at location "addr".
            */
    unsigned short checksum;
    long sum = 0;
    unsigned short *buf = data;
    while (len > 1)
    {
        /*  This is the inner loop */
        sum += *buf++;
        len -= 2;
    }
    /*  Add left-over byte, if any */
    if (len > 0)
        sum += *(unsigned char *)buf;
    /*  Fold 32-bit sum to 16 bits */
    while (sum >> 16)
        sum = (sum & 0xffff) + (sum >> 16);
    checksum = ~sum;
    return (checksum);
}


int set_socket(char *ip_p)
{
    unsigned char ip_n[sizeof(struct in6_addr)];
     char str[INET6_ADDRSTRLEN];
    int s;
    if (s = inet_pton(AF_INET, ip_p, ip_n) <= 0)
    {
        if (s == 0)
            fprintf(stderr, "Not in presentation format\n");
        else
            fprintf(stderr, "inet_pton error\n");
        exit;
    }

    struct sockaddr_in sin;
    sin.sin_addr = ip_n;
    sin.sin_family = AF_INET;

    printf("ip === %lu\n", sin.sin_addr.s_addr);
    SOCKET sock;
    if (sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) < 0)
    {
        fprintf(stderr, "socket_error\n");
        exit(EXIT_FAILURE);
    }

   // send_ping(sock, &sin);






//  t_packet packet;
//     struct msghdr *resp;

//     int packet_sequence = 0;
//     while (1)
//     {
//         ft_bzero(&packet, sizeof(packet));
//         packet.hdr.type = ICMP_ECHO;
//         packet.hdr.un.echo.id = getpid();
//         int i = 0;
//         while (packet.msg[i] != '\0')
//         {
//             packet.msg[i] = '@';
//             i++;
//         }
//         packet.hdr.un.echo.sequence = packet_sequence;
//         packet_sequence++;
//         packet.hdr.checksum = checksum(&packet, sizeof(packet));

//         if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr *)&sin, sizeof(sin)) < 0)
//         {
//             fprintf(stderr, "Packet sending error\n");
//             exit(EXIT_FAILURE);
//         }

//         recvmsg(sock, resp, 0);
//         printf("OKOKOKOKOK\n");
//     }
    return (0);
}

int main(int argc, char **argv)
{

    // char *ip_p[] = get_ip();
    char ip_p[] = "185.12.49.10";
    set_socket(ip_p);
}