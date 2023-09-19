/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 16:56:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/19 08:47:03 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


void	*trace(t_ray camera2Ray, t_rederInfo *rData, t_scene *scene)
{
	static f_testHit	*testHit[1]	= {testHitSP}; //testHitPL, testHitCY
	float 				t;
	t_list				*temp;
	t_object			*object;
	
	t = INFINITY;
	rData->tNear = INFINITY;
	rData->hitObject = NULL;
	temp = scene->objects;
	
	while (temp)
	{
		object = (t_object *)temp->content;
		if (testHit[object->id](camera2Ray, object, &t))
		{
			if (t < rData->tNear)
			{
				rData->hitObject = object;
				rData->tNear = t;
			}
		}
		temp = temp->next;
	}
	return (rData->hitObject);
}

float	get_sphere_surface_data2(float hp_distance, t_object *sph, t_px *px)
{
	t_xyz		surface_normal_at_hitpoint;
	t_xyz		hitpoint;
	float		facing_ratio;

	hitpoint = v_add(px->cam_origin, v_mulitply(px->direction, hp_distance));
	surface_normal_at_hitpoint = v_subtract(sph->pOrigin, hitpoint);
	v_normalizep(&surface_normal_at_hitpoint);
	facing_ratio = v_dot(surface_normal_at_hitpoint, px->direction);
	return (facing_ratio);
}

uint32_t	getColor(t_rederInfo rData)
{
	uint32_t	color;
	t_object	*object;
	// float		ratio;

	object = (t_object *)rData.hitObject;
	if (!object)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	// ratio = get_sphere_surface_data2(rData.tNear, rData.hitObject)
	color = (object->rgb[0] << 24 | object->rgb[1] << 16 | object->rgb[2] << 8 | 255);
	return (color);
}

void	renderImage(t_scene *scene)
{
	t_px		*pixels;
	uint32_t	width;
	uint32_t	height;

	width = scene->image->width;
	height = scene->image->height;
	scene->camera->image_width = width;
	scene->camera->image_height = height;
	scene->camera->aspect_ratio = (float)width / height;
	pixels = ft_calloc(scene->camera->image_width * scene->camera->image_height, sizeof(t_px));
	if (pixels == NULL)
		exit_error(ERROR_MEM, NULL, scene);
	loop_pixels(scene, pixels);
}

void	renderTest(t_scene *scene)
{
	int			x;
	int			y;
	float		screenSize;
	double		radians;
	t_ray 		camRay;
	t_camera2	*cam;
	t_rederInfo	*rData;
	
	rData = malloc(sizeof(rData));
	if (!rData)
		exit_error(ERROR_MEM, NULL, scene);
	x = 0;
	y = 0;
	cam = scene->camera2;
	update_camera2(scene);
	radians = (cam->fov[0] / 2) * (3.14159 / 180);
	screenSize = tanf(radians) * cam->clipping[0] * 2;
	printf("screensize:%f, imageW:%d, imageH:%d\n", screenSize, cam->image_size[0], cam->image_size[1]);
	print_vector(cam->pCanvas_centre);
	while (x < cam->image_size[0])
	{
		while (y < cam->image_size[1])
		{
			rData->p.x = (2 * (((float)x + 0.5) / cam->image_size[0]) - 1) * screenSize;
			rData->p.y = (1 - 2 * ((float)y + 0.5) / cam->image_size[1] * (screenSize));
			rData->p.z = cam->pCanvas_centre.z;
			camRay = ray(cam->pOrigin, v_add(cam->pCanvas_centre, rData->p));
			rData->hitObject = trace(camRay, rData, scene);
			mlx_put_pixel(scene->image, x, y, getColor(*rData));
			y++;	
		}
		y = 0;
		x++;
	}
}
