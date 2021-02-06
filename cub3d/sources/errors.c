/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 11:28:11 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/26 15:17:20 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void		free_textures_wall(t_wall *data)
{
	if (data)
	{
		free(data->img);
		free(data->ptr);
		free(data);
	}
}

static void		free_textures(t_data *data)
{
	free_textures_wall(data->texture->wall_e);
	free_textures_wall(data->texture->wall_s);
	free_textures_wall(data->texture->wall_w);
	free_textures_wall(data->texture->wall_n);
	free_textures_wall(data->texture->sprite);
	free(data->texture);
}

static void		free_sprites(t_sprites *root)
{
	t_sprites *next;
	t_sprites *tmp;

	next = root;
	while (next)
	{
		tmp = next;
		free(next->sh);
		next = next->next;
		free(tmp);
	}
}

void			free_all(t_data *data)
{
	free(data->keys);
	ft_split_free(data->rays->arg);
	free(data->rays);
	free_textures(data);
	ft_split_free(data->map);
	free(data->addr);
	free(data->img);
	if (data->line)
		free(data->line);
	free(data->helpers->r_map);
	free(data->helpers);
	free_sprites(data->sprites_root);
	free(data);
}

void			free_init(t_data *data)
{
	free(data->texture);
	free(data->rays);
	free(data->keys);
	free(data->helpers);
	free(data);
	ft_printf("Error : So bad malloc didn`t give memory\n");
	exit(0);
}
