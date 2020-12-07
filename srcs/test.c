#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

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

int main(int argc, char **argv)
{
  struct addrinfo hints;
  struct addrinfo *res;
  struct addrinfo *p;
  char adress[] = "google.fr";
  
  init_hints(&hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  int status;

  if ((status = getaddrinfo(adress, NULL, &hints, &res)) != 0)
  {
    fprintf(stderr, "ping: %s: %s\n", adress, ft_gai_strerror(status));
    ft_freeaddrinfo(&res);
    exit;
  }

  p = res;
  void *addr;
  char ipver;
  char ipstr[INET6_ADDRSTRLEN];
  while (p != NULL)
  {

    // Identification de l'adresse courante
    if (p->ai_family == AF_INET)
    { // IPv4
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
      addr = &(ipv4->sin_addr);
      ipver = '4';
    }
    else
    { // IPv6
      struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
      addr = &(ipv6->sin6_addr);
      ipver = '6';
    }

    // Conversion de l'adresse IP en une chaîne de caractères
    inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
    printf(" IPv%c: %s\n", ipver, ipstr);

    // Adresse suivante
    p = p->ai_next;
  }
  ft_freeaddrinfo(&res);
  return (0);
}