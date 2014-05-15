/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:19:58 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/15 15:32:33 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
**	MACRO
*/

# define END	"\007"

# include "libft.h"

/*
**	STRUCT
*/

typedef struct			s_data
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	int					r;
	char				buf[1024];
}						t_data;

#endif
