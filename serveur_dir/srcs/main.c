/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/18 22:46:42 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_putstr("\033[31mERROR\033[0m\n");
		ft_putstr("Bind problem, please try another port\n");
		exit(0);
	}
	listen(sock, 42);
	return (sock);
}

void	put(int cs, char *data)
{
	int		ret;
	char	buf[1024];
	int		r;
	char	**tab;

	tab = ft_strsplit(data, ' ');
	ret = open(tab[1], O_RDWR | O_CREAT | O_EXCL, 07777);
	while ((r = read(cs, buf, 1023)) > 0)
	{
		buf[r] = 0;
		write(ret, buf, r);
	}
	close(ret);
	if (tab)
		free_tab(&tab);
}

void	action(t_data *data, char **env)
{
	while (42)
	{
		data->r = read(data->cs, data->buf, 1023);
		data->buf[data->r] = 0;
		write(1, data->buf, data->r);
		write(1, "\n", 1);
		if (ft_strncmp(data->buf, "ls", 2) == 0)
			ls(data->cs, data->buf);
		else if (ft_strncmp(data->buf, "cd", 2) == 0)
			cd(data->cs, data->buf, data->limit);
		else if (ft_strncmp(data->buf, "pwd", 3) == 0)
			pwd(data->cs, data->buf, env);
		else if (ft_strcmp(data->buf, "quit") == 0)
			quit(data->cs, data->buf);
		else
			error_not_found(data->cs);
		send(data->cs, END, 2, 0);
	}
}

void	do_fork(t_data data, char **env, int sock)
{
	data.cs = accept(sock, (struct sockaddr *)&data.csin, &data.cslen);
	if (fork() == 0)
		action(&data, env);
	else
		do_fork(data, env, sock);
}

int		main(int ac, char **av, char **env)
{
	t_data				data;
	int					port;
	int					sock;
	char				buf[1024];

	if (ac != 2)
	{
		ft_putstr("[USAGE] - ./serveur [port]\n");
		return (0);
	}
	port = ft_atoi(av[1]);
	sock = create_server(port);
	data.limit = getcwd(buf, 1023);
	do_fork(data, env, sock);
	close(data.cs);
	close(sock);
	return (0);
}
