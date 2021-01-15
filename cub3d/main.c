/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:29:05 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/14 18:39:28 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int		main(void)
{
	t_data		*data;

	data = malloc(sizeof(t_data));
	data_init(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, keys_pressd, data);
	mlx_hook(data->win_ptr, 3, 1L << 1, keys_relesd, data);
	mlx_loop_hook(data->mlx_ptr, render_next_frame, data);
	mlx_loop(data->mlx_ptr);
	free(data);
	return (0);
}
