/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:51:54 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 20:52:13 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	ls(int cs, char *buf)
{
	char			**tab;
	DIR				*dir;
	struct dirent	*sd;
	
	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "ls") == 0)
	{
		send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
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
