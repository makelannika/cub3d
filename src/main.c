/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:48:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/22 19:19:23 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub3d	data;

	data = (t_cub3d){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("program takes one .cub file as an argument", NULL));
	if (parse_file(&data, argv[1]))
		return (free_data(&data));
	if (init_game(&data))
		return (free_data(&data));
	free_data(&data);
	return (0);
}
