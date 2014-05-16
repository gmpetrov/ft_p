/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:46:33 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 21:08:13 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	cd_folder(int cs, char *folder)
{
	if (chdir(folder) == 0)	
		send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	else		
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
}

void	cd(int cs, char *buf)
{
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "cd") != 0)
	{	
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		free_tab(&tab);
		return ;
	}
	if (tab[1] && ft_strcmp(tab[1], "..") != 0)
		cd_folder(cs, tab[1]);
	if (tab)
		free_tab(&tab);
}


