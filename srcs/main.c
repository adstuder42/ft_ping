/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 15:38:16 by adstuder          #+#    #+#             */
/*   Updated: 2020/12/07 18:51:50 by adstuder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


void init(t_ping *flags)
{
    flags->flag_v = 0;
    flags->flag_h = 0;
}

void usage()
{
    printf("usage:\n");
    exit;
}

t_ping get_args(int argc, char **argv, t_ping flags)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = 0;
        if (argv[i][j] == '-')
        {
            j++;
            while (argv[i][j] != '\0')
            {
                if (argv[i][j] == 'v')
                    flags.flag_v = 1;
                else if (argv[i][j] == 'h')
                    flags.flag_h = 1;
                else
                    usage();
                j++;
            }
        }
        i++;
    }
    return (flags);
}

int main(int argc, char **argv)
{
    t_ping flags;
  
    if (argc < 2)
    {
        usage();
        return (0);
    }
    init(&flags);
    flags = get_args(argc, argv, flags);
    
    printf("v = %d\nh = %d\n", flags.flag_v, flags.flag_h);
    return (0);
}