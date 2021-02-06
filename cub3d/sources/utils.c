/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 15:19:29 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/26 15:19:19 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void								drow_sprite(t_data *data,
									int y, int x, t_sprites *sprite)
{
	int color;

	color = my_mlx_pixel_addres(data->texture->sprite,
			sprite->sh->tex_x, sprite->sh->tex_y);
	if (color != EMPTY && y < data->heigth)
		my_mlx_pixel_put(data, x, y, color);
}

int									check_map(char **map)
{
	int j;
	int	i;

	i = -1;
	j = 0;
	while (map[j])
		j++;
	while (++i < (int)ft_strlen(map[0]))
		if (map[0][i] != '1')
			return (-1);
	i = -1;
	while (++i < (int)ft_strlen(map[j - 1]))
		if (map[j - 1][i] != '1')
			return (-1);
	i = -1;
	while (++i < j)
		if (map[i][0] != '1')
			return (-1);
	i = -1;
	while (++i < j)
		if (map[i][((int)ft_strlen(map[i]) - 1)] != '1')
			return (-1);
	return (0);
}

int									create_sprite(t_data *data, int i, int j)
{
	t_sprites	*next;
	t_sprites	*elem;

	if (!(elem = malloc(sizeof(t_sprites))))
		return (-1);
	ft_bzero(elem, sizeof(t_sprites));
	if (!data->sprites_root)
		data->sprites_root = elem;
	else
	{
		next = data->sprites_root;
		while (next->next)
			next = next->next;
		next->next = elem;
	}
	elem->pos_x = j * 64 + 32;
	elem->pos_y = i * 64 + 32;
	elem->next = NULL;
	elem->sh = malloc(sizeof(t_sprite_helpers));
	return (0);
}

void								errror_exit(short error, t_data *data)
{
	if (error == -2)
		ft_printf("Error : Invalid resolution\n");
	else if (error == -3)
		ft_printf("Error : Invalid textures path of files\n");
	else if (error == -4)
		ft_printf("Error : Invalid floor or ceiling color\n");
	else if (error == -5)
		ft_printf("Error : Invalid params size\n");
	else if (error == -6)
		ft_printf("Error : Elot of players\n");
	else if (error == -7)
		ft_printf("Error : No player\n");
	else if (error == -10)
		ft_printf("Error : So bad malloc didn`t give memory\n");
	else if (error == -11)
		ft_printf("Error : Map error\n");
	else if (error == -20)
		ft_printf("See you later\n");
	free_all(data);
	exit(0);
}
