/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:42:17 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 20:43:29 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

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
	send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	boo = getcwd(buffer, 1024);
	send(cs, boo, ft_strlen(boo) + 1, MSG_OOB);
	send(cs, "\n", 2, MSG_OOB);
	free_tab(&tab);
}