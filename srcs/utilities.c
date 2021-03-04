/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:12:47 by adstuder          #+#    #+#             */
/*   Updated: 2021/03/04 11:10:38 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

unsigned short checksum(void *data, int len)
{
  unsigned short checksum;
  long sum = 0;
  unsigned short *buf = data;
  while (len > 1)
  {
    sum += *buf++;
    len -= 2;
  }
  if (len > 0)
    sum += *(unsigned char *)buf;
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
    if (params.flag_v == 1)
      return ("EAI_BADFLAGS : Bad value for ai_flags");
    else
      return ("Bad value for ai_flags");
  else if (status == -2)
    if (params.flag_v == 1)
      return ("EAI_NONAME : Name or service not known");
    else
      return ("Name or service not known");
  else if (status == -3)
    if (params.flag_v == 1)
      return ("EAI_AGAIN : Temporary failure in name resolution");
    else
      return ("Temporary failure in name resolution");
  else if (status == -4)
    if (params.flag_v == 1)
      return ("EAI_FAIL : Non-recoverable failure in name resolution");
    else
      return ("Non-recoverable failure in name resolution");
  else if (status == -5)
    if (params.flag_v == 1)
      return ("EAI_NODATA : No address associated with hostname");
    else
      return ("No address associated with hostname");
  else if (status == -6)
    if (params.flag_v == 1)
      return ("EAI_FAMILY : ai_family not supported");
    else
      return ("ai_family not supported");
  else if (status == -7)
    if (params.flag_v == 1)
      return ("EAI_SOCKTYPE : ai_socktype not supported");
    else
      return ("ai_socktype not supported");
  else if (status == -8)
    if (params.flag_v == 1)
      return ("EAI_SERVICE : Servname not supported for ai_socktype");
    else
      return ("Servname not supported for ai_socktype");
  else if (status == -9)
    if (params.flag_v == 1)
      return ("EAI_ADDRFAMILY : Address family for hostname not supported");
    else
      return ("Address family for hostname not supported");
  else if (status == -10)
    if (params.flag_v == 1)
      return ("EAI_MEMORY : Memory allocation failure");
    else
      return ("Memory allocation failure");
  else if (status == -11)
    if (params.flag_v == 1)
      return ("EAI_SYSTEM : System error");
    else
      return ("System error");
  else if (status == -100)
    if (params.flag_v == 1)
      return ("EAI_INPROGRESS : Processing request in progress");
    else
      return ("Processing request in progress");
  else if (status == -101)
    if (params.flag_v == 1)
      return ("EAI_CANCELED : Request canceled");
    else
      return ("Request canceled");
  else if (status == -102)
    if (params.flag_v == 1)
      return ("EAI_NOTCANCELED : Request not canceled");
    else
      return ("Request not canceled");
  else if (status == -103)
    if (params.flag_v == 1)
      return ("EAI_ALLDONE : All requests done");
    else
      return ("All requests done");
  else if (status == -104)
    if (params.flag_v == 1)
      return ("EAI_INTR : Interrupted by a signal");
    else
      return ("Interrupted by a signal");
  else if (status == -105)
    if (params.flag_v == 1)
      return ("EAI_IDN_ENCODE : Parameter string not correctly encoded");
    else
      return ("Parameter string not correctly encoded");
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

int ft_strcmp(const char *s1, const char *s2)
{
  unsigned char *str1;
  unsigned char *str2;
  int i;

  str1 = (unsigned char *)s1;
  str2 = (unsigned char *)s2;
  i = 0;
  while ((str1[i] == str2[i]) && (str1[i] != '\0') && (str2[i] != '\0'))
    i++;
  return (str1[i] - str2[i]);
}