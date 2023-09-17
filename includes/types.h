/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:32 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/17 23:09:12 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "vector.h"
# include "matrix.h"

/**
 * @brief Ambient lighting (id: "A")
 * @param	ratio (float) ambient lighting ratio in range [0.0,1.0]
 * @param	rgb	(uint32_t[3]) R,G,B colors in range [0-255]
 */
typedef struct ambient_s
{
	float		ratio;
	uint32_t	rgb[3];	
}				t_ambient;

/**
 * @brief Camera (id: "C")
 * @param	view_point (t_xyz) x,y,z coordinates of the camera's origing
 * @param	orientation_v (t_xyz) 3d normalized orientation vector. 
 * In range [-1,1] for each x,y,z axis
 * @param	fov	(int) Horizontal field of view in degrees in range [0,180]
 * @param	principal_axis (t_xyz) vector from camera positon to lookAt position
 */
typedef struct camera_s
{
	t_xyz	view_point;
	t_xyz	orientation_v;
	int		fov;
	t_xyz	look_at;
	float	plane_dist;
	float	c_width;
	float	c_height;
	t_xyz	principal_axis;
	t_xyz	screenU;
	t_xyz	screenV;
	t_xyz	screenCentre;
	t_xyz	origin;
	int		image_width;
	int		image_height;
	float	aspect_ratio;
	float	fov_scale;
	t_m44	cam2world;
	// m44		
}			t_camera;

/**
 * @brief Light (id: "L")
 * @param	light_point (t_xyz) x,y,z coordinates of the light point
 * @param	brightness (float) the light brightness ratio in range [0.0,1.0]
 * @param	rgb	(uint32_t[3]) R,G,B colors 
 * in range [0-255] (unused in mandatory part)
 */
typedef struct light_s
{
	t_xyz		light_point;
	float		brightness;
	uint32_t	rgb[3];	
}				t_light;

/**
 * @brief Sphere (id: "sp")
 * @param	pC (t_xyz) x,y,z coordinates of the sphere center
 * @param	diameter (float) the sphere diameter
 * @param	rgb	(uint32_t[3]) R,G,B colors in range [0-255]
 */
typedef struct s_sphere
{
	t_xyz		pC;
	float		diameter;
	float		radius;
	uint32_t	rgb[3];
}			t_sphere;

/**
 * @brief Plane (id: "pl")
 * @param	point (t_xyz) x,y,z coordinates of a point in the plane
 * @param	normal_v (t_xyz) 33d normalized normal vector. 
 * 					In range [-1,1] for each x,y,z axis:
 * @param	rgb	(uint32_t[3]) R,G,B colors in range [0-255]
 */
typedef struct s_plane
{
	t_xyz		point;
	t_xyz		normal_v;
	uint32_t	rgb[3];
}				t_plane;

/**
 * @brief Cylinder (id: " cy")
 * @param	center (t_xyz) x,y,z coordinates of the center of the cylinder
 * @param	axis_v (t_xyz) 3d normalized vector of axis of cylinder. 
 * 					In range [-1,1] for each x,y,z axis
 * @param	diameter (float) the cylinder diameter
 * @param	height (float) the cylinder height
 * @param	rgb (uint32_t[3]) R,G,B colors in range [0-255]
 */
typedef struct s_cylinder
{
	t_xyz		center;
	t_xyz		axis_v;
	float		diameter;
	float		height;
	uint32_t	rgb[3];
}				t_cylinder;


#endif
