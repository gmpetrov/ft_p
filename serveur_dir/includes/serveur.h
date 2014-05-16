/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:19:58 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/16 20:53:11 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
# define SERVEUR_H

/*
**	MACRO
*/

# define NL		"\006"
# define END	"\007"

#include<fcntl.h>
#include<sys/stat.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
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

/*
**	tools.c
*/
void	free_tab(char ***tab);

/*
**	pwd.c
*/
void	pwd(int cs, char *buf, char **env);
/*
**	cd.c
*/
void	cd_folder(int cs, char *folder);
void	cd(int cs, char *buf);

/*
**	ls.c
*/

void	ls(int cs, char *buf);

int		create_server(int port);
t_pwd	*pwd_init(void);


#endif
