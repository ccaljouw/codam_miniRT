/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:32 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/12 00:05:39 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>
# include <vector.h>
# include "matrix.h"
# include <MLX42.h>
# include <libft.h>

typedef enum e_type
{
	SP = 0,
	PL,
	CY,
	CO
}	t_type;

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
	float			height;
	float			albedo;
	float			specular_size;
	float			specular_weight;
	float			refl;
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
	float		hit_height; // nodig?
	float		refl_count;
	int			color;
}	t_px;

/**
 * @brief Ambient lighting (id: "A")
 * @param	ratio (float) ambient lighting ratio in range [0.0,1.0]
 * @param	rgb	(int[3]) R,G,B colors in range [0-255]
 */
typedef struct ambient_s
{
	float		ratio;
	int			rgb[3];	
	float		rgb_ratio[3];
}				t_ambient;

typedef struct camera_s
{
	t_xyz	origin;
	t_xyz	view_point;
	t_xyz	orientation_v;
	int		fov;
	int		image_width;
	int		image_height;
	float	aspect_ratio;
	float	fov_scale;
	t_m44	cam2world;
}			t_camera;

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
}					t_scene;

typedef struct s_block
{
	t_scene		*scene;
	int			y;
	int			y_max;
}	t_block;

/**
 * @brief a struct containing a stop for a color map.
 * @param	pos 	(float) a scalar value (between 0 and 1) on the color map
 * @param	rgb_fact (float[3]) scalar values for the rgb chanals of the color;
 */
typedef struct stop_s
{
	float	pos;
	t_xyz	rgb_fact;
}			t_stop;

/**
 * @brief struct to store grid values for interpolation
 * @param ab (float[2])
 * @param cd (float[2])
 */
typedef struct grid_s
{
	float	ab[2];
	float	cd[2];
}			t_gird;

/**
 * @brief Light (id: "L")
 * @param	light_point (t_xyz) x,y,z coordinates of the light point
 * @param	brightness (float) the light brightness ratio in range [0.0,1.0]
 * @param	rgb	(int[3]) R,G,B colors 
 * in range [0-255] (unused in mandatory part)
 */
typedef struct light_s
{
	t_xyz		origin;
	float		brightness;
	int			rgb[3];
	t_xyz		rgb_ratios;
}	t_light;

// fuction pointer for intersection test functions of different objects
typedef int		t_hit_test(t_px *ray, t_object, float *hp_info);
typedef int		t_surface_data(t_object obj, t_px *px);
typedef int		t_get_color(t_object obj, t_px px);
typedef t_xyz	t_colormap(float pos);
typedef t_xyz	t_uv(t_object obj, t_px px, t_scene *scene);
typedef t_xyz	t_n_uv(t_object obj, t_xyz uv);

typedef void	t_f(char **param, t_scene *scene);

#endif
