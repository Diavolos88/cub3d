/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_init_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 16:33:40 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 17:28:53 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int								args_len(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

static	int						init_resolution(t_data *data, char **arg)
{
	int		width;
	int		heigth;

	if (args_len(arg) < 3)
		return (-1);
	width = ft_atoi(arg[1]);
	heigth = ft_atoi(arg[2]);
	if (width <= 0 || heigth <= 0)
		return (-1);
	if (width > 2560)
		width = 2560;
	if (heigth > 1440)
		heigth = 1440;
	if (width < 100)
		width = 1280;
	if (heigth < 100)
		heigth = 720;
	data->width = width;
	data->heigth = heigth;
	data->params++;
	return (0);
}

static int						init_floor(char **arg, t_data *data)
{
	int		r;
	int		g;
	int		b;
	char	**tmp;

	if (args_len(arg) < 2)
		return (-1);
	if (!(tmp = ft_split(arg[1], ',')))
		return (-1);
	if (args_len(tmp) != 3)
		return (-1);
	r = ft_atoi(tmp[0]);
	g = ft_atoi(tmp[1]);
	b = ft_atoi(tmp[2]);
	ft_split_free(tmp);
	if (r < 0 || r > 255)
		return (-1);
	if (g < 0 || g > 255)
		return (-1);
	if (b < 0 || b > 255)
		return (-1);
	data->params++;
	return (create_trgb(1, r, g, b));
}

int								init_param_numbers(t_data *data)
{
	if (!ft_strncmp(data->rays->arg[0], "R", data->l))
	{
		if (init_resolution(data, data->rays->arg) < 0)
			return (-2);
	}
	else if (!ft_strncmp(data->rays->arg[0], "F", data->l))
	{
		if ((data->texture->floor = init_floor(data->rays->arg, data)) < 0)
			return (-4);
	}
	else
	{
		if ((data->texture->ceilling = init_floor(data->rays->arg, data)) < 0)
			return (-4);
	}
	return (0);
}
