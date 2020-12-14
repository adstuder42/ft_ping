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
char *ntop(unsigned int naddr)
{
  char ipstr[INET6_ADDRSTRLEN];

  if (inet_ntop(AF_INET, &naddr, ipstr, sizeof(ipstr)) == NULL)
    printf("inet_ntop error");
  return (ft_strdup(ipstr));
}


int main(int argc, char **argv)
{

  (void)argc;
  (void)argv;
 
  unsigned int saddr = 1138113240l;

printf("%s\n",  ntop(saddr));
  return (0);
}