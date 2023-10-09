/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:24 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/09 23:38:28 by albertvanan      ###   ########.fr       */
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

/**
 * @brief 	object struct containing parameters for each object type
 * 
 * @param	id (t_type) SP: sphere, PL: plane, CY: cylinder, CO: cone
 * @param	p_origin (t_xyz) x,y,z coordinates of the object origin
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
	t_xyz			p_origin;
	t_xyz			v_normal;
	float			diameter; //store radius??
	float			height; // nodig?
	float			albedo;
	float			specular_size;
	float			specular_weight;
	int				rgb[3];
	int				bump_proc;
	int				text_proc;
	mlx_texture_t	*text;
	mlx_texture_t	*bump;
	t_m44			rotate_matrix;
	float			plane_z;
}					t_object;

/**
 * @brief info for each pixel in the image
 * @param	cam_origin (t_xyz)
 * @param	direction (t_xyz)
 * @param	hitObect (t_object *)
 * @param	hp_distance (float) distance to hitpoint
 * @param	facing_ratio (float)
 */
typedef struct s_pixel
{
	t_object	*hitobject;
	t_xyz		cam_origin;
	t_xyz		direction;
	t_xyz		hitpoint;
	t_xyz		uv;
	t_xyz		surface_normal;
	t_xyz		diffuse;
	t_xyz		specular;
	float		facing_ratio;
	float		hit_distance;
	float		hit_height;
	int			color;
}	t_px;

typedef struct s_scene
{
	mlx_t			*mlx;
	mlx_image_t		*image;
	mlx_texture_t	**textures;
	t_ambient		*ambient; // op stack?
	t_camera		*camera; // op stack?
	t_list			*lights;
	t_list			*objects;
	t_px			**pixels;
	int				p_width;
	int				p_height;
	int				n_width;
	int				n_height;
	int				must_resize;
	t_object		*selected;
	t_list			*selected_light;
	bool			single_light;
	float			min_x; //remove
	float			max_x; //remove
	float			min_y; //remove
	float			max_y; //remove
}					t_scene;

typedef struct s_block
{
	t_scene		*scene;
	int			y;
	int			y_max;
}	t_block;

typedef void	t_f(char **param, t_scene *scene);

void			parse_file(char *file, t_scene *scene);
void			parse_type(char *line, t_scene *scene);
t_xyz			set_xyz(char *param, t_scene *scene);
void			set_rgb(char *param, int *rgb, t_scene *scene);
mlx_texture_t	*set_texture(char *param, t_scene *scene);
int				set_procedure(char *param, t_scene *scene);
int				set_bump_procedure(char *param, t_scene *scene);
float			set_specular_size(char *param, t_scene *scene);
float			set_specular_weight(char *param, t_scene *scene);
float			set_albedo(char *param, t_scene *scene);
void			set_surface_properties(char **param, t_object *obj, \
												int i, t_scene *s);
float			to_float(char *param, t_scene *scene);
void			init_ambient(char **param, t_scene *scene);
void			init_camera(char **param, t_scene *scene);
void			camera_geo(t_scene *scene);
void			init_lights(char **param, t_scene *s);
void			init_sphere(char **param, t_scene *scene);
void			init_plane(char **param, t_scene *scene);
void			init_cylinder(char **param, t_scene *scene);
void			init_cone(char **param, t_scene *scene);
void			init_resolution(char **param, t_scene *scene);
// void			calculate_angles(t_scene *scene);

#endif
