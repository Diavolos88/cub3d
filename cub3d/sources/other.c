/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:32:21 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/15 21:35:46 by ealexa           ###   ########.fr       */
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
	*(unsigned int*)dst = color;
}

void				data_init(t_data *data)
{
	t_rays_param	*rays;
	t_keys			*k;
	t_texture		*t;

	ft_bzero(data, sizeof(t_data));
	
	t = malloc(sizeof(t_texture));
	ft_bzero(t, sizeof(t_texture));
	k = malloc(sizeof(t_keys));
	ft_bzero(k, sizeof(t_keys));
	data->keys = k;
	rays = malloc(sizeof(t_rays_param));
	ft_bzero(rays, sizeof(t_rays_param));
	data->rays = rays;
	data->texture = t;
	data->rays->heigth = 64;
	data->rays->width = 64;
	data->mlx_ptr = mlx_init();
	init_map(data);
	data->camera = data->direction * PI / 180;
	data->fov = 60;
	data->angle = 0;
	// data->rays->extra_x = 0;
	// data->rays->extra_y = 1;
	data->dist_project = data->width / 2 / tan(data->fov / 2 * PI / 180);
	data->title = "cub3d";
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->width,
						data->heigth, data->title);
	data->img = mlx_new_image(data->mlx_ptr, data->width, data->heigth);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
						&data->line_length, &data->endian);
}

int					keys_pressd(int keycode, t_data *data)
{
	// ft_printf("key = %d", keycode);
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
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		exit(0);
	}
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

float					direction(float x, int flag)
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

int					keys_hook(t_data *data)
{
	if (data->keys->s)
	{
		if(data->map[(int)(floor((float)(data->pos_x - (SPEED * 10) * direction(data->direction, 1)) / data->rays->width))][(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x -= SPEED * direction(data->direction, 1);
		if(data->map[(int)(floor(data->pos_x / data->rays->width))][(int)(floor((data->pos_y - (SPEED * 10) * direction(data->direction, 0)) / data->rays->heigth))] == '0')
			data->pos_y -= SPEED * direction(data->direction, 0);
	}
	if (data->keys->w)
	{
		if(data->map[(int)(floor((float)(data->pos_x + (SPEED * 10) * direction(data->direction, 1)) / data->rays->width))][(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x += SPEED * direction(data->direction, 1);
		if(data->map[(int)(floor(data->pos_x / data->rays->width))][(int)(floor((data->pos_y + (SPEED * 10) * direction(data->direction, 0)) / data->rays->heigth))] == '0')
			data->pos_y += SPEED * direction(data->direction, 0);
	}
	if (data->keys->down)
		data->direction -= 5;
	if (data->keys->up)
		data->direction += 5;
	if (data->keys->a)
	{
		if(data->map[(int)(floor((float)(data->pos_x - (SPEED * 5) * direction(data->direction, 0)) / data->rays->width))][(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x -= SPEED * direction(data->direction, 0);
		if(data->map[(int)(floor(data->pos_x / data->rays->width))][(int)(floor((data->pos_y + (SPEED * 5) * direction(data->direction, 1)) / data->rays->heigth))] == '0')
			data->pos_y += SPEED * direction(data->direction, 1);
	}
	if (data->keys->d)
	{
		if(data->map[(int)(floor((float)(data->pos_x + (SPEED * 5) * direction(data->direction, 0)) / data->rays->width))][(int)(floor(data->pos_y / data->rays->heigth))] == '0')
			data->pos_x += SPEED * direction(data->direction, 0);
		if(data->map[(int)(floor(data->pos_x / data->rays->width))][(int)(floor((data->pos_y - (SPEED * 5) * direction(data->direction, 1)) / data->rays->heigth))] == '0')
			data->pos_y -= SPEED * direction(data->direction, 1);
	}
	return (0);
}

void		drow_sprite(t_data *data, int x)
{
	int color;
	int	y;
	int pixel;

	y = data->texture->top;
	while (y <= data->texture->top + data->texture->heigth  && y < data->heigth)
	{
		pixel = (y - (int)data->texture->top) * 64 / (int)data->texture->heigth;
		color = my_mlx_pixel_addres(data->texture->sprite, ((int)data->rays->x % 64 + (int)data->rays->y % 64), pixel);
		if (color != EMPTY)
			my_mlx_pixel_put(data, x, y, color);
		y++;
	}
}

void				sprite(t_data *data)
{
	int ray = -1;
	while (++ray <= data->width)
	{
		data->angle = (data->direction - data->fov / 2) * UNGLE + ray * data->fov / data->width * UNGLE;
		data->sin_angle = sin(data->angle);
		data->cos_angle = cos(data->angle);
		data->cos_fov = cos((0 - data->fov / 2 + ray * data->fov / data->width) * UNGLE);
		data->rays->y = data->pos_y;
		data->rays->x = data->pos_x;
		while (1)
		{
			if (data->map[(int)floor(data->rays->x / data->texture->sprite->width_img)][(int) floor(data->rays->y / data->texture->sprite->heigth_img)] == '2')
			{
				data->rays->distanse = round(sqrt((data->pos_x - data->rays->x)*(data->pos_x - data->rays->x) + (data->pos_y - data->rays->y)*(data->pos_y - data->rays->y))) * data->cos_fov;
				data->texture->heigth = (data->texture->sprite->heigth_img / data->rays->distanse * data->dist_project);
				data->texture->top = data->heigth  / 2 - data->texture->heigth / 2;
				drow_sprite(data, ray);
				break ;
			}
			if (data->map[(int)floor(data->rays->x / data->rays->width)][(int) floor(data->rays->y / data->rays->heigth)] == '1')
				break ;
			data->rays->x += 0.5 * data->cos_angle;
			data->rays->y += 0.5 * data->sin_angle;
		}
	}
}

int					render_next_frame(t_data *data)
{
	keys_hook(data);
	int ray = data->width + 1;
	while (--ray)
	{
		data->angle = (data->direction - data->fov / 2) * UNGLE + ray * data->fov / data->width * UNGLE;
		data->sin_angle = sin(data->angle);
		data->cos_angle = cos(data->angle);
		data->cos_fov = cos((0 - data->fov / 2 + ray * data->fov / data->width) * UNGLE);
		data->rays->y = data->pos_y;
		data->rays->x = data->pos_x;
		while (1)
		{
			if (data->map[(int)floor(data->rays->x / data->rays->width)][(int) floor(data->rays->y / data->rays->heigth)] == '1')
			{
				if (fabs(data->rays->x - round(data->rays->x / data->rays->width) * data->rays->heigth) < fabs(data->rays->y - round(data->rays->y / data->rays->heigth) * data->rays->heigth))
				{
					if (round(data->rays->x / data->rays->width) * data->rays->width - floor(data->rays->x / data->rays->width + 1) * data->rays->width == (float) 0)
						data->rays->wall = 'W';
					else
						data->rays->wall = 'E';
				}
				else
				{
					if (round(data->rays->y / data->rays->heigth) * data->rays->heigth - floor(data->rays->y / data->rays->heigth + 1) * data->rays->heigth == (float) 0)
						data->rays->wall = 'N';
					else
						data->rays->wall = 'S';
				}
				data->rays->distanse = round(sqrt((data->pos_x - data->rays->x)*(data->pos_x - data->rays->x) + (data->pos_y - data->rays->y)*(data->pos_y - data->rays->y))) * data->cos_fov;
				data->texture->heigth = (data->rays->heigth / data->rays->distanse * data->dist_project);
				data->texture->top = data->heigth  / 2 - data->texture->heigth / 2;
				drow_column(data, ray);
				break ;
			}
			data->rays->x += 0.5 * data->cos_angle;
			data->rays->y += 0.5 * data->sin_angle;
		}
	}
	// sprite(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img, 0, 0);
	return (0);
}

int				my_mlx_pixel_addres(t_wall *data, int x, int y)
{
	char	*dst;

	dst = data->ptr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void		drow_column(t_data *data, int x)
{
	int color;
	int	y;
	int pixel;
	y = 0;
	while (y < data->texture->top)
	{
		my_mlx_pixel_put(data, x, y, create_trgb(1, 0, 255 , 255));
		y++;
	}
	while (y <= data->texture->top + data->texture->heigth  && y < data->heigth)
	{
		pixel = (y - (int)data->texture->top) * 64 / (int)data->texture->heigth;
		if (data->rays->wall == 'W')
		{
			if ((int)data->rays->y % 64 == 0)
				color = GREY;
			else
				color = my_mlx_pixel_addres(data->texture->wallW, (int)data->rays->y % 64, pixel);
		}
		else if (data->rays->wall == 'E')
		{
			if ((int)data->rays->y % 64 == 0)
				color = GREY;
			else
				color = my_mlx_pixel_addres(data->texture->wallE, (int)data->rays->y % 64, pixel);
		}
		else if (data->rays->wall == 'N')
		{
			if ((int)data->rays->x % 64 == 0)
				color = GREY;
			else
				color = my_mlx_pixel_addres(data->texture->wallN, (int)data->rays->x % 64, pixel);
		}
		else if (data->rays->wall == 'S')
		{
			if ((int)data->rays->x % 64 == 0)
				color = GREY;
			else
				color = my_mlx_pixel_addres(data->texture->wallS, (int)data->rays->x % 64, pixel);
		} else if (data->rays->wall == 'G')
			color = my_mlx_pixel_addres(data->texture->sprite, (int)data->rays->x % 64, pixel);
		my_mlx_pixel_put(data, x, y, color);
		y++;
	}
	while (y < data->heigth)
	{
		my_mlx_pixel_put(data, x, y, create_trgb(1, 127, 255 , 0));
		y++;
	}
}

// color = img->text[1].addr[img->text->text_y % 64 * img->text[1].line_lenght + img->text->text_x % 64 * img->text[1].bits_per_pixel / 8];