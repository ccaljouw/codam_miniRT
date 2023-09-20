/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 16:56:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/20 10:20:07 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

uint32_t	getColor(t_px	px, t_scene *scene)
{
	uint32_t	color;
	t_object	*object;
	float		ratio;

	(void)scene;
	object = (t_object *)px.hitobject;
	if (!object)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	ratio = get_sphere_surface_data(*px.hitobject, px);
	color = (object->rgb[0] << 24 | object->rgb[1] << 16 | object->rgb[2] << 8 | (uint32_t)(255 * ratio));
	return (color);
}

t_px	get_ray(t_scene *s, int x, int y)
{
	t_px	px;
	
	px.cam_origin = s->camera->origin;
	px.screen_x = x;
	px.screen_y = y;
	px.cam_x = (2 * (((float)x + 0.5) / s->camera->image_width) - 1) \
						* s->camera->aspect_ratio * s->camera->fov_scale;
	px.cam_y = (1 - 2 * ((float)y + 0.5) / s->camera->image_height) \
						* s->camera->fov_scale;
	px.cam_v3 = v_create(px.cam_x, px.cam_y, 1);
	m44_multiply_vec3_dir(s->camera->cam2world, px.cam_v3, \
											&px.direction);
	v_normalizep(&px.direction);
	return (px);
}

t_px	trace(t_px px, t_scene *scene)
{
	// static f_testHit	*testHit[1]	= {testHitSP}; //testHitPL, testHitCY
	float 				t;
	t_list				*temp;
	t_object			*object;
	
	t = INFINITY;
	px.hit_distance = INFINITY;
	px.hitobject = NULL;
	temp = scene->objects;
	
	while (temp)
	{
		object = (t_object *)temp->content;
		// if (testHit[object->id](&px, object))
		if (test_sphere(px, *object, &px.hit_distance))
		{
			px.hitobject = object;
			if (t < px.hit_distance)
				px.hit_distance = t;
		}
		temp = temp->next;
	}
	return (px);
}


void	renderImage(t_scene *scene)
{
	t_px	px;
	int		x;
	int		y;
	int	width;
	int	height;

	width = scene->image->width;
	height = scene->image->height;
	scene->camera->image_width = width;
	scene->camera->image_height = height;
	scene->camera->aspect_ratio = (float)width / height;
	y = 0;
	while (y < scene->camera->image_height)
	{
		x = 0;
		while (x < scene->camera->image_width)
		{
			px = get_ray(scene, x, y);
			px = trace(px, scene);
			mlx_put_pixel(scene->image, x, y, getColor(px, scene));
			x++;
		}
		y++;
	}
}


