/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:29:05 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 17:23:01 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static	int				ft_equals_str(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (0);
	while (i < (int)ft_strlen(s1))
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

static	int				check_map_name(char *name)
{
	int	i;

	i = 0;
	while (name[i] != '.' && name[i] != 0)
		i++;
	if (!ft_equals_str(name + i, ".cub"))
		return (1);
	return (0);
}

static	int				check_param(int *flag, int argc, char **argv)
{
	if (argc <= 1)
	{
		ft_printf("Error : Not enough arguments\n");
		return (0);
	}
	if (argc > 3)
	{
		ft_printf("Error : Alot of arguments\n");
		return (0);
	}
	if (argc == 3)
	{
		*flag = 0;
		if (!ft_equals_str(argv[2], "--save"))
		{
			ft_printf("Error : Wrong second arguments\n");
			return (0);
		}
	}
	if (check_map_name(argv[1]))
	{
		ft_printf("Error : Wrong first arguments\n");
		return (0);
	}
	return (1);
}

static	void			hooks_start(t_data *data)
{
	mlx_hook(data->win_ptr, 2, 1L << 0, keys_pressd, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, exit_x, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, keys_relesd, data);
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data);
	mlx_loop(data->mlx_ptr);
}

int						main(int argc, char *argv[])
{
	t_data		*data;
	int			flag;

	flag = 1;
	if (!check_param(&flag, argc, argv))
		return (0);
	if (!(data = malloc(sizeof(t_data))))
	{
		ft_printf("Error : So bad malloc didn`t give memory\n");
		return (0);
	}
	ft_bzero(data, sizeof(t_data));
	data_init(data, flag, argv[1]);
	if (flag)
		hooks_start(data);
	else
	{
		render_next_frame(data);
		screen(data);
	}
	free_all(data);
	return (0);
}
