/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ip.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:27:45 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/03 20:07:29 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
#include <errno.h>



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

char *get_ip(char *address)
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
    ft_freeaddrinfo(&res);
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
      printf("sinfamily %d\n", target->sin_family);
      printf("sinport %d\n", target->sin_port);
      printf("sinaddr %d\n", target->sin_addr.s_addr);


      addr = target->sin_addr;
      printf("addr %d\n",addr.s_addr);

      if (inet_ntop(p->ai_family, &addr, ipstr, sizeof(ipstr)) == NULL)
      {
        fprintf(stderr, "inet_ntop error\n");
        exit(EXIT_FAILURE);
      }
      ft_freeaddrinfo(&res);
      return (ft_strdup(ipstr));
    }
    p = p->ai_next;
  }
  ft_freeaddrinfo(&res);
  return (0);
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

int  sendclone(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen)
{
  printf("s == %d\n", s);
  printf("packet.hdr.type == %d\n", s);
  printf("s == %d\n", s);
  printf("s == %d\n", s);
  printf("s == %d\n", s);
  printf("s == %d\n", s);



    exit(EXIT_FAILURE);

}


int set_socket()
{

  SOCKET sock;
 
  if ((sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
  {
    fprintf(stderr, "socket_error\n");
    exit(EXIT_FAILURE);
  }
  printf("socket === %d\n", sock);
  // send_ping(sock, &sin);

  t_packet packet;
  //struct msghdr *resp;

  int sequence = 0;
  while (1)
  {
    ft_bzero(&packet, sizeof(packet));
    packet.hdr.type = ICMP_ECHO;
    packet.hdr.un.echo.id = getpid();
    long unsigned int i = 0;
    while (i < (sizeof(packet.msg) - 1))
    {
      packet.msg[i] = '@';
      i++;
    }
    packet.msg[i] = '\0';
    packet.hdr.un.echo.sequence = sequence;
    sequence++;
    packet.hdr.checksum = checksum(&packet, sizeof(packet));
    

  //  sendto(int s, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen);
   // printf("sendclone == %d\n",sendclone(sock, &packet, sizeof(packet), 0, (struct sockaddr*)target, sizeof(target)));

 
    printf("%d\n", sizeof(packet));
    if (sendto(sock, &packet, sizeof(packet), 0, (struct sockaddr*)&target, sizeof(target)) < 0)
    {
      fprintf(stderr, "Packet sending error\n");
 
     printf("errno == %d\n",errno);
      exit(EXIT_FAILURE);
    }
    printf("OKOKOKOKOK\n");

    //recvmsg(sock, resp, 0);
  }
  return (0);
}

int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  char *ip_p;
  char address[] = "google.fr";
  ip_p = get_ip(address);
  printf("%s\n", ip_p);
  printf("%u\n", inet_addr(ip_p));
  // printf("%u\n", target->sin_addr);
  // printf("%u\n", target->sin_family);
  // printf("%u\n", target->sin_port);
  
  
  
  
  //set_socket(ip_p);
  return (0);
}