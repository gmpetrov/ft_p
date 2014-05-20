/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpetrov <gpetrov@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/05/13 18:16:38 by gpetrov           #+#    #+#             */
/*   Updated: 2014/05/18 22:35:55 by gpetrov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

/*
**	MACRO
*/

# define END	"\007"
# define NL		"\006"
# define GET	"\005"
# define END_GET "\004"

# include <fcntl.h>
# include <sys/socket.h>
# include <sys/stat.h>
# include <netdb.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include "libft.h"

void	reception(int sock);
void	quit_client(char *buf);
void	put(int sock, char *file);
void	dl_file(int sock, char *file, int t);
void	dl_file(int sock, char *file, int t);
int		create_client(char *addr, int port);
void	free_tab(char ***tab);

#endif
