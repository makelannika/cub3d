/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:33:08 by amakela           #+#    #+#             */
/*   Updated: 2024/09/27 16:37:06 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_extension(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len > 4)
		return (ft_strncmp(&arg[len - 4], ".cub", 5));
	return (1);
}

void	set_orientation(t_cub3d *data, char orientation, int x, int y)
{
	if (orientation == 'E')
		data->map.p_angle = 0.0;
	else if (orientation == 'N')
		data->map.p_angle = 90.0;
	else if (orientation == 'W')
		data->map.p_angle = 180.0;
	else if (orientation == 'S')
		data->map.p_angle = 270.0;
	data->map.player.x = x;
	data->map.player.y = y;
	data->map.offsetx = 13;
	data->map.offsety = 13;
	data->map.player.pix_x = x * 25 + 13;
	data->map.player.pix_y = y * 25 + 13;
}

int	validate_index(t_cub3d *data, char **grid, int y, int x)
{
	if (ft_strchr("NSWE", grid[y][x]))
	{
		if (data->map.player.pix_x)
			return (err("multiple starting positions found in the map", NULL));
		set_orientation(data, grid[y][x], x, y);
		return (0);
	}
	if (!grid[y][x - 1] || !ft_strchr("01NSWE", grid[y][x - 1])
		|| !grid[y][x + 1] || !ft_strchr("01NSWE", grid[y][x + 1])
		|| !grid[y - 1][x] || !ft_strchr("01NSWE", grid[y - 1][x])
		|| !grid[y + 1][x] || !ft_strchr("01NSWE", grid[y + 1][x]))
		return (err("map must be surrounded by walls", NULL));
	return (0);
}

int	validate_line(char *str)
{
	while (*str)
	{
		if (!ft_strchr(" 10NSWE\n", *str))
			return (1);
		str++;
	}
	return (0);
}
