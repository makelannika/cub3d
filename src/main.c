/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: linhnguy <linhnguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 19:48:24 by linhnguy          #+#    #+#             */
/*   Updated: 2024/07/27 21:33:35 by linhnguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	parse_file(t_cub *data, char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (err("Error: open failed :("));
	line = get_next_line(fd); //check line
	while (line && ft_strncmp(line, " ", 1) && ft_strncmp(line, "1", 1))
	{
		if (ft_strncmp(line, "\n", 1))
		{
			line = get_next_line(fd);
			continue ;
		}
		if (check_identifier(line, data))
			return (err("Error"));
		free(line);
		line = get_next_line(fd);
	}
	if (init_map(fd, data, line))
		return (err("Error"));
	return (0);
}

int	array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return(i);
}

int	check_column(char **map, int col, int row, int direction)
{
	if (direction == 0)
	{
		while (row >= 0)
		{
			if (map[row][col] == '1' || map[row][col] == ' ')
				;
			else
				return (1);
			row--;
		}
	}
	else if (direction == 1)
	{
		while (row >= 0)
		{
			if (map[row][col] == '1' || map[row][col] == ' ')
				;
			else
				return (1);
			row++;
		}
	}
	return (0);
}

int	retrace_vertical(char **map, int col, int row, int direction)
{
	int	end;
	
	end = ft_strlen(map[0]);
	if (col == 0){
		printf("here1\n");	
		return (check_column(map, col + 1, row, direction));
	}
	else if (col == end){
		printf("here2\n");	
		return (check_column(map, col - 1, row, direction));}
	else
	{
		if (check_column(map, col + 1, row, direction)
			|| check_column(map, col - 1, row, direction)){
				
		printf("here3\n");	
		return (1);
			}
	}
	return (0);
}

int	check_levels_down(char **map, int col)
{
	int	row;
	int last_str;
	int	up;

	last_str = array_len(map);
	up = 0;
	row = 1;
	while (map[row])
	{
		if (map[row][col] == '1' && row == 1)
			return (0);
		else if (map[row][col] == ' ')
			;
		else if (map[row][col] == '1')
			return (retrace_vertical(map, col, row, up));
		else if (map[row][col] != '1')
			return (1);
		row++;
	}
	return (0);
}

int	check_top_border(char **map)
{
	int	i;
	
	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '1')
			;
		else if (map[0][i] == ' ')
		{
			if (check_levels_down(map, i))
				return (1);
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	check_map_border(char **map)
{
	printf("%c\n", map[0][0]);
	if (check_top_border(map))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	data;

	data = (t_cub){0};
	if (argc != 2 || check_extension(argv[1]))
		return (err("Error: invalid argument"));
	if (parse_file(&data, argv[1]))
		return (1); //checks what exist and free
	for (int i = 0; data.map[i]; i++)
		ft_printf(2, "%s\n", data.map[i]);
	if (check_map_char(&data) || check_map_border(data.map))
		return (err("\nError map is shit")); // clean
	return (0);
}
