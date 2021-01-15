/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 10:02:36 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/15 21:32:48 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "../printf/include/ft_printf.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define SPEED 5

# define UNGLE PI / 180 * -1
# define PI 3.1416

# define EMPTY 0x007C0001
# define WHITE 0x00FFFFFF
# define GREY 0x001f1e1e
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

typedef struct		s_rays_param
{
	// int				extra_x;
	// int				extra_y;
	float			width;
	float			heigth;
	float			x;
	float			y;
	float			distanse;
	char			wall;
}					t_rays_param;

typedef struct		s_wall
{
	void			*img;
	void			*ptr;
	int				bits_per_pixel;
	int				width_img;
	int				line_length;
	int				endian;
	int				heigth_img;
}					t_wall;

typedef struct		s_texture
{
	float			heigth;
	float			top;
	t_wall			*wallW;
	t_wall			*wallS;
	t_wall			*wallE;
	t_wall			*wallN;
	t_wall			*sprite;
}					t_texture;

typedef struct		s_keys
{
	short			w;
	short			a;
	short			s;
	short			d;
	short			esc;
	short			up;
	short			down;
}					t_keys;

typedef struct		s_data
{
	char			**map;
	void			*mlx_ptr;
	void			*win_ptr;
	float			direction;
	float			fov;
	float			camera;
	int				width;
	int				heigth;
	float			angle;
	float			cos_angle;
	float			sin_angle;
	float			cos_fov;
	int				pos_x;
	int				pos_y;
	float			distance;
	float			dist_project;
	char			*title;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_keys			*keys;
	t_rays_param	*rays;
	t_texture		*texture;
}					t_data;

int					render_next_frame(t_data *data);
void				data_init(t_data *data);
int					create_trgb(int t, int r, int g, int b);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
int					keys_hook(t_data *data);
int					init_map(t_data *data);
int					keys_pressd(int keycode, t_data *data);
int					keys_relesd(int keycode, t_data *data);
int					keys_fosuc(int keycode, t_data *data);
void				drow_column(t_data *data, int x);
int					my_mlx_pixel_addres(t_wall *data, int x, int y);
t_wall				*init_texture(char **arg, t_data *data);
void				*ft_split_free(char **start);

#endif
