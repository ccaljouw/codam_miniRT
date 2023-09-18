/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 16:56:05 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/18 23:31:31 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	*trace(t_ray cameraRay, t_rederInfo *rData, t_scene *scene)
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
		if (testHit[object->id](cameraRay, object, &t))
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

uint32_t	getColor(t_rederInfo rData, t_scene *scene)
{
	uint32_t	color;
	t_object	*object;

	object = (t_object *)rData.hitObject;
	if (!object)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	color = (object->rgb[0] << 24 | object->rgb[1] << 16 | object->rgb[2] << 8 \
		| (uint32_t)(255 * scene->ambient->ratio));
	return (color);
}

// void	render(t_scene *scene)
// {
// 	t_rederInfo	*rData;
// 	uint32_t	x;
// 	uint32_t	y;
// 	t_ray		cameraRay;

// 	x = 0;
// 	y = 0;
// 	update_camera(scene);
// 	print_camera(*(scene->camera));
// 	rData = malloc(sizeof(rData));
// 	if (!rData)
// 		exit_error(ERROR_MEM, NULL, scene);
// 	while (x < scene->image->width)
// 	{
// 		while (y < scene->image->height)
// 		{
// 			cameraRay = generate_ray(scene, x, y);
// 			rData->hitObject = trace(cameraRay, rData, scene);
// 			// if (rData->hitObject && (cameraRay.p2.x < scene->camera->canvas_window.left || cameraRay.p2.x > scene->camera->canvas_window.right \
// 			// 	|| cameraRay.p2.y < scene->camera->canvas_window.bottom || cameraRay.p2.y > scene->camera->canvas_window.top))
// 			// 	printf("outside canvas\n");
// 			mlx_put_pixel(scene->image, x, y, getColor(*rData, scene));
// 			y++;
// 		}
// 		x++;
// 		y = 0;
// 	}
// }

