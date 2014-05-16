/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:19:58 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 18:09:02 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
**	MACRO
*/

# define NL		"\666"
# define END	"\007"

# include "libft.h"

/*
**	STRUCT
*/

typedef struct			s_pwd
{
	char				*pwd;
	int					test;
}						t_pwd;

typedef struct			s_data
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;
	int					r;
	char				buf[1024];
}						t_data;

/*
**	PROTOTYPES
*/


void	free_tab(char ***tab);
char	*get_pwd(char **env);
int		create_server(int port);
t_pwd	*pwd_init(void);

#endif
