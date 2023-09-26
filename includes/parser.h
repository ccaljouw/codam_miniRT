/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:24 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/26 15:30:46 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <pthread.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# define ASCII_WIDTH  120
# define ASCII_HEIGHT 40

# define IM_WIDTH 512
# define IM_HEIGHT 512
# define MAX_WIDTH 1024
# define MAX_HEIGHT 1024

# define THREADS 1

# define MOVE_X_P 	MLX_KEY_RIGHT
# define MOVE_X_N 	MLX_KEY_LEFT
# define MOVE_Y_P 	MLX_KEY_UP
# define MOVE_Y_N 	MLX_KEY_DOWN
# define MOVE_Z_P 	MLX_KEY_PERIOD
# define MOVE_Z_N 	MLX_KEY_COMMA

# define ZOOM_IN 	MLX_KEY_I
# define ZOOM_OUT 	MLX_KEY_O

#define SHADOW_BIAS 0.001

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_image_t		*rendering;
	t_ambient		*ambient; // bij één ambient light kan dit op de stack?
	t_camera		*camera; // bij éen camera kan dit op de stack?
	t_light			*light;
	t_list			*lights;
	t_list			*objects;
	t_px			**pixels;
	int				p_width;
	int				p_height;
	t_object		*selected;
}					t_scene;

typedef struct s_block
{
	t_scene		*scene;
	int			y;
	int			y_max;
}	t_block;

typedef void	t_f(char **param, t_scene *scene);

void	parse_file(char *file, t_scene *scene);
void	parse_type(char *line, t_scene *scene);
t_xyz	set_xyz(char *param, t_scene *scene);
void	set_rgb(char *param, int *rgb, t_scene *scene);
float	to_float(char *param, t_scene *scene);
void	init_ambient(char **param, t_scene *scene);
void	init_camera(char **param, t_scene *scene);
void	cameraGeometry(t_scene *scene);
void	init_light(char **param, t_scene *scene);
void	init_lights(char **param, t_scene *s);
void	init_sphere(char **param, t_scene *scene);
void	init_plane(char **param, t_scene *scene);
void	init_cylinder(char **param, t_scene *scene);
void	init_resolution(char **param, t_scene *scene);

#endif
