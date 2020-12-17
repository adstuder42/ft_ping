/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   networking.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:03:40 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/17 15:05:54 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

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
        ft_freeaddrinfo(res);
        print_error("inet_ntop error");
      }
      params.target = target;
    }
    p = p->ai_next;
  }
  params.ipv4 = ft_strdup(ipstr);

  freeaddrinfo(res);
}