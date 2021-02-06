/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 11:42:56 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 16:03:43 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void			one_sprite_column(t_data *data, t_sprites *sprite)
{
	int stripe;
	int y;

	stripe = sprite->sh->draw_start_x - 1;
	while (++stripe < sprite->sh->draw_end_x)
	{
		sprite->sh->tex_x = (int)(256 * (stripe - (-sprite->sh->sprite_width
			/ 2 + sprite->sh->sprite_screen_x)) * 64
			/ sprite->sh->sprite_width) / 256;
		y = sprite->sh->draw_start_y - 1;
		if (sprite->transform_y > 0 && stripe > 0 && stripe
		< data->width && sprite->transform_y < data->helpers->r_map[stripe].d)
			while (++y < sprite->sh->draw_end_y)
			{
				sprite->sh->d = (y) * 256 - data->heigth *
					128 + sprite->sh->sprite_height * 128;
				sprite->sh->tex_y = ((sprite->sh->d * 64)
				/ sprite->sh->sprite_height) / 256;
				drow_sprite(data, y + sprite->sh->sprite_height / 2,
				stripe, sprite);
			}
	}
}

static void			one_sprite_body(t_data *data, t_sprites *sprite)
{
	if (sprite->sh->draw_start_y < 0)
		sprite->sh->draw_start_y = 0;
	sprite->sh->draw_end_y = sprite->sh->sprite_height / 2 + data->heigth / 2;
	if (sprite->sh->draw_end_y >= data->heigth)
		sprite->sh->draw_end_y = data->heigth - 1;
	sprite->sh->sprite_width =
			fabs((data->heigth / (sprite->transform_y)) * 64);
	sprite->sh->draw_start_x =
			-sprite->sh->sprite_width / 2 + sprite->sh->sprite_screen_x;
	if (sprite->sh->draw_start_x < 0)
		sprite->sh->draw_start_x = 0;
	sprite->sh->draw_end_x =
			sprite->sh->sprite_width / 2 + sprite->sh->sprite_screen_x;
	if (sprite->sh->draw_end_x >= data->width)
		sprite->sh->draw_end_x = data->width - 1;
}

static void			one_sprite(t_data *data, t_sprites *sprite)
{
	sprite->inv_det = 1.0 / (data->helpers->plane_x *
	data->helpers->dir_y - data->helpers->dir_x * data->helpers->plane_y);
	sprite->transform_x = sprite->inv_det *
	(data->helpers->dir_y * sprite->dist_x -
		data->helpers->dir_x * sprite->dist_y);
	sprite->transform_y = sprite->inv_det * (-data->helpers->plane_y *
	sprite->dist_x + data->helpers->plane_x * sprite->dist_y);
	sprite->sh->sprite_screen_x = (int)((data->width / 2)
	* (1 + sprite->transform_x / sprite->transform_y));
	sprite->sh->sprite_height =
		fabs((data->heigth / (sprite->transform_y)) * 64);
	sprite->sh->draw_start_y =
		-sprite->sh->sprite_height / 2 + data->heigth / 2;
	one_sprite_body(data, sprite);
	one_sprite_column(data, sprite);
}

static void			boble_sort(t_sort *args, int size)
{
	int			i;
	int			j;
	t_sort		tmp;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (args[j].dist > args[j + 1].dist)
			{
				tmp = args[j];
				args[j] = args[j + 1];
				args[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void				sprite(t_data *data)
{
	t_sprites	*next;
	t_sort		*args;
	int			i;

	i = 0;
	args = malloc(sizeof(t_sort) * 20);
	ft_bzero(args, sizeof(t_sort) * 20);
	next = data->sprites_root;
	while (next)
	{
		next->dist = hypot(next->pos_x - data->pos_x,
						next->pos_y - data->pos_y);
		next->dist_x = next->pos_x - data->pos_x;
		next->dist_y = next->pos_y - data->pos_y;
		args[i].dist = next->dist;
		args[i].link = next;
		next = next->next;
		i++;
	}
	boble_sort(args, i);
	while (--i != -1)
		one_sprite(data, args[i].link);
	free(args);
}
