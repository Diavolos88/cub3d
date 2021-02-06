/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:40:07 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:52:12 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void			render_init(t_data *data, int ray)
{
	data->helpers->angle =
	(data->helpers->direction - data->helpers->fov / 2)
	* UNGLE + ray * data->helpers->fov / data->width * UNGLE;
	data->helpers->sin_angle = sin(data->helpers->angle);
	data->helpers->cos_angle = cos(data->helpers->angle);
	data->helpers->cos_fov = cos((0 - data->helpers->fov
	/ 2 + ray * data->helpers->fov / data->width) * UNGLE);
	data->rays->y = data->pos_y;
	data->rays->x = data->pos_x;
}

static	void		init_wall_y(t_data *data)
{
	if (round(data->rays->x / data->rays->width) * data->rays->width -
	floor(data->rays->x / data->rays->width + 1) *
	data->rays->width == (float)0)
		data->rays->wall = 'W';
	else
		data->rays->wall = 'E';
}

static	void		init_wall_x(t_data *data)
{
	if (round(data->rays->y / data->rays->heigth) * data->rays->heigth -
	floor(data->rays->y / data->rays->heigth + 1) *
	data->rays->heigth == (float)0)
		data->rays->wall = 'N';
	else
		data->rays->wall = 'S';
}

static	void		render_next_frame_while(t_data *data, int ray)
{
	while (1)
	{
		if (data->map[(int)floor(data->rays->x / data->rays->width)]
		[(int)floor(data->rays->y / data->rays->heigth)] == '1')
		{
			if (fabs(data->rays->x - round(data->rays->x / data->rays->width) *
			data->rays->heigth) < fabs(data->rays->y - round(data->rays->y
			/ data->rays->heigth) * data->rays->heigth))
				init_wall_y(data);
			else
				init_wall_x(data);
			data->rays->distanse = round(sqrt_dist(data->pos_x,
			data->rays->x, data->pos_y, data->rays->y))
			* data->helpers->cos_fov;
			data->texture->heigth = (data->rays->heigth /
			data->rays->distanse * data->helpers->dist_project);
			data->texture->top = data->heigth / 2 - data->texture->heigth / 2;
			drow_column(data, ray);
			break ;
		}
		data->rays->x += 0.5 * data->helpers->cos_angle;
		data->rays->y += 0.5 * data->helpers->sin_angle;
	}
}

int					render_next_frame(t_data *data)
{
	int ray;

	ray = -1;
	if (data->flag)
		keys_hook(data);
	while (++ray < data->width)
	{
		render_init(data, ray);
		render_next_frame_while(data, ray);
		data->helpers->r_map[ray].d =
		(float)hypot(data->rays->x - data->pos_x, data->rays->y - data->pos_y);
	}
	sprite(data);
	if (data->flag)
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}
