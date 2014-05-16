/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/16 20:40:32 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 23:06:01 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

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

void	error_not_found(int cs)
{
	send(cs, "\033[31mERROR\033[0m\n", 17, MSG_OOB);	
	send(cs, "Command not found\n", 19, MSG_OOB);
}
