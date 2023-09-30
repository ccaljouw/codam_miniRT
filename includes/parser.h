/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/30 19:41:49 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <pthread.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# ifndef THREADS
#  define THREADS 1
# endif

# define ASCII_WIDTH  120
# define ASCII_HEIGHT 40

# define IM_WIDTH 512
# define IM_HEIGHT 512
# define MAX_WIDTH 1024
# define MAX_HEIGHT 1024


# define MOVE_X_P 	MLX_KEY_RIGHT
# define MOVE_X_N 	MLX_KEY_LEFT
# define MOVE_Y_P 	MLX_KEY_UP
# define MOVE_Y_N 	MLX_KEY_DOWN
# define MOVE_Z_P 	MLX_KEY_PERIOD
# define MOVE_Z_N 	MLX_KEY_COMMA

# define ZOOM_IN 	MLX_KEY_I
# define ZOOM_OUT 	MLX_KEY_O

#define SHADOW_BIAS 0.001

/**
 * @brief 	object struct containing parameters for each object type
 * 
 * @param	id (t_type) SP: sphere, PL: plane, CY: cylinder
 * @param	pOrigin (t_xyz) x,y,z coordinates of the object origin
 * @param	diameter (float) the diameter (of sphere or cylinder)
 * @param	rgb	(int[3]) R,G,B colors in range [0-255]
 * @param	vNormal (t_xyz) 33d normalized normal vector (of plane). 
 * @param	vAxis (t_xyz) 3d normalized vector of axis of cylinder. 
 * 			In range [-1,1] for each x,y,z axis
 * @param	height (float) the cylinder height
 * @param	text	(int) id for the texture to apply to the surgface.
 * @param	albedo (float) the albedo of the object surface
 */
typedef struct s_object
{
	t_type			id;
	t_xyz			pOrigin;
	float			diameter;
	float			height;
	int				text;
	int				rgb[3];
	t_xyz			vNormal;
	float			albedo;
}					t_object;

/**
 * @brief info for each pixel in the image
 * @param	screen_x (int)
 * @param	screen_y (int)
 * @param	cam_x (float)
 * @param	cam_y (float)
 * @param	cam_v3 (t_xyz)
 * @param	cam_origin (t_xyz)
 * @param	direction (t_xyz)
 * @param	hitObect (t_object *)
 * @param	hp_distance (float) distance to hitpoint
 * @param	facing_ratio (float)
 */
typedef struct s_pixel
{
	int			screen_x;
	int			screen_y;
	float		cam_x;
	float		cam_y;
	t_xyz		cam_v3;
	t_xyz		cam_origin;
	t_xyz		direction;
	t_object	*hitobject;
	t_xyz		hitpoint;
	t_xyz		surface_normal;
	t_xyz		ratios;
	float		hit_distance;
	float		m;
	float		facing_ratio;
	int			color;
}	t_px;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	**textures;
	t_ambient		*ambient; // bij één ambient light kan dit op de stack?
	t_camera		*camera; // bij éen camera kan dit op de stack?
	// t_light			*light;
	t_list			*lights;
	t_list			*objects;
	t_px			**pixels;
	int				p_width;
	int				p_height;
	int				n_width;
	int				n_height;
	bool			must_resize;
	t_object		*selected;
	t_list			*selected_light;
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
void	init_lights(char **param, t_scene *s);
void	init_sphere(char **param, t_scene *scene);
void	init_plane(char **param, t_scene *scene);
void	init_cylinder(char **param, t_scene *scene);
void	init_cone(char **param, t_scene *scene);
void	init_resolution(char **param, t_scene *scene);

#endif
