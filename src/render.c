/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 16:56:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/17 17:56:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	*trace(t_ray cameraRay, t_rederInfo *rData, t_scene *scene)
{
	float 	t;
	t_list	*temp;
	
	t = INFINITY;
	rData->tNear = INFINITY;
	rData->hitObject = NULL;
	temp = scene->spheres;
	
	while (temp)
	{
		if (test_spIntersection(cameraRay, temp->content, &t))
		{
			if (t < rData->tNear)
			{
				rData->hitObject = (t_sphere *)temp->content;
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
	t_sphere	*sphere;

	sphere = (t_sphere *)rData.hitObject;
	if (!sphere)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	color = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | (uint32_t)(255 * scene->ambient->ratio));
	// (void)scene;
	// color = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | 255);
	return (color);
}

void	render(t_scene *scene)
{
	t_rederInfo	*rData;
	uint32_t	x;
	uint32_t	y;
	t_ray		cameraRay;

	x = 0;
	y = 0;
	update_camera(scene);
	print_camera(*(scene->camera));
	rData = malloc(sizeof(rData));
	if (!rData)
		exit_error(ERROR_MEM, NULL, scene);
	while (x < scene->image->width)
	{
		while (y < scene->image->height)
		{
			cameraRay = generate_ray(scene, x, y);
			rData->hitObject = trace(cameraRay, rData, scene);
			// if (rData->hitObject && (cameraRay.p2.x < scene->camera->canvas_window.left || cameraRay.p2.x > scene->camera->canvas_window.right \
			// 	|| cameraRay.p2.y < scene->camera->canvas_window.bottom || cameraRay.p2.y > scene->camera->canvas_window.top))
			// 	printf("outside canvas\n");
			mlx_put_pixel(scene->image, x, y, getColor(*rData, scene));
			y++;
		}
		x++;
		y = 0;
	}
}

