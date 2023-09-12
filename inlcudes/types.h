/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   types.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:32 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 16:26:57 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

/**
 * @brief Ambient lightning (id: "A")
 * @param	ratio (float) ambient lighting ratio in range [0.0,1.0]
 * @param	RGB	(int[3]) R,G,B colors in range [0-255]
 */
typedef struct	ambient_s
{
	float		ratio;
	int			RGB[3];	
}				t_ambient;

/**
 * @brief Camera (id: "C")
 * @param	xyz (float[3]) x,y,z coordinates of the view point
 * @param	norm (?) 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
 * @param	FOV	(int) Horizontal field of view in degrees in range [0,180]
 */
typedef struct	camera_s
{
	float		xyz[3];
	// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis
	int			FOV;
}				t_camera;

/**
 * @brief Light (id: "L")
 * @param	xyz (float[3]) x,y,z coordinates of the light point
 * @param	brightness (float) the light brightness ratio in range [0.0,1.0]
 * @param	RGB	(int[3]) R,G,B colors in range [0-255] (unused in mandatory part)
 */
typedef struct	light_s
{
	float		xyz[3];
	float		brightness;
	int			RGB[3];	
}				t_light;

/**
 * @brief Sphere (id: "sp")
 * @param	xyz (float[3]) x,y,z coordinates of the sphere center
 * @param	diameter (float) the sphere diameter
 * @param	RGB	(int[3]) R,G,B colors in range [0-255]
 */
typedef struct	s_sphere
{
	float		xyz[3];
	float		diameter;
	int			RGB[3];
}				sphere_t;

/**
 * @brief Plane (id: "pl")
 * @param	xyz (float[3]) x,y,z coordinates of a point in the plane
 * @param	norm (?) 33d normalized normal vector. In range [-1,1] for each x,y,z axis:
 * @param	RGB	(int[3]) R,G,B colors in range [0-255]
 */
typedef struct	s_plane
{
	float		xyz[3];
	// 3d normalized normal vector. In range [-1,1] for each x,y,z axis:
	int			RGB[3];
}				plane_t;

/**
 * @brief Cylinder (id: " cy")
 * @param	xyz (float[3]) x,y,z coordinates of the center of the cylinder
 * @param	norm (?) 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis
 * @param	diameter (float) the cylinder diameter
 * @param	height (float) the cylinder height
 * @param	RGB (int[3]) R,G,B colors in range [0-255]
 */
typedef struct	s_cylinder
{
	float		xyz[3];
	// 3d normalized normal vector. In range [-1,1] for each x,y,z axis:
	float		diameter;
	float		height;
	int			RGB[3];
}				t_cylinder;




#endif