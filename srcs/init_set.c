/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_set.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:21:35 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/19 12:44:20 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void init_params()
{
  params.flag_v = 0;
  params.flag_h = 0;
  params.address = NULL;
  params.ipv4 = NULL;
  params.rdns = NULL;
  params.sock = 0;
  params.target = NULL;
  ft_bzero(&params.packet, sizeof(params.packet));
  ft_bzero(&params.msg, sizeof(params.msg));
  params.received = 0;
  ft_bzero(&params.start, sizeof(params.start));
  ft_bzero(&params.end, sizeof(params.end));
  params.error_cnt = 0;
}

void init_hints(struct addrinfo *hints)
{
  hints->ai_flags = 0;
  hints->ai_family = 0;
  hints->ai_socktype = 0;
  hints->ai_protocol = 0;
  hints->ai_addrlen = 0;
  hints->ai_addr = NULL;
  hints->ai_canonname = NULL;
  hints->ai_next = NULL;
}

t_packet set_packet()
{
  t_packet packet;
  ft_bzero(&packet, sizeof(packet));
  packet.hdr.type = ICMP_ECHO;
  packet.hdr.un.echo.id = getpid();

  int i = 0;
  while (i < (int)(sizeof(packet.msg) - 1))
  {
    packet.msg[i] = '@';
    i++;
  }
  packet.msg[i] = '\0';
  packet.hdr.un.echo.sequence = 0;
  packet.hdr.checksum = 0;
  packet.hdr.checksum = checksum(&packet, sizeof(packet));
  return (packet);
}

void set_params()
{
  t_packet packet;
  SOCKET sock;
  char buffer[80];
  struct msghdr msg;
  struct iovec iov[1];

  if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
    print_error("socket error");

  ft_bzero(&msg, sizeof(msg));
  ft_bzero(iov, sizeof(iov));
  iov[0].iov_base = buffer;
  iov[0].iov_len = sizeof(buffer);
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  ft_bzero(&packet, sizeof(packet));
  packet = set_packet();
  params.msg = msg;
  params.sock = sock;
  params.packet = packet;
  params.rdns = reverse_dns_lookup();

  send_ping();

  while (1)
  {
  }
}
