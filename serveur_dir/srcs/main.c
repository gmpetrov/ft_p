/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:20:57 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 19:16:24 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<fcntl.h>
#include<sys/stat.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

void	free_tab(char ***tab)
{
	int		i;

	i = 0;
	while ((*tab)[++i])
	{
		free((*tab)[i]);
		i++;
	}
	free(*tab);
}

void	ls(int cs, char *buf)
{
	char			**tab;
	DIR				*dir;
	struct dirent	*sd;
	
	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "ls") == 0)
	{
		send(cs, "\033[32mSUCCESS\033[0m\n", 20, MSG_OOB);
		dir = opendir(".");
		while ((sd = readdir(dir)) != NULL)
		{
			send(cs, sd->d_name, ft_strlen(sd->d_name) + 1, MSG_OOB);
			send(cs, "\n", 2, MSG_OOB);
		}
		closedir(dir);
	}
	else	
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
	free_tab(&tab);
}

void	cd_folder(int cs, char *folder)
{
	char	*path;
	t_pwd	*struct_pwd;

	struct_pwd = pwd_init();
	path = (char *)malloc(sizeof(ft_strlen(struct_pwd->pwd) + ft_strlen(folder) + 1));
	path = ft_strcpy(path, struct_pwd->pwd);
	path = ft_strcat(path, "/");
	path = ft_strcat(path, folder);	
	if (chdir(path))		
		send(cs, "\033[32mSUCCESS\033[0m\n", 20, MSG_OOB);
	else		
		send(cs, "\033[31mERROR\033[0m\n", 18, MSG_OOB);
	write(1, "test\n", 5);
}

void	cd(int cs, char *buf)
{
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "cd") != 0)
	{	
		send(cs, "\033[31mERROR\033[0m\n", 18, MSG_OOB);
		free_tab(&tab);
		return ;
	}
	if (tab[1] && ft_strcmp(tab[1], "..") != 0)
		cd_folder(cs, tab[1]);
//	send(cs, "SUCCESS", 7, MSG_OOB);
	free_tab(&tab);
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

char	*get_pwd(char **env)
{
	int		i;
	char	*pwd;
	int		j;
	int		k;

	i = 0;
	j = 4;
	k = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD", 3) == 0)
		{
			pwd = (char *)malloc(sizeof(env[i]));
			while (env[i][j] != 0)
			{
				pwd[k] = env[i][j];
				k++;
				j++;
			}
			pwd[k] = 0;
			return (pwd);
		}
		i++;
	}
	return (NULL);
}

void	pwd(int cs, char *buf, char **env)
{
	char	**tab;
	char	buffer[1024];
	char	*boo;

	(void)env;
	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "pwd") != 0)
	{	
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		free_tab(&tab);
		return ;
	}
	send(cs, "\033[32mSUCCESS\033[0m\n", 20, MSG_OOB);
	boo = getcwd(buffer, 1024);
	send(cs, boo, ft_strlen(boo) + 1, MSG_OOB);
	send(cs, "\n", 2, MSG_OOB);
	free_tab(&tab);
}

void	quit(int cs, char *buf)
{
	(void)buf;
	send(cs, "SUCCESS\n", 8, MSG_OOB);
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
	else if (ft_strncmp(data->buf, "quit", 4) == 0)
		quit(data->cs, data->buf);
	else
		send(data->cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
	send(data->cs, END, 4, 0);
	close(data->cs);
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
