/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amakela <amakela@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 18:01:45 by amakela           #+#    #+#             */
/*   Updated: 2024/09/26 16:09:19 by amakela          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static bool	is_equal(double a, double b)
{
	return (fabs(a - b) < 1e-9);
}

void    horizontal_hit(t_map map, t_ray *ray_c, t_cub3d *data)
{
    ray_c->ray_distance = (ray_c->side_dist_y - ray_c->delta_dist_y) * 25;
    if (map.player.y > ray_c->ray_index_y)
    {
    //     printf("north\n");
        ray_c->wall_hit_y = (ray_c->ray_index_y + 1) * 25;
		data->wall_to_draw = data->no_arr;
    }
    else
    {
    //     printf("south\n");
        ray_c->wall_hit_y = ray_c->ray_index_y * 25;
		data->wall_to_draw = data->so_arr;
    }
    ray_c->wall_hit_x = (ray_c->unit_x + (ray_c->side_dist_y - ray_c->delta_dist_y) * ray_c->ray_dir_x) * 25;
}

 void   vertical_hit(t_map map, t_ray *ray_c, t_cub3d *data)
 {
    ray_c->ray_distance = (ray_c->side_dist_x - ray_c->delta_dist_x) * 25;
    if (map.player.x > ray_c->ray_index_x)
    {
    //     printf("west\n");
        ray_c->wall_hit_x = (ray_c->ray_index_x + 1) * 25;
		data->wall_to_draw = data->we_arr;
    }
    else
    {
    //     printf("east\n");
        ray_c->wall_hit_x = ray_c->ray_index_x * 25;
		data->wall_to_draw = data->ea_arr;
    }
    ray_c->wall_hit_y = (ray_c->unit_y + (ray_c->side_dist_x - ray_c->delta_dist_x) * ray_c->ray_dir_y) * 25;
 }
 
void    forward(t_ray *ray_c, char coor)
{
    if (coor == 'x')
    {
        ray_c->side_dist_x += ray_c->delta_dist_x;
        ray_c->ray_index_x += ray_c->step_x;
        ray_c->side = 0;
    }
    else if (coor == 'y')
    {
        ray_c->side_dist_y += ray_c->delta_dist_y;
        ray_c->ray_index_y -= ray_c->step_y;
        ray_c->side = 1;
    }
}

void    step_pos(t_ray *ray_c, char coor)
{
    if (coor == 'x')
    {
        ray_c->step_x = 1;
        ray_c->side_dist_x = (ray_c->ray_index_x + 1.0 - ray_c->unit_x) * ray_c->delta_dist_x;
    }
    else if (coor == 'y')
    {
        ray_c->step_y = 1;
        ray_c->side_dist_y = (ray_c->unit_y - ray_c->ray_index_y) * ray_c->delta_dist_y;
    }
}

void    step_neg(t_ray *ray_c, char coor)
{
    if (coor == 'x')
    {
        ray_c->step_x = -1;
        ray_c->side_dist_x = (ray_c->unit_x - ray_c->ray_index_x) * ray_c->delta_dist_x;
    }
    else if (coor == 'y')
    {
        ray_c->step_y = -1;
        ray_c->side_dist_y = (ray_c->ray_index_y + 1.0 - ray_c->unit_y) * ray_c->delta_dist_y;
    }
}

void    set_side_dist(t_ray *ray_c)
{
	if (is_equal(ray_c->ray_dir_x, 0.0))
		ray_c->side_dist_x = DBL_MAX;
	else if (ray_c->ray_dir_x < 0.0)
        step_neg(ray_c, 'x');
		else
			step_pos(ray_c, 'x');
	if (is_equal(ray_c->ray_dir_y, 0.0))
		ray_c->side_dist_y = DBL_MAX;
    else if (ray_c->ray_dir_y < 0.0)
        step_neg(ray_c, 'y');
    else
        step_pos(ray_c, 'y');
}

void    init_vars(t_map map, t_ray *ray_c)
{
    ray_c->delta_dist_x = fabs(1 / ray_c->ray_dir_x);
    ray_c->delta_dist_y = fabs(1 / ray_c->ray_dir_y);
	ray_c->unit_x = map.player.pix_x / 25;
	ray_c->unit_y = map.player.pix_y / 25;
	ray_c->ray_index_x = map.player.x;
	ray_c->ray_index_y = map.player.y;
    ray_c->hit = 0;
    ray_c->side = 0;
}

void	ray_cast(t_cub3d *data, t_ray *ray_c)
{
    init_vars(data->map, ray_c);
    set_side_dist(ray_c);
    while (!ray_c->hit)
    {
        if (ray_c->side_dist_x < ray_c->side_dist_y)
            forward(ray_c, 'x');
        else
            forward(ray_c, 'y');
        if (data->map.grid[ray_c->ray_index_y][ray_c->ray_index_x] == '1')
            ray_c->hit = 1;
    }
    if (!ray_c->side)
        vertical_hit(data->map, ray_c, data);
    else
	{
		
        horizontal_hit(data->map, ray_c, data);
	}
}

int rgba_to_hex(int r, int g, int b, int a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

// void	draw_pixel(t_cub3d *data, int x, uint8_t *tmp2)
// {
// 	int color = rgba_to_hex(tmp2[0], tmp2[1], tmp2[2], tmp2[3]);
// 	if (data->start < data->end)
// 	{
// 		mlx_put_pixel(data->background, x, data->start, color);
// 		data->start++;
// 	}
// 	printf("## x is %i start is %i\n", x, data->start);
// }

// void	draw_ray(t_cub3d *data, int ray_index)
// {
	// uint8_t 	tmp2[4];
	// uint8_t 	*tmp;
	// int			y;
	// int			x;
	// int			i;
	// int			j;

	// i = 1000/data->wall_height;
	// y = 0;
	// tmp = data->wall_to_draw->pixels;
	// while (y < 1000)
	// {
	// 	x = 0;
	// 	j = y;
	// 	while (x < 4)
	// 		tmp2[x++] = tmp[j++];
	// 	draw_pixel(data, ray_index, tmp2);
	// 	y += i * 4;
	// }
// }


void	get_hex(t_cub3d *data)
{
	data->f = rgba_to_hex(data->floor[0], data->floor[1], data->floor[2], 255);
	data->c = rgba_to_hex(data->ceiling[0], data->ceiling[1], data->ceiling[2], 255);
	int 		i = 0;
	int			y = 0;
	uint8_t		*no = data->no->pixels;
	uint8_t		*so = data->so->pixels;
	uint8_t		*we = data->we->pixels;
	uint8_t		*ea = data->ea->pixels;

	while (y < 4000000)
	{
		data->no_arr[i] = rgba_to_hex(no[y], no[y + 1], no[y + 2], no[y + 3]);
		data->so_arr[i] = rgba_to_hex(so[y], so[y + 1], so[y + 2], so[y + 3]);
		data->we_arr[i] = rgba_to_hex(we[y], we[y + 1], we[y + 2], we[y + 3]);
		data->ea_arr[i] = rgba_to_hex(ea[y], ea[y + 1], ea[y + 2], ea[y + 3]);
		i++;
		y += 4;
	}
}

void	draw_pixel(t_cub3d *data, int x, int incr)
{
	if (data->start < data->end)
	{
	// mlx_delete_image(data->mlx, data->background);
		mlx_put_pixel(data->background, x, data->start, data->wall_to_draw[incr]);
		data->start++;
	}
	
	// printf("## x is %i start is %i\n", x, data->start);
}

void	draw_ray(t_cub3d *data, int x)
{
	int i = 1000/data->wall_height;
	int j = 0;

	// (void)i;
	while (data->start < data->end)
	{
		draw_pixel(data, x, i * (j * 1000 + x));
		j++;
	}
}

void	set_strip_height(t_cub3d *data, float distance)
{
	if (distance < 1)
		distance = 1;
	data->wall_height = (int)(SCREEN_HEIGHT / (distance/25));
	if (data->wall_height > 999)
		data->wall_height = 1000;
	data->start = -data->wall_height / 2 + SCREEN_HEIGHT / 2;
	if (data->start < 0)
		data->start = 0;
	data->end = data->start + data->wall_height;
	if (data->end >= SCREEN_HEIGHT)
		data->end = SCREEN_HEIGHT - 1;
// 	printf("Wall height is %i distance is %f start is %i end is %i\n", data->wall_height, distance, data->start, data->end);
}

void	draw_background(t_cub3d *data)
{
	int	y;
	int x;

	y = 0;
	while (y < 1000)
	{
		x = 0;
		if (y < 500)
		{
			while (x < 1000)
				mlx_put_pixel(data->background, x++, y, data->c);
		}
		else
		{
			while (x < 1000)
				mlx_put_pixel(data->background, x++, y, data->f);
		}
		y++;
	}
}

void render_ray(t_cub3d *data, int distance, int ray_index)
{
	set_strip_height(data, distance);
	draw_ray(data, ray_index);
}

void	fov_cast(t_cub3d *data, t_ray *ray_c, float player_angle)
{
	double	rad;
	float	ray;
	int		x;
	int		y;
	int		i;
	int index = 0;

	ray = 60;
	// int s = 0;

	draw_background(data);
	while (ray > 0)
	{
		// ray_c->current_angle = player_angle - 5 + ray;
		ray_c->current_angle = player_angle + 30 + ray;
		rad = ray_c->current_angle * M_PI / 180.0;
		ray_c->ray_dir_x = cos(rad);
		ray_c->ray_dir_y = sin(rad);
		ray_cast(data, ray_c);
		i = 0;
		while (i < ray_c->ray_distance)
		{
			x = PLAYER_X + (int)(ray_c->ray_dir_x * i);
			y = PLAYER_Y - (int)(ray_c->ray_dir_y * i);
			if (x > 0 && x < 275 && y > 0 && y < 275)
				mlx_put_pixel(data->minimap, x, y, 0xFFFFFF);
			i++;
		}
		// render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance * cos(fabs((ray - 5) * M_PI / 180.0))), SCREEN_WIDTH / 5 * ray);
		// render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance * cos((ray - 30) * M_PI / 180.0)), index);
		// printf("distance is %f\n", ray_c->ray_distance);
		// render_ray(data, ray_c->ray_distance);
		render_ray(data, (int)(ray_c->ray_distance), index);
		// render_ray(data, (int)(SCREEN_HEIGHT / ray_c->ray_distance), index);
		// ray += 1;
		index++;
		ray -= .06;
	}
}
