/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 15:31:40 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/26 15:19:49 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	int					check_zero(char **map, int j)
{
	int	i;

	i = -1;
	while (map[j][++i])
	{
		if (map[j][i] == '0' || map[j][i] == '2')
		{
			if (map[j][i + 1] == ' ' || map[j][i - 1] == ' '
						|| map[j - 1][i] == ' ' || map[j + 1][i] == ' ')
				return (-1);
		}
	}
	return (0);
}

static	int					longer_line(char **map, int j, int len)
{
	char	*tmp;
	int		i;

	i = -1;
	if ((int)ft_strlen(map[j]) < len)
	{
		if (!(tmp = malloc(sizeof(char) * len + 1)))
			return (-10);
		while (++i < (int)ft_strlen(map[j]))
			tmp[i] = map[j][i];
		while (i < len)
			tmp[i++] = ' ';
		tmp[i] = 0;
		free(map[j]);
		map[j] = tmp;
		return (0);
	}
	return (0);
}

static	int					check_zero_line(char **map, t_data *data)
{
	int	j;
	int	size;
	int	len;

	len = 0;
	size = 0;
	j = -1;
	while (map[++j])
		if ((int)ft_strlen(map[j]) > len)
			len = (int)ft_strlen(map[j]);
	size = -1;
	while (++size < j)
		if ((data->exit = longer_line(map, size, len)) < 0)
			return (data->exit);
	size = 0;
	while (++size < j - 1)
		if (check_zero(map, size) < 0)
			return (-11);
	return (0);
}

static	int					pool_map(char **map, t_data *data)
{
	int	i;
	int	j;

	if ((data->exit = check_zero_line(map, data)) < 0)
		return (data->exit);
	j = -1;
	while (map[++j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == ' ')
				map[j][i] = '1';
			i++;
		}
		map[j][i] = 0;
	}
	return (0);
}

int							init_map(t_data *data)
{
	int		j;

	j = 0;
	data->fd = open(data->map_name, O_RDONLY);
	if (!(data->map = malloc(sizeof(char*) * 100)))
		errror_exit(-10, data);
	ft_bzero(data->map, sizeof(char*) * 100);
	if ((data->exit = init_param(data, data->fd)) < 0)
		errror_exit(data->exit, data);
	if ((data->exit = init_line(data->map, data, j++)) < 0)
		errror_exit(data->exit, data);
	while (get_next_line(data->fd, &data->line))
		if ((data->exit = init_line(data->map, data, j++)) < 0)
			errror_exit(data->exit, data);
	if ((data->exit = init_line(data->map, data, j++)) < 0)
		errror_exit(data->exit, data);
	close(data->fd);
	data->line = 0;
	if (data->pos_y == 0 && data->pos_x == 0)
		errror_exit(-7, data);
	if (pool_map(data->map, data) < 0)
		errror_exit(data->exit, data);
	if (check_map(data->map))
		errror_exit(-11, data);
	return (0);
}
