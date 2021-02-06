/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_init_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:38:12 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/17 16:47:51 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	t_wall					*init_texture(char **arg, t_data *data)
{
	t_wall	*wall;

	if (args_len(arg) < 2)
		return (0);
	if (!(wall = malloc(sizeof(t_wall))))
		return (0);
	wall->img = mlx_xpm_file_to_image(data->mlx_ptr, arg[1],
	&(wall->width_img), &(wall->heigth_img));
	if (!wall->img)
		return (0);
	wall->ptr = mlx_get_data_addr(wall->img, &wall->bits_per_pixel,
						&wall->line_length, &wall->endian);
	if (!wall->ptr)
		return (0);
	data->params++;
	return (wall);
}

static	int						init_param_textures_2(t_data *data)
{
	if (!ft_strncmp(data->rays->arg[0], "SO", data->l))
	{
		if (data->texture->wall_s ||
		!(data->texture->wall_s = init_texture(data->rays->arg, data)))
			return (-3);
	}
	else if (!ft_strncmp(data->rays->arg[0], "WE", data->l))
	{
		if (data->texture->wall_w ||
		!(data->texture->wall_w = init_texture(data->rays->arg, data)))
			return (-3);
	}
	else if (data->texture->wall_e ||
	!(data->texture->wall_e = init_texture(data->rays->arg, data)))
		return (-3);
	return (0);
}

static	int						init_param_textures_1(t_data *data)
{
	if (!ft_strncmp(data->rays->arg[0], "NO", data->l))
	{
		if (data->texture->wall_n ||
		!(data->texture->wall_n = init_texture(data->rays->arg, data)))
			return (-3);
	}
	else if (!ft_strncmp(data->rays->arg[0], "S", data->l))
	{
		if (data->texture->sprite ||
		!(data->texture->sprite = init_texture(data->rays->arg, data)))
			return (-3);
	}
	else if ((data->exit = init_param_textures_2(data)) < 0)
		return (data->exit);
	return (0);
}

static	int						init_param_body(t_data *data)
{
	char *tmp;

	if (!(data->rays->arg = ft_split(data->line, ' ')))
		return (-1);
	tmp = data->rays->arg[0];
	data->l = ft_strlen(tmp);
	if (!ft_strncmp(tmp, "R", data->l) ||
	!ft_strncmp(tmp, "F", data->l) || !ft_strncmp(tmp, "C", data->l))
	{
		if ((data->exit = init_param_numbers(data)) < 0)
			return (data->exit);
	}
	else if (!ft_strncmp(tmp, "NO", data->l) ||
	!ft_strncmp(tmp, "S", data->l) || !ft_strncmp(tmp, "SO", data->l) ||
	!ft_strncmp(tmp, "WE", data->l) || !ft_strncmp(tmp, "EA", data->l))
	{
		if ((data->exit = init_param_textures_1(data)) < 0)
			return (data->exit);
	}
	else
		return (0);
	return (1);
}

int								init_param(t_data *data, int fd)
{
	while (1)
	{
		if (get_next_line(fd, &data->line) == -1)
			return (-11);
		if (ft_strlen(data->line) > 0)
		{
			data->exit = init_param_body(data);
			if ((data->exit < 0))
				return (data->exit);
			else if (data->exit == 0)
				break ;
		}
		if (ft_strlen(data->line) > 0)
		{
			ft_split_free(data->rays->arg);
			data->rays->arg = 0;
		}
		free(data->line);
	}
	if (data->params == 8)
		return (0);
	else
		return (-5);
}
