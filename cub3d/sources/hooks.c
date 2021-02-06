/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:33:18 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:36:32 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void				keys_hook_dir_up(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = data->helpers->dir_x;
	data->helpers->dir_x = data->helpers->dir_x *
	cos(POV * UNGLE) - data->helpers->dir_y * sin(POV * UNGLE);
	data->helpers->dir_y = old_dir_x * sin(POV *
	UNGLE) + data->helpers->dir_y * cos(POV * UNGLE);
	data->helpers->direction += POV;
	old_plane_x = data->helpers->plane_x;
	data->helpers->plane_x =
	data->helpers->plane_x * cos(POV * UNGLE)
	- data->helpers->plane_y * sin(POV * UNGLE);
	data->helpers->plane_y = old_plane_x * sin(POV
	* UNGLE) + data->helpers->plane_y * cos(POV * UNGLE);
}

static void				keys_hook_dir(t_data *data)
{
	double old_dir_x;
	double old_plane_x;

	if (data->keys->down)
	{
		old_dir_x = data->helpers->dir_x;
		data->helpers->dir_x = data->helpers->dir_x *
		cos(-POV * UNGLE) - data->helpers->dir_y * sin(-POV * UNGLE);
		data->helpers->dir_y = old_dir_x * sin(-POV * UNGLE)
		+ data->helpers->dir_y * cos(-POV * UNGLE);
		old_plane_x = data->helpers->plane_x;
		data->helpers->plane_x = data->helpers->plane_x
		* cos(-POV * UNGLE) - data->helpers->plane_y * sin(-POV * UNGLE);
		data->helpers->plane_y = old_plane_x * sin(-POV
		* UNGLE) + data->helpers->plane_y * cos(-POV * UNGLE);
		data->helpers->direction -= POV;
	}
	if (data->keys->up)
		keys_hook_dir_up(data);
}

static void				keys_hook_move(t_data *data)
{
	if (data->keys->s)
	{
		if (data->map[(int)(floor((float)(data->pos_x - (SPEED * 10)
		* direction(data->helpers->direction, 1)) / data->rays->width))]
		[(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x -= SPEED * direction(data->helpers->direction, 1);
		if (data->map[(int)(floor(data->pos_x / data->rays->width))]
		[(int)(floor((data->pos_y - (SPEED * 10) *
		direction(data->helpers->direction, 0)) / data->rays->heigth))] == '0')
			data->pos_y -= SPEED * direction(data->helpers->direction, 0);
	}
	if (data->keys->w)
	{
		if (data->map[(int)(floor((float)(data->pos_x + (SPEED * 10) *
		direction(data->helpers->direction, 1)) / data->rays->width))]
		[(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x += SPEED * direction(data->helpers->direction, 1);
		if (data->map[(int)(floor(data->pos_x / data->rays->width))]
		[(int)(floor((data->pos_y + (SPEED * 10) *
		direction(data->helpers->direction, 0)) / data->rays->heigth))] == '0')
			data->pos_y += SPEED * direction(data->helpers->direction, 0);
	}
}

int						keys_hook(t_data *data)
{
	keys_hook_dir(data);
	keys_hook_move(data);
	if (data->keys->a)
	{
		if (data->map[(int)(floor((float)(data->pos_x - (SPEED * 5)
		* direction(data->helpers->direction, 0)) / data->rays->width))]
		[(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x -= SPEED * direction(data->helpers->direction, 0);
		if (data->map[(int)(floor(data->pos_x / data->rays->width))]
		[(int)(floor((data->pos_y + (SPEED * 5) *
		direction(data->helpers->direction, 1)) / data->rays->heigth))] == '0')
			data->pos_y += SPEED * direction(data->helpers->direction, 1);
	}
	if (data->keys->d)
	{
		if (data->map[(int)(floor((float)(data->pos_x + (SPEED * 5) *
		direction(data->helpers->direction, 0)) / data->rays->width))]
		[(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x += SPEED * direction(data->helpers->direction, 0);
		if (data->map[(int)(floor(data->pos_x / data->rays->width))]
		[(int)(floor((data->pos_y - (SPEED * 5) *
		direction(data->helpers->direction, 1)) / data->rays->heigth))] == '0')
			data->pos_y -= SPEED * direction(data->helpers->direction, 1);
	}
	return (0);
}
