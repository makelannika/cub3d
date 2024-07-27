/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 13:24:23 by amakela           #+#    #+#             */
/*   Updated: 2024/07/27 21:02:40 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_cub
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor[3];
	int		ceiling[3];
	char	**map;
} t_cub;

		/*********UTILS*********/
int		err(char *str);
char	*strdup_no_newline(const char *s1);
int		check_extension(char *arg);

		/**********MAP**********/
int		check_map_char(t_cub *data);
int		init_map(int fd, t_cub *data, char *line);

		/********VALIDATION******/
int		check_identifier(char *line, t_cub *data);
#endif

