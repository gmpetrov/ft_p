/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/14 17:50:51 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "serveur.h"

int		create_server(int port)
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
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sock, (const struct sockaddr *)&sin, sizeof(sin));
	listen(sock, 42);
	return (sock);	
}

int		main(int ac, char **av)
{
	int					port;
	int					sock;
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;	
	int					r;
	char				buf[1024];

	if (ac != 2)
	{
		ft_putstr("[USAGE] - ./serveur [port]\n");
		return (0);
	}
	port = ft_atoi(av[1]);
	sock = create_server(port);
	mkdir("./MY_SERVER", 07777);
	chdir("./MY_SERVER");
	while (42)
	{
		cs = accept(sock, (struct sockaddr *)&csin, &cslen);
		if (fork() == 0)
		{
			r = read(cs, buf, 1023);	
			buf[r] = 0;
			write(1, buf, r);
			close(cs);
			return (0);
		}
	}
	close(cs);
	close(sock);
	return (0);
}
