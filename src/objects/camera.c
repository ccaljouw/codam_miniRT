/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 11:23:58 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/17 18:38:42 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

t_xyz	look_at(t_camera * cam, int x, int y)
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
	t_camera	*cam;
	t_ray		ray;

	cam = scene->camera;
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

void	canvas_window(t_camera	*cam)
{
	float		canvas_size;

	canvas_size = 2 * tan(cam->fov[0] / 2) * cam->clipping[0];
	cam->canvas_window.right = canvas_size / 2;
	cam->canvas_window.left = -cam->canvas_window.right;
	canvas_size = 2 * tan(cam->fov[1] / 2) * cam->clipping[0];
	cam->canvas_window.top = canvas_size / 2;
	cam->canvas_window.bottom = -cam->canvas_window.top;
	cam->canvas_ratio = (2 * cam->canvas_window.right) / (2 * cam->canvas_window.top);
}

void	update_camera(t_scene *scene)
{
	t_camera	*cam;

	cam = scene->camera;
	cam->image_size[0] = scene->image->width;
	cam->image_size[1] = scene->image->height;
	cam->image_ratio = cam->image_size[0] / cam->image_size[1];
	cam->clipping[0] = 1; // is used hardcoded in other functions!!!
	cam->clipping[1] = 1000;
	canvas_window(cam);
	cam->focal_length = cam->canvas_window.right / tan(cam->fov[0] / 2);
	cam->vCanvasU = v_cross(cam->vUp, cam->vDirection);
	cam->vCanvasU = v_mulitply(v_normalize(cam->vCanvasU), cam->image_ratio); //image ratio correct here?
	cam->vCanvasV = v_cross(cam->vCanvasU, cam->vUp);
	cam->vCanvasV = v_mulitply(v_normalize(cam->vCanvasV), cam->image_ratio); // image ratio correct here?
	cam->pCanvas_centre = v_add(cam->pOrigin, v_mulitply(cam->vUp, cam->focal_length));
}
