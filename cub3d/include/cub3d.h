/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealexa <ealexa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 10:02:36 by ealexa            #+#    #+#             */
/*   Updated: 2021/01/21 17:30:52 by ealexa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CUB3D_H
# define FT_CUB3D_H

# include "../printf/include/ft_printf.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>

# define SPEED 5
# define POV 2

# define PI 3.1416
# define UNGLE PI / 180 * -1

# define EMPTY 0x007C0001
# define GREY 0x001f1e1e

typedef struct				s_rays_param
{
	float					width;
	float					heigth;
	float					x;
	float					y;
	float					distanse;
	char					wall;
	char					**arg;
}							t_rays_param;

typedef struct				s_wall
{
	void					*img;
	void					*ptr;
	int						bits_per_pixel;
	int						width_img;
	int						line_length;
	int						endian;
	int						heigth_img;
}							t_wall;

typedef struct				s_texture
{
	int						floor;
	int						ceilling;
	float					heigth;
	float					top;
	t_wall					*wall_w;
	t_wall					*wall_s;
	t_wall					*wall_e;
	t_wall					*wall_n;
	t_wall					*sprite;
}							t_texture;

typedef struct				s_keys
{
	short					w;
	short					a;
	short					s;
	short					d;
	short					esc;
	short					up;
	short					down;
}							t_keys;

typedef struct				s_ray_map
{
	float					d;
}							t_ray_map;

typedef struct				s_helpers
{
	float					camera;
	float					direction;
	float					angle;
	float					cos_angle;
	float					sin_angle;
	float					cos_fov;
	float					distance;
	float					dist_project;
	float					fov;
	float					dir_x;
	float					dir_y;
	float					plane_x;
	float					plane_y;
	t_ray_map				*r_map;
}							t_helpers;

typedef struct				s_sprite_helpers
{
	int						sprite_screen_x;
	int						sprite_height;
	int						draw_start_y;
	int						draw_end_y;
	int						sprite_width;
	int						draw_start_x;
	int						draw_end_x;
	int						tex_x;
	int						tex_y;
	int						d;
}							t_sprite_helpers;

typedef struct				s_sprites
{
	int						pos_x;
	int						pos_y;
	float					dist_x;
	float					dist_y;
	float					dist;
	float					inv_det;
	float					transform_x;
	float					transform_y;
	struct s_sprites		*next;
	t_sprite_helpers		*sh;
}							t_sprites;

typedef struct				s_sort
{
	float					dist;
	t_sprites				*link;
}							t_sort;

typedef struct				s_data
{
	char					**map;
	char					*addr;
	char					*map_name;
	char					*line;
	void					*img;
	void					*mlx_ptr;
	void					*win_ptr;
	short					exit;
	short					params;
	int						width;
	int						l;
	int						heigth;
	int						fd;
	int						flag;
	int						pos_x;
	int						pos_y;
	int						line_length;
	int						endian;
	int						bits_per_pixel;
	t_sprites				*sprites_root;
	t_helpers				*helpers;
	t_keys					*keys;
	t_rays_param			*rays;
	t_texture				*texture;
}							t_data;

int							render_next_frame(t_data *data);
void						data_init(t_data *data, int flag, char *map_name);
int							create_trgb(int t, int r, int g, int b);
void						my_mlx_pixel_put(t_data *data,
							int x, int y, int color);
int							keys_hook(t_data *data);
int							init_map(t_data *data);
int							keys_pressd(int keycode, t_data *data);
int							keys_relesd(int keycode, t_data *data);
int							keys_fosuc(int keycode, t_data *data);
void						drow_column(t_data *data, int x);
int							my_mlx_pixel_addres(t_wall *data, int x, int y);
void						*ft_split_free(char **start);
void						errror_exit(short error, t_data *data);
void						free_all(t_data *data);
void						free_init(t_data *data);
int							init_param_numbers(t_data *data);
int							args_len(char **arg);
int							init_param(t_data *data, int fd);
int							init_line(char **map, t_data *data, int j);
int							check_map(char **map);
void						sprite(t_data *data);
int							screen(t_data *data);
float						sqrt_dist(float a, float b,
							float a1, float b1);
void						drow_sprite(t_data *data,
							int y, int x, t_sprites *sprite);
int							check_map(char **map);
float						direction(float x, int flag);
int							create_sprite(t_data *data, int i, int j);
int							exit_x(t_data *data);

#endif
