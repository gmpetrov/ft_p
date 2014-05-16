/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:46:33 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 22:42:10 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	cd_folder(int cs, char *limit, char *path)
{
	char	*pwd;
	char	buf[1024];

	if (chdir(path) != 0)
	{
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		return ;
	}
	pwd = getcwd(buf, 1023);
	if (ft_strncmp(limit, pwd, ft_strlen(limit)) == 0)
		send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	else
	{
		chdir(limit);
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
	}
}
void	cd(int cs, char *buf, char *limit)
{
	char	**tab;

	tab = ft_strsplit(buf, ' ');
	if (ft_strcmp(tab[0], "cd") != 0)
	{	
		send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);
		free_tab(&tab);
		return ;
	}
	else if (ft_strcmp(tab[0], "cd") == 0  && !tab[1])
	{
		chdir(limit);
		send(cs, "\033[32mSUCCESS\033[0m\n", 19, MSG_OOB);
	}
	else if (ft_strcmp(tab[0], "cd") == 0 && tab[1])
		cd_folder(cs, limit, tab[1]);
	
//	if (tab)
//		free_tab(&tab);

}


