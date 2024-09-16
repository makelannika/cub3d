/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:48:37 by amakela           #+#    #+#             */
/*   Updated: 2024/09/12 18:05:42 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// void	rotate_point(int *x, int *y, double angle)
// {
// 	double	radians = angle * M_PI / 180.0;
// 	int		cx = PLAYER_X;
// 	int		cy = PLAYER_Y;
// 	int		new_x = (int)((*x - cx) * cos(radians) - (*y - cy) * sin(radians) + cx);
// 	int		new_y = (int)((*x - cx) * sin(radians) + (*y - cy) * cos(radians) + cy);

// 	*x = new_x;
// 	*y = new_y;
// }

void	rotate_right(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	draw_wall(data);
	data->p_angle -= 15;
	if (data->p_angle < 0)
		data->p_angle = 360;
	draw_player(data, data->p_angle);
}

void	rotate_left(t_minimap *data)
{
	mlx_delete_image(data->mlx, data->background_png);
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	draw_wall(data);
	data->p_angle += 15;
	if (data->p_angle > 360)
		data->p_angle = 0;
	draw_player(data, data->p_angle);
}

void	my_keyhook(mlx_key_data_t keydata, void *game_data)
{
	t_minimap	*data;

	data = (t_minimap *)game_data;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down(data);
}
