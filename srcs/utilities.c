/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:12:47 by adstuder          #+#    #+#             */
/*   Updated: 2021/01/16 13:05:21 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

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

void print_error(char *str)
{
  fprintf(stderr, "%s\n", str);
  free_all();
  exit(EXIT_FAILURE);
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

void free_all()
{
  if (params.address != NULL)
    free(params.address);
  if (params.ipv4 != NULL)
    free(params.ipv4);
  if (params.rdns != NULL)
    free(params.rdns);
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

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = 0;
	while ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
		i++;
	return (str1[i] - str2[i]);
}