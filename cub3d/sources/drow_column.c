/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drow_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 16:54:51 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 17:07:27 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					exit_x(t_data *data)
{
	errror_exit(-20, data);
	return (0);
}

static	void		get_color_col_e(t_data *data, int *color, int pixel)
{
	if (data->rays->wall == 'N')
	{
		if ((int)data->rays->x % 64 == 0)
			*color = GREY;
		else
			*color = my_mlx_pixel_addres(data->texture->wall_n,
			(int)data->rays->x % 64, pixel);
	}
	else if (data->rays->wall == 'S')
	{
		if ((int)data->rays->x % 64 == 0)
			*color = GREY;
		else
			*color = my_mlx_pixel_addres(data->texture->wall_s,
			(int)data->rays->x % 64, pixel);
	}
	else if (data->rays->wall == 'G')
		*color = my_mlx_pixel_addres(data->texture->sprite,
		(int)data->rays->x % 64, pixel);
}

static	void		get_color_col(t_data *data, int *color, int pixel)
{
	if (data->rays->wall == 'W')
	{
		if ((int)data->rays->y % 64 == 0)
			*color = GREY;
		else
			*color = my_mlx_pixel_addres(data->texture->wall_w,
			(int)data->rays->y % 64, pixel);
	}
	else if (data->rays->wall == 'E')
	{
		if ((int)data->rays->y % 64 == 0)
			*color = GREY;
		else
			*color = my_mlx_pixel_addres(data->texture->wall_e,
			(int)data->rays->y % 64, pixel);
	}
	get_color_col_e(data, color, pixel);
}

void				drow_column(t_data *data, int x)
{
	int color;
	int	y;
	int pixel;

	color = 0;
	y = 0;
	while (y < data->texture->top)
		my_mlx_pixel_put(data, x, y++, data->texture->ceilling);
	while (y <= data->texture->top +
		data->texture->heigth - 2 && y < data->heigth)
	{
		pixel = (y - (int)data->texture->top) * 64 / (int)data->texture->heigth;
		get_color_col(data, &color, pixel);
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
	while (y < data->heigth)
		my_mlx_pixel_put(data, x, y++, data->texture->floor);
}
