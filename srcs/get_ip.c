/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:27:45 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/08 18:35:42 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_params params;

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

void init_params()
{
   params.ipv4 = NULL;
    params.sock = 0;
    params.target = NULL;
    ft_bzero(&params.packet,sizeof(params.packet));
    ft_bzero(&params.msg, sizeof(params.msg));
    params.received = 0;
     ft_bzero(&params.start, sizeof(params.start));
     ft_bzero(&params.end, sizeof(params.end));
}

void terminate()
{
  float ratio = 0;
  int sec;
  int usec;
  ratio = ((float)params.received / (float)params.packet.hdr.un.echo.sequence * (float)100) - 100;
  ratio = ratio - 2* ratio;
  gettimeofday(&params.end, NULL);
  sec = params.end.tv_sec - params.start.tv_sec;
  usec = params.end.tv_usec - params.start.tv_usec;
  int precision;
  if (ratio == 0 || ratio == 100)
    precision = 0;
  else if (ratio < 10)
    precision = 5;
  else
    precision = 4;
  int duration = (usec /1000) + (sec * 1000);
  printf("\n--- %s ping statistics ---\n", params.ipv4);
  printf("%d packets transmitted, %d received, %.*f%% packet loss, time %dms\n", params.packet.hdr.un.echo.sequence, params.received, precision, ratio, duration);

  free(params.ipv4);
  exit(EXIT_SUCCESS);
}

void print_error(char *str)
{
  printf("%s\n", str);
  if (params.ipv4)
    free(params.ipv4);
  exit(EXIT_FAILURE);
}

char *ft_strdup(const char *s1)
{
  int i;
  char *cpy;

  i = 0;
  while (s1[i] != '\0')
    i++;
  if (!(cpy = (char *)malloc(sizeof(char) * (i + 1))))
    return (0);
  i = 0;
  while (s1[i] != '\0')
  {
    cpy[i] = s1[i];
    i++;
  }
  cpy[i] = '\0';
  return (cpy);
}

void ft_freeaddrinfo(struct addrinfo **lst)
{
  struct addrinfo *tmp;

  tmp = *lst;
  while (tmp)
  {
    *lst = (*lst)->ai_next;
    free(tmp);
    tmp = *lst;
  }
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

char *ft_gai_strerror(int status)
{
  if (status == -1)
    return ("Bad value for ai_flags");
  else if (status == -2)
    return ("Name or service not known");
  else if (status == -3)
    return ("Temporary failure in name resolution");
  else if (status == -4)
    return ("Non-recoverable failure in name resolution");
  else if (status == -5)
    return ("No address associated with hostname");
  else if (status == -6)
    return ("ai_family not supported");
  else if (status == -7)
    return ("ai_socktype not supported");
  else if (status == -8)
    return ("Servname not supported for ai_socktype");
  else if (status == -9)
    return ("Address family for hostname not supported");
  else if (status == -10)
    return ("Memory allocation failure");
  else if (status == -11)
    return ("System error");
  else
    return ("Unknown error");
}

void get_target(char *address)
{
  struct sockaddr_in *target;
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *p;

  init_hints(&hints);
  hints.ai_family = AF_INET;
  int status;

  if ((status = getaddrinfo(address, NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "ping: %s: %s\n", address, ft_gai_strerror(status));
    exit(EXIT_FAILURE);
  }

  p = res;
  struct in_addr addr;
  char ipstr[INET6_ADDRSTRLEN];
  while (p != NULL)
  {
    if (p->ai_family == AF_INET)
    {
      target = (struct sockaddr_in *)p->ai_addr;

      addr = target->sin_addr;

      if (inet_ntop(p->ai_family, &addr, ipstr, sizeof(ipstr)) == NULL)
      {
      ft_freeaddrinfo(&res);
        print_error("inet_ntop error");
      }
      params.target = target;
      params.ipv4 = ft_strdup(ipstr);
    }
    p = p->ai_next;
  }
  ft_freeaddrinfo(&res);
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

t_packet set_packet()
{
  t_packet packet;
  ft_bzero(&packet, sizeof(packet));
  packet.hdr.type = ICMP_ECHO;
  packet.hdr.un.echo.id = getpid();
  int i = 0;
  while (i < (sizeof(packet.msg) - 1))
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

void send_ping()
{
  struct timeval timeout;
  struct timeval request;
  struct timeval reply;

  timeout.tv_sec = 1;
  timeout.tv_usec = 0;
  request.tv_sec = 0;
  request.tv_usec = 0;
  reply.tv_sec = 0;
  reply.tv_usec = 0;
  long int duration;
struct iphdr *ip;
struct icmphdr *icmp;

  alarm(1);
int ttl = 155; /* max = 255 */ 
  if (setsockopt(params.sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
    print_error("setsockopt setting IP_TTL failed");
  if (setsockopt(params.sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) < 0)
    print_error("setsockopt setting SO_RCVTIMEO failed");
  gettimeofday(&request, NULL);
  // if (setsockopt(params.sock, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
  //                sizeof(timeout)) < 0)
  //  print_error("setsockopt failed");
  params.packet.hdr.un.echo.sequence++;

  params.packet.hdr.checksum = 0;
  params.packet.hdr.checksum = checksum(&(params.packet), sizeof(params.packet));
  if (sendto(params.sock, &(params.packet), sizeof(params.packet), 0, (struct sockaddr *)params.target, sizeof(*params.target)) <= 0)
    printf("ping: sendto: Le réseau n'est pas accessible\n");
  if (recvmsg(params.sock, &params.msg, 0) > 0)
  {
    ip = (struct iphdr *)params.msg.msg_iov[0].iov_base;
  icmp = (struct icmphdr *)(params.msg.msg_iov[0].iov_base + sizeof(struct iphdr));
   
    gettimeofday(&reply, NULL);
    duration = reply.tv_usec - request.tv_usec;
    params.received++;
    printf("64 bytes from %s: icmp_seq=%d ttl=%d time=%ld.%ld ms\n",params.ipv4, icmp->un.echo.sequence, ip->ttl, duration/1000, (duration/10)%100);
  }
}

int set_params()
{
  int sequence = 0;
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

  send_ping();

  while (1)
  {
  }

  return (0);
}

int main(int argc, char **argv)
{

  (void)argc;
  (void)argv;
  float f = 3;
  char address[] = "google.fr";

  signal(SIGALRM, send_ping);
  signal(SIGINT, terminate);
  init_params();

  get_target(address);


  gettimeofday(&params.start, NULL);
  printf("PING %s (%s) 56(84) bytes of data.\n", address, params.ipv4);
  // printf("s_addr == %u\n", target->sin_addr.s_addr);
  // printf("sin_family == %u\n", target->sin_family);
  // printf("sin_port == %u\n", target->sin_port);

  // printf("p.hdr.type == %d\n", packet.hdr.type);
  // printf("p.hdr.code == %d\n", packet.hdr.code);
  // printf("p.hdr.checksum == %d\n", packet.hdr.checksum);
  set_params();

  return (0);
}