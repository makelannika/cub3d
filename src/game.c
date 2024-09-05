/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:18:02 by linhnguy          #+#    #+#             */
/*   Updated: 2024/09/05 13:54:17 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int create_images(t_minimap *data)
{
	data->background_tex = mlx_load_png("assets/black_bg.png");
	data->background_png = mlx_texture_to_image(data->mlx, data->background_tex);
	mlx_resize_image(data->background_png, 275, 275);
	mlx_image_to_window(data->mlx, data->background_png, 0, 0);
	// data->arrow_tex = mlx_load_png("assets/player_icon.png");
	// data->arrow_png = mlx_texture_to_image(data->mlx, data->arrow_tex);
	// mlx_resize_image(data->arrow_png, 20, 20);
	// mlx_image_to_window(data->mlx, data->arrow_png, 625, 450);
	return (0);
}

void draw_square(t_minimap *data, float y_coor, float x_coor)
{
	int i;
	int j;

	i = 0;
	while (i < INDEX_HEIGHT)
	{
		j = 0;
		while (j < INDEX_WIDTH)
		{
			mlx_put_pixel(data->background_png, (int)(x_coor + j), (int)(y_coor + i), 0x00FFFF);
			j++;
		}
		i++;
	}
}

int draw_wall(t_minimap *data)
{
	int	i;
	int j;
	int k;

	i = data->player->y - 4;
	j = data->player->x - 4;
	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;
	k = j;
	while (data->map[i])
	{
		j = k;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				draw_square(data, i * INDEX_HEIGHT, j * INDEX_WIDTH);
			j++;
		}
		i++;
	}
	return (0);
}

int draw_player(t_minimap *data)
{
	int i = 0;

	i = 0;
	mlx_put_pixel(data->background_png, (int)PLAYER_X, (int)PLAYER_Y, 0xFFFFFF);
	while (i < 10)
	{
		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y + i), 0xFFFFFF);
		mlx_put_pixel(data->background_png, (int)(PLAYER_X - i), (int)(PLAYER_Y - i), 0xFFFFFF);
		i++;
	}
	return (0);
}
int init_game(t_minimap *data)
{
	data->mlx = mlx_init(1000, 900, "Cub3D", false);
	create_images(data);
	draw_player(data);
	draw_wall(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (0);
}

void do_game(t_cub data2)
{
	t_minimap	data;
	data = (t_minimap){0};
	data.map = data2.map.layout;
	data.map_width = data2.map.width;
	data.map_height = data2.map.height;
	data.player = &data2.map.player;

	for(int i = 0; data.map[i]; i++)
		printf("%s\n", data.map[i]);
	init_game(&data);
}

// void	my_keyhook(mlx_key_data_t keydata, void *game_data)
// {
// 	t_data			*data;

// 	data = (t_data *)game_data;
// 	if (data->is_end == true)
// 		return ;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_RELEASE)
// 		mlx_close_window(data->mlx);
// 	if (keydata.key == MLX_KEY_W && keydata.action == MLX_RELEASE)
// 		move_up(data);
// 	if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
// 		move_left(data);
// 	if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
// 		move_right(data);
// 	if (keydata.key == MLX_KEY_S && keydata.action == MLX_RELEASE)
// 		move_down(data);
// }