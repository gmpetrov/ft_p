/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/18 22:31:48 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/18 22:45:50 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	put(int sock, char *file)
{
	int		ret;
	char	buf[1024];
	int		t;

	ft_putstr(file);
	write(sock, file, ft_strlen(file));
	if ((ret = open(file, O_RDONLY)) < 0)
	{
		ft_putstr("\033[31mERROR\033[0m\n");
		ft_putstr("File does not exist\n");
		close(ret);
		return ;
	}
	while ((t = read(ret, buf, 1023)) > 0)
	{
		buf[t] = 0;
		write(sock, buf, t);
	}
	ft_putstr("\033[32mSUCCESS\033[0m\n");
	close(ret);
}

void	quit_client(char *buf)
{
	if (ft_strcmp(buf, "quit") == 0)
	{
		ft_putstr("\033[32mSUCCESS\033[0m\n");
		exit(0);
	}
}

void	reception(int sock)
{
	int					t;
	char				buf[1024];

	while ((t = recv(sock, buf, sizeof(buf), 0)) > 0)
	{
		buf[t] = 0;
		if (ft_strcmp(buf, END) == 0 || (ft_strcmp(buf, "") == 0))
			return ;
		write(1, buf, t);
	}
}
