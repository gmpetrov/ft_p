/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:17:46 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/18 22:45:34 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	free_tab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

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

void	dl_file(int sock, char *file, int t)
{
	(void)sock;
	(void)t;
	ft_putstr("attention\n");
	open(file, O_RDWR, O_CREAT, O_EXCL);
}

int		main(int ac, char **av)
{
	int					port;
	int					sock;
	int					r;
	char				buf[1024];

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
		buf[r - 1] = 0;
		write(sock, buf, r);
		quit_client(buf);
		reception(sock);
	}
	close(sock);
	return (0);
}
