/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujeon <sujeon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:32:56 by sujeon            #+#    #+#             */
/*   Updated: 2021/04/24 21:22:15 by sujeon           ###   ########.fr       */
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

# define KEY_AR_L 123
# define KEY_AR_R 124
# define KEY_AR_U 126
# define KEY_AR_D 125

# define KEY_ESC				53

/*
** VARIABLE
*/

# define screenW		   		640
# define screenH			    480
# define mapW			    	24
# define mapH			  		24
# define textureW				64
# define textureH				64

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	    17

/*
** STRUCT
*/

typedef struct      s_img
{
    void    *img;
    int     *data;
    int     size_l;
    int     bpp;
    int     endian;
	int		img_width;
	int		img_height;
}                   t_img;

typedef struct		s_tex
{
	int		texNum;
	double	wallX;
	int		texX;
	int		texY;
	double	step;
	double	texPos;
	int		color;
	int		sign_x;
	int		sign_y;
}					t_tex;

typedef struct 		s_fc
{
	float	rayDirX0;
	float	rayDirY0;
	float	rayDirX1;
	float	rayDirY1;
	int		p;
	float	posZ;
	float	rowDistance;
	float	floorStepX;
	float	floorStepY;
	float	floorX;
	float	floorY;
	int		cellX;
	int		cellY;
	int		color;

}					t_fc;


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
}					t_ray;

typedef struct		s_val
{
	int		h;
	int		w;
	char	*tex_path[4];
	char	*s_path;
	char	*f_color;
	char	*c_color;

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
	int		buf[screenH][screenW];
	int		texture[4][textureH * textureW];
	t_img	img;
}					t_val;

/*
** FUNCTION
*/

//parsing.c
int			parsing(t_val *lst,int fd);
int			get_next_line(int fd, char **line);

// map.c
int			worldMap[mapW][mapH];

// texture.c
void		load_texture(t_val *lst);

// key_press.c
int			key_press(int key, t_val *lst);

// raycasting.c
int			ray_c(t_val *lst);
void		print_tex(t_val *lst, t_ray *ray, t_tex *tex, int x);
void		floor_ceiling(t_val *lst);

//main.c
int			rint_error(void);
#endif