/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:32 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/06 07:10:42 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef	enum	e_type
{
	SP = 0,
	PL,
	CY,
	CO
}	t_type;

typedef struct s_m44
{
	float	arr[4][4];
}	t_m44;

/**
 * @brief struct with points x, y and z. Can be used to represent 
 * either a point(p), vector(v) or normal(n)
 */
typedef struct xyz_s
{
	float	x;
	float	y;
	float	z;
}			t_xyz;

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

/**
 * @brief Camera (id: "C")
 * @param	view_point (t_xyz) x,y,z coordinates of the camera's origing
 * @param	orientation_v (t_xyz) 3d normalized orientation vector. 
 * In range [-1,1] for each x,y,z axis
 * @param	fov[2]	(float) Horizontal and vertical field of view in degrees in range [0,180]
 * @param	principal_axis (t_xyz) vector from camera positon to lookAt position
 */
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

/**
 * @brief Light (id: "L")
 * @param	light_point (t_xyz) x,y,z coordinates of the light point
 * @param	brightness (float) the light brightness ratio in range [0.0,1.0]
 * @param	rgb	(int[3]) R,G,B colors 
 * in range [0-255] (unused in mandatory part)
 */
typedef struct light_s
{
	t_xyz		light_point;
	t_xyz		origin;
	float		brightness;
	int			rgb[3];
	t_xyz		rgb_ratios;
	t_m44		l2w;
}	t_light;

#endif
