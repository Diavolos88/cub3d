/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:10:01 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:14:08 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void				my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int					keys_pressd(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keys->w = 1;
	else if (keycode == 1)
		data->keys->s = 1;
	else if (keycode == 123)
		data->keys->down = 1;
	else if (keycode == 124)
		data->keys->up = 1;
	else if (keycode == 2)
		data->keys->d = 1;
	else if (keycode == 0)
		data->keys->a = 1;
	else if (keycode == 53)
		errror_exit(-20, data);
	return (0);
}

int					keys_relesd(int keycode, t_data *data)
{
	if (keycode == 13)
		data->keys->w = 0;
	else if (keycode == 1)
		data->keys->s = 0;
	else if (keycode == 123)
		data->keys->down = 0;
	else if (keycode == 124)
		data->keys->up = 0;
	else if (keycode == 2)
		data->keys->d = 0;
	else if (keycode == 0)
		data->keys->a = 0;
	return (0);
}

float				direction(float x, int flag)
{
	x *= UNGLE;
	while (x >= 2 * PI)
		x -= 2 * PI;
	while (x < 0)
		x += 2 * PI;
	if (flag)
		return (cos(x));
	return (sin(x));
}
