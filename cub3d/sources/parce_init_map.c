/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_init_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:41:04 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:04:42 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	void						init_plane(t_data *data, int dir)
{
	if (dir == 90)
	{
		data->helpers->dir_x = 0;
		data->helpers->dir_y = -1;
		data->helpers->plane_x = -0.66;
		data->helpers->plane_y = 0;
	}
	else if (dir == 180)
	{
		data->helpers->dir_x = -1;
		data->helpers->dir_y = 0;
		data->helpers->plane_x = 0.0;
		data->helpers->plane_y = 0.66;
	}
	else if (dir == 270)
	{
		data->helpers->dir_x = 0;
		data->helpers->dir_y = 1;
		data->helpers->plane_x = 0.66;
		data->helpers->plane_y = 0.0;
	}
}

static int							init_map_elem(int dir,
									int i, int j, t_data *data)
{
	if (data->pos_y == 0 && data->pos_x == 0)
	{
		data->pos_y = (i + 1) * 64 - 32;
		data->pos_x = (j + 1) * 64 - 32;
		data->helpers->direction = dir;
		data->map[j][i] = '0';
		if (dir == 0)
		{
			data->helpers->dir_x = 1;
			data->helpers->dir_y = 0;
			data->helpers->plane_x = 0.0;
			data->helpers->plane_y = -0.66;
		}
		else
			init_plane(data, dir);
		return (0);
	}
	else
		return (-6);
}

static	int							pos_player(t_data *data,
									int i, int j)
{
	if (data->line[i] == 'S')
	{
		if ((data->exit = init_map_elem(0, i, j, data)))
			return (data->exit);
	}
	else if (data->line[i] == 'W')
	{
		if ((data->exit = init_map_elem(90, i, j, data)))
			return (data->exit);
	}
	else if (data->line[i] == 'N')
	{
		if ((data->exit = init_map_elem(180, i, j, data)))
			return (data->exit);
	}
	else
	{
		if ((data->exit = init_map_elem(270, i, j, data)))
			return (data->exit);
	}
	return (0);
}

static	void						init_line_elem(char c,
									int *i, int j, t_data *data)
{
	if (c == '1')
		data->map[j][*i] = '1';
	else if (c == '0')
		data->map[j][*i] = '0';
	else if (c == '2')
	{
		create_sprite(data, *i, j);
		data->map[j][*i] = '2';
	}
	else
		data->map[j][*i] = ' ';
	*i += 1;
}

int									init_line(char **map, t_data *data, int j)
{
	int	i;

	i = 0;
	if (data->line && !ft_strlen(data->line))
		return (-11);
	if (!(map[j] = malloc(sizeof(char) * ft_strlen(data->line + 1))))
		return (-10);
	while (i < (int)ft_strlen(data->line))
	{
		if (data->line[i] == '1' || data->line[i] == '2' ||
			data->line[i] == '0' || data->line[i] == ' ')
			init_line_elem(data->line[i], &i, j, data);
		else if (data->line[i] == 'S' || data->line[i] == 'W'
				|| data->line[i] == 'N' || data->line[i] == 'E')
		{
			if ((data->exit = pos_player(data, i++, j)) < 0)
				return (data->exit);
		}
		else
			return (-11);
	}
	map[j][i] = 0;
	free(data->line);
	return (0);
}
