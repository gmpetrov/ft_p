/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 21:30:27 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/stat.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"

int		create_client(char *addr, int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (!proto)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = inet_addr(addr);
	connect(sock, (const struct sockaddr *)&sin, sizeof(sin));
	return (sock);	
}

int		main(int ac, char **av)
{
	int					port;
	int					sock;
	int					r;
	char				buf[1024];
	int					t;

	if (ac != 3)
	{
		ft_putstr("[USAGE] - ./client [address] [port]\n");
		return (0);
	} 
	port = ft_atoi(av[2]);
	sock = create_client(av[1], port);
	while (42)
	{
		write(1, "\033[33m[client]-> \033[0m", 20);
		r = read(0, buf, 1023);
		buf[r] = 0;
		write(sock, buf, r);
		while ((t = recv(sock, buf, sizeof(buf), 0)) > 0)
		{
			buf[t] = 0;
			if (ft_strcmp(buf, END) == 0 || (ft_strcmp(buf, "") == 0))
				break ;
			if (ft_strcmp(buf, NL) == 0)
			{
				close(sock);
				exit(0);
			}
			write(1, buf, t);
		}
	}
	close(sock);
	return (0);
}
