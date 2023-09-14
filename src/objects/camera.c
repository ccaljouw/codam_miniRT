/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 11:23:58 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 13:28:54 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_camera(t_camera *cam)
{
	// cam->viewpoint read from file;
	cam->look_at = v_create(0.0, 0.0, 0.0);
	// cam->orientation_v read from file
	cam->plane_dist = 1;
	cam->c_width = 1;
	cam->c_height = 1;
	
}

/**
 * @brief 
 * 1. compute vector form camera to lookAt position (principal axis)
 * 2. compute U and V vectors (vectors on the screen paralel to 
 * x and y of camera position)
 * 3. comput the centre of the screen
 * 4. modify the U and V vectors to match the size of the screen
 * 
 * @param cam (t_camera)
 */
void	cameraGeometry(t_camera *cam)
{
	cam->principal_axis = v_subtract(cam->look_at, cam->view_point);
	v_normalize(&cam->principal_axis);
	
	cam->screenU = v_cross(cam->principal_axis, cam->orientation_v);
	v_normalize(&cam->screenU);
	cam->screenV = v_cross(cam->screenCentre, cam->principal_axis);
	v_normalize(&cam->screenV);
	
	cam->screenCentre = v_add(cam->view_point, v_mulitply(cam->principal_axis, cam->plane_dist));

	cam->screenU = v_mulitply(cam->screenU, cam->c_height);
	cam->screenV = v_mulitply(cam->screenCentre, cam->c_height);
}

/**
 * @brief 
 * 1. comput the location of the screen point in world coordinates
 * 2. use this point and the pamera position to comput the ray
 * 
 * @param screen_x (float)
 * @param screen_y (float)
 * @return t_ray 
 */
t_ray	generate_ray(t_camera *cam, float screen_x, float screen_y)
{
	t_ray	new;
	t_xyz	screenWorldPart1;
	t_xyz	screenWorldCoord;
	
	screenWorldPart1 = v_add(cam->screenCentre, v_mulitply(cam->screenU, screen_x));
	screenWorldCoord = v_add(screenWorldPart1, v_mulitply(cam->screenV, screen_y));
	new = ray(cam->view_point, screenWorldCoord);
	return (new);
}

t_ray	ray(t_xyz p1, t_xyz p2)
{
	t_ray	ray;

	ray.p1 = p1;
	ray.p2 = p2;
	ray.p1_p2 = v_subtract(p2, p1);
	return (ray);
}