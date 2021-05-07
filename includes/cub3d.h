/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:32:56 by sujeon            #+#    #+#             */
/*   Updated: 2021/05/07 15:08:23 by sujeon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Header
*/

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

/*
** KEY
*/

# define KEY_A					0
# define KEY_B					11
# define KEY_C					8
# define KEY_D					2
# define KEY_E					14
# define KEY_F					3
# define KEY_G					5
# define KEY_H					4
# define KEY_I					34
# define KEY_J					38
# define KEY_K					40
# define KEY_L					37
# define KEY_M					46
# define KEY_N					45
# define KEY_O					31
# define KEY_P					35
# define KEY_Q					12
# define KEY_R					15
# define KEY_S					1
# define KEY_T					17
# define KEY_U					32
# define KEY_V					9
# define KEY_W					13
# define KEY_X					7
# define KEY_Y					16
# define KEY_Z					6

# define KEY_AR_L				123
# define KEY_AR_R				124
# define KEY_AR_U				126
# define KEY_AR_D				125

# define KEY_ESC				53

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	    17

/*
** VARIABLE
*/

# define TEXTUREW				64
# define TEXTUREH				64

/*
** STRUCT
*/

typedef struct		s_sprpos
{
	double	x;
	double	y;
	double	dist;
}					t_sprpos;

typedef struct		s_spr
{
	double	spr_x;
	double	spr_y;
	double	invdet;
	double	trans_x;
	double	trans_y;
	int		screenx;
	int		spr_h;
	int		spr_w;
	int		drawstart_x;
	int		drawstart_y;
	int		drawend_x;
	int		drawend_y;
	int		stripe;
	int		tex_x;
	int		tex_y;
	int		y;
	int		d;
	int		color;
}					t_spr;

typedef struct		s_tex
{
	int		texnum;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	int		sign_x;
	int		sign_y;
	int		texture[5][TEXTUREW * TEXTUREW];
}					t_tex;

typedef struct		s_ray
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int		mapX;
	int		mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		**buf;
	double	*zbuf;
}					t_ray;

typedef struct		s_img
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}					t_img;

typedef struct		s_par
{
	int			screenH;
	int			screenW;
	char		*tex_path[4];
	char		*s_path;
	char		*f_rgb;
	char		*c_rgb;
	int			f_color;
	int			c_color;
	char		*map_one;
	char		**map_double;
	char		**test_map;
	int			**map;
	int			cnt_val;
	int			map_h;
	int			*map_w;
	int			spr_num;
	int			sign_map;
	char		orient;
	char		sign_orient;
	int			sign_val[8];
	t_sprpos	*sprpos;
}					t_par;

typedef struct		s_main
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	moveSpeed;
	double	rotSpeed;
	void	*mlx;
	void	*win;
	int		max_h;
	int		max_w;
	int		bmp_sign;
	t_par	par;
	t_img	img;
	t_ray	ray;
	t_tex	tex;
}					t_main;

/*
** FUNCTION
*/

/*
** main.c
*/
void				error(void);
int					ft_exit();

/*
** check.c
*/
void				check(t_main *lst, int argc, char *argv[]);

/*
** main_loop.c
*/
int					main_loop(t_main *lst);

/*
** cub_val.c
*/
void				cub_val(t_main *lst, char *file);
int					rgb_hex(char *src);
void				screen_size(t_main *lst, char **split);

/*
** get_next_line.c
*/
int					get_next_line(int fd, char **line);
char				*g_strjoin(char *s1, char *s2);

/*
** map.c
*/
void				map(t_main *lst, t_par *par);

/*
** check_map.c
*/
void				check_map(t_main *lst, t_par *par);

/*
** load_texture.c
*/
void				load_texture(t_main *lst);

/*
** raycasting.c
*/
void				raycasting(t_main *lst);
void				print_tex(t_main *lst, int x);

/*
** floor_ceiling.c
*/
void				floor_ceiling(t_main *lst);

/*
** sprite.c
*/
void				sprite(t_main *lst);

/*
** draw.c
*/
void				draw(t_main *lst);

/*
** bmp.c
*/
void				bmp(t_main *lst);

/*
** key_press.c
*/
int					key_press(int key, t_main *lst);

/*
** set.c
*/
void				set_ray(t_main *lst, int x);
void				set_lst(t_main *lst);
void				mlx(t_main *lst);
void				set_map(t_main *lst, t_par *par);
void				set_buf(t_main *lst);

/*
** utils.c
*/
void				free_double(char **s);
void				free_one(char *s);
int					check_val(char **s);

#endif
