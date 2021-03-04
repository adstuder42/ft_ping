/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   networking.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:03:40 by adstuder          #+#    #+#             */
/*   Updated: 2021/03/04 11:25:38 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

char *reverse_dns_lookup()
{
  socklen_t len;
  char buf[NI_MAXHOST];
  char *rdns;
  struct sockaddr_in tmp;

  tmp.sin_family = params.target->sin_family;
  tmp.sin_port = params.target->sin_port;
  tmp.sin_addr.s_addr = params.target->sin_addr.s_addr;
  rdns = NULL;
  len = sizeof(struct sockaddr_in);
  if (getnameinfo((struct sockaddr *)params.target, len, buf,
                  sizeof(buf), NULL, 0, 0))
    return (NULL);
  params.target->sin_family = tmp.sin_family;
  params.target->sin_port = tmp.sin_port;
  params.target->sin_addr.s_addr = tmp.sin_addr.s_addr;
  if (params.isAdressIpv4 == true)
    rdns = ft_strdup(params.ipv4);
  else
    rdns = ft_strdup(buf);
  return (rdns);
}

char *ntop(unsigned int naddr)
{
  char ipstr[INET6_ADDRSTRLEN];
  
  if (inet_ntop(AF_INET, &naddr, ipstr, sizeof(ipstr)) == NULL)
    print_error("inet_ntop error");
  return (ft_strdup(ipstr));
}

void ft_freeaddrinfo(struct addrinfo *res)
{
  struct addrinfo *tmp;

  tmp = res;
  while (tmp)
  {
    res = res->ai_next;
    free(tmp);
    tmp = res;
  }
}

void get_target(char *address)
{
  struct sockaddr_in *target;
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *p;
  int status;

  init_hints(&hints);
  hints.ai_family = AF_INET;
  if ((status = getaddrinfo(address, NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "ping: %s: %s\n", address, ft_gai_strerror(status));
    free_all();
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
        ft_freeaddrinfo(res);
        print_error("inet_ntop error");
      }
      params.target = target;
    }
    p = p->ai_next;
  }
  params.ipv4 = ft_strdup(ipstr);
  if (ft_strcmp(params.ipv4, params.address) == 0)
    params.isAdressIpv4 = true;
  freeaddrinfo(res);
}