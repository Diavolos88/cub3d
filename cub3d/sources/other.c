/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:32:21 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:55:30 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void			data_init_start(t_data *data, int flag, char *map_name)
{
	data->helpers = malloc(sizeof(t_helpers));
	ft_bzero(data->helpers, sizeof(t_helpers));
	data->texture = malloc(sizeof(t_texture));
	ft_bzero(data->texture, sizeof(t_texture));
	data->keys = malloc(sizeof(t_keys));
	ft_bzero(data->keys, sizeof(t_keys));
	data->rays = malloc(sizeof(t_rays_param));
	ft_bzero(data->rays, sizeof(t_rays_param));
	data->flag = flag;
	data->map_name = map_name;
	data->rays->heigth = 64;
	data->rays->width = 64;
	data->mlx_ptr = mlx_init();
	if (!data->helpers || !data->texture ||
		!data->keys || !data->rays || !data->mlx_ptr)
		free_init(data);
}

void				data_init(t_data *data, int flag, char *map_name)
{
	data_init_start(data, flag, map_name);
	init_map(data);
	data->helpers->r_map = malloc(sizeof(t_ray_map) * data->width);
	ft_bzero(data->helpers->r_map, sizeof(t_ray_map) * data->width);
	data->helpers->camera = data->helpers->direction * PI / 180;
	data->helpers->fov = 66;
	data->helpers->dist_project = data->width
		/ 2 / tan(data->helpers->fov / 2 * PI / 180);
	if (flag)
	{
		data->win_ptr = mlx_new_window(data->mlx_ptr, data->width,
						data->heigth, "switcher 3d");
	}
	data->img = mlx_new_image(data->mlx_ptr, data->width, data->heigth);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
						&data->line_length, &data->endian);
}

float				sqrt_dist(float a, float b, float a1, float b1)
{
	return (round(sqrt((a - b) * (a - b) + (a1 - b1) * (a1 - b1))));
}

int					my_mlx_pixel_addres(t_wall *data, int x, int y)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}
