/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/17 18:46:38 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/18 22:44:41 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	get_file(int cs, char *file)
{
	int		ret;
	char	buf[1024];
	int		t;

	if ((ret = open(file, O_RDONLY)) < 0)
	{
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		send(cs, "File does not exist\n", 21, MSG_OOB);
		close(ret);
		return ;
	}
	send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	send(cs, GET, 2, 0);
	while ((t = read(ret, buf, 1023)) > 0)
	{
		buf[t] = 0;
		send(cs, buf, t + 1, MSG_OOB);
	}
	send(cs, END_GET, 2, 0);
	close(ret);
}

void	get(int cs, char *buf)
{
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if ((ft_strcmp(tab[0], "get") != 0) ||
			(ft_strcmp(tab[0], "get") == 0 && !tab[1]))
	{
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		send(cs, "File does not exist\n", 21, MSG_OOB);
		free_tab(&tab);
		return ;
	}
	else
		get_file(cs, tab[1]);
	if (tab)
		free_tab(&tab);
}
