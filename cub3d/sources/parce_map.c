/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:31:40 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/15 21:38:39 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

void				init_map_elem(char s, int dir, int i, int j, t_data *data, char **map)
{
				data->pos_y = (i + 1) * 64 - 32;
				data->pos_x = (j + 1) * 64 - 32;
				data->direction = dir;
				map[j][i] = s;
}

int					args_len(char **arg, int n)
{
	int		i;

	i = 0;
	while (arg[i])
		i++;
	if (i > n)
		return -1;
	return (0);
}

int					init_resolution(t_data *data, char **arg)
{
	int		width;
	int		heigth;

	if (args_len(arg, 3) < 0)
		return -1;
	width = ft_atoi(arg[1]);
	heigth = ft_atoi(arg[2]);
	if (!width || !heigth)
		return (-1);
	if (width > 2600)
		width = 2600;	
	if (heigth > 1420)
		heigth = 1420;
	if (width < 200)
		width = 1280;
	if (heigth < 200)
		heigth = 720;
	data->width = width;
	data->heigth = heigth;
	return (0);
}
t_wall				*init_texture(char **arg, t_data *data)
{
	t_wall	*wall;

	printf("arg[1] = %s\n", arg[1]);
	if (args_len(arg, 2) < 0)
		return (0);
	if (!(wall = malloc(sizeof(t_wall))))
		return (0);
	wall->img = mlx_xpm_file_to_image(data->mlx_ptr, arg[1], &(wall->width_img), &(wall->heigth_img));
	if (!wall->img)
		return (0);
	wall->ptr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel,
						&wall->line_length, &wall->endian);
	return (wall);
}

int				init_param(t_data *data, int fd)
{
	int		i;
	char	*line;
	char	**arg;

	i = -1;
	while (++i < 8)
	{
		get_next_line(fd, &line);
		if (ft_strlen(line) > 0)
		{
			printf("line = %s\n", line);
			arg = ft_split(line, ' ');
			if (!ft_strncmp(arg[0], "R", ft_strlen(arg[0])))
			{
				if (init_resolution(data, arg) < 0)
					return -1;				
			}
			else if (!ft_strncmp(arg[0], "NO", ft_strlen(arg[0])))
			{
				if (data->texture->wallN)
					return (-1);
				else
					data->texture->wallN = init_texture(arg, data);
			}
			else if (!ft_strncmp(arg[0], "SO", ft_strlen(arg[0])))
			{
				if (data->texture->wallS)
					return (-1);
				else
					data->texture->wallS = init_texture(arg, data);
			}
			else if (!ft_strncmp(arg[0], "WE", ft_strlen(arg[0])))
			{
				if (data->texture->wallW)
					return (-1);
				else
					data->texture->wallW = init_texture(arg, data);
			}
			else if (!ft_strncmp(arg[0], "EA", ft_strlen(arg[0])))
			{
				if (data->texture->wallE)
					return (-1);
				else
					data->texture->wallE = init_texture(arg, data);
			}
			else if (!ft_strncmp(arg[0], "S", ft_strlen(arg[0])))
			{
				if (data->texture->sprite)
					return (-1);
				else
					data->texture->sprite = init_texture(arg, data);
			}
			else if (!ft_strncmp(arg[0], "F", ft_strlen(arg[0])))
			{
				// if (init_resolution(data, arg) < 0)
					// return -1;
			}
			else if (!ft_strncmp(arg[0], "C", ft_strlen(arg[0])))
			{
				// if (init_resolution(data, arg) < 0)
					// return -1;
			}
			else
				return (-1);
		}
		else
			i--;
		// if (arg)
			// ft_split_free(arg);
		free(line);
	}
	return (0);
}

int				init_map(t_data *data)
{
	char	*line;
	int		fd;
	char	**map;
	int		i;
	int 	j;

	j = 0;
	if (!(map = malloc(sizeof(char*) * 100)))
		return (0);
	fd = open("map.cub", O_RDONLY);
	init_param(data, fd);
	while (get_next_line(fd, &line))
	{
		i = -1;
		map[j] = malloc(sizeof(char) * ft_strlen(line + 1));
		while (++i < (int)ft_strlen(line))
		{
			if (line[i] == '1')
				map[j][i] = '1';
			else if (line[i] == '0')
				map[j][i] = '0';
			else if (line[i] == 'S')
				init_map_elem('0', 0, i, j, data, map);
			else if (line[i] == 'W')
				init_map_elem('0', 90, i, j, data, map);
			else if (line[i] == 'N')
				init_map_elem('0', 180, i, j, data, map);
			else if (line[i] == 'E')
				init_map_elem('0', 270, i, j, data, map);
			else if (line[i] == '2')
				map[j][i] = '2';
			else if (line[i] == ' ')
				map[j][i] = ' ';
		}
		map[j][i] = 0;
		printf("line = %s\n", map[j]);
		free(line);
		j++;
	}
	i = -1;
	map[j] = malloc(sizeof(char) * ft_strlen(line + 1));
	while (++i < (int)ft_strlen(line))
	{
		if (line[i] == '1')
			map[j][i] = '1';
		else if (line[i] == '0')
			map[j][i] = '0';
	}
	map[j][i] = 0;
	printf("line = %s\n", map[j]);
	close(fd);
	free(line);
	data->map = map;
	return (1);
}
