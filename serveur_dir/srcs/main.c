/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 21:03:52 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

t_pwd	*pwd_init(void)
{
	static t_pwd	*pwd = NULL;

	if (pwd == NULL)
	{
		pwd = (t_pwd *)malloc(sizeof(t_pwd));
		pwd->test = 1;
	}
	return (pwd);
}

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

void	get(int cs, char *buf)
{
	(void)buf;
	send(cs, "SUCCESS\n", 8, MSG_OOB);
}

void	put(int cs, char *buf)
{
	(void)buf;
	send(cs, "SUCCESS\n", 8, MSG_OOB);
}

void	quit(int cs, char *buf)
{
	(void)buf;	
	send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	send(cs, NL, 2, MSG_OOB);
}

void	action(t_data *data, char **env)
{
	data->r = read(data->cs, data->buf, 1023);	
	data->buf[data->r - 1] = 0;
	write(1, data->buf, data->r);
	write(1, "\n", 1);
	if (ft_strncmp(data->buf, "ls", 2) == 0)
		ls(data->cs, data->buf);
	else if (ft_strncmp(data->buf, "cd", 2) == 0)
		cd(data->cs, data->buf);
	else if (ft_strncmp(data->buf, "get", 3) == 0)
		get(data->cs, data->buf);
	else if	(ft_strncmp(data->buf, "put", 3) == 0)
		put(data->cs, data->buf);
	else if (ft_strncmp(data->buf, "pwd", 3) == 0)
		pwd(data->cs, data->buf, env);
	else if (ft_strcmp(data->buf, "quit") == 0)
		quit(data->cs, data->buf);
	else
		send(data->cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
	send(data->cs, END, 2, 0);
//	close(data->cs);
}

int		main(int ac, char **av, char **env)
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
	//chdir("./MY_SERVER");
	while (42)
	{
		data.cs = accept(sock, (struct sockaddr *)&data.csin, &data.cslen);
		if (fork() == 0)
		{
			action(&data, env);
			return (0);
		}
	}
	close(data.cs);
	close(sock);
	return (0);
}
