/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 11:23:58 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/18 20:51:44 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_xyz	look_at(t_camera2 * cam, int x, int y)
{
	t_xyz	worldCoord;
	float	xFact;
	float	yFact;
	float	normX;
	float	normY;
	
	xFact = 1.0 / ((float)cam->image_size[0] / 2);
	yFact = 1.0 / ((float)cam->image_size[1] / 2);
	normX = ((float)x * xFact) - 1.0;
	normY = ((float)y * yFact) - 1.0;
	worldCoord = v_add(cam->pCanvas_centre, v_mulitply(cam->vCanvasU, normX));
	worldCoord = v_add(worldCoord, v_mulitply(cam->vCanvasV, normY));
	return (worldCoord);
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
t_ray	generate_ray(t_scene * scene, int x, int y)
{
	t_camera2	*cam;
	t_ray		ray;

	cam = scene->camera2;
	ray.p1 = cam->pOrigin;
	ray.p2 = look_at(cam, x, y);
	ray.p1_p2 = v_subtract(ray.p2, ray.p1);
	return (ray);
}

/**
 * @brief creates a ray based on start and endpoint
 * 
 * @param p1 (t_xyz) starting point of the cast ray
 * @param p2 (t_xyz) end point
 * @param p1_p2 (t_xyz) distance between p1 and p2
 * @return t_ray 
 */
t_ray	ray(t_xyz p1, t_xyz p2)
{
	t_ray	ray;

	ray.p1 = p1;
	ray.p2 = p2;
	ray.p1_p2 = v_subtract(p2, p1);
	return (ray);
}

void	update_camera2(t_scene *scene)
{
	t_camera2	*cam;

	cam = scene->camera2;
	cam->image_size[0] = scene->image->width;
	cam->image_size[1] = scene->image->height;
	cam->image_ratio = cam->image_size[0] / cam->image_size[1];
	cam->clipping[0] = 1;
	cam->clipping[1] = 1000;
	cam->vCanvasU = v_cross(cam->pOrigin, cam->vDirection);
	cam->vCanvasU = v_normalize(cam->vCanvasU);
	cam->vCanvasV = v_cross(cam->vDirection, cam->vCanvasU);
	cam->vCanvasV = v_normalize(cam->vCanvasV);
	cam->pCanvas_centre = v_add(cam->pOrigin, v_mulitply(cam->vDirection, cam->clipping[0]));
}
