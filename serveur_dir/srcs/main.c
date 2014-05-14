/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/14 20:46:55 by gpetrov          ###   ########.fr       */
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
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
	{
		ft_putstr("[ERROR] - BIND\n");
		exit(0);
	}
	listen(sock, 42);
	return (sock);	
}

void	ls(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	cd(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	get(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	put(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	pwd(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	quit(int cs)
{
	send(cs, "SUCCESS", 7, MSG_OOB);
}

void	action(t_data *data)
{
	data->r = read(data->cs, data->buf, 1023);	
	data->buf[data->r] = 0;
	write(1, data->buf, data->r);
	if (ft_strncmp(data->buf, "ls", 2) == 0)
		ls(data->cs);
	else if (ft_strncmp(data->buf, "cd", 2) == 0)
		cd(data->cs);
	else if (ft_strncmp(data->buf, "get", 3) == 0)
		get(data->cs);
	else if	(ft_strncmp(data->buf, "put", 3) == 0)
		put(data->cs);
	else if (ft_strncmp(data->buf, "pwd", 3) == 0)
		pwd(data->cs);
	else if (ft_strncmp(data->buf, "quit", 4) == 0)
		quit(data->cs);
	else
		send(data->cs, "ERROR", 6, MSG_OOB);
	close(data->cs);
}

int		main(int ac, char **av)
{
	t_data				data;
	int					port;
	int					sock;

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
		data.cs = accept(sock, (struct sockaddr *)&data.csin, &data.cslen);
		if (fork() == 0)
		{
			action(&data);
			return (0);
		}
	}
	close(data.cs);
	close(sock);
	return (0);
}
