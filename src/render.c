/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 16:56:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/18 22:46:15 by cariencaljo   ########   odam.nl         */
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

uint32_t	getColor(t_rederInfo rData, t_scene *scene)
{
	uint32_t	color;
	t_object	*object;

	object = (t_object *)rData.hitObject;
	if (!object)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	float		dist;
	float		newA;
	dist = rData.tNear;
	(void)scene;
	newA = 255 - ((dist / (object->diameter)));
	color = (object->rgb[0] << 24 | object->rgb[1] << 16 | object->rgb[2] << 8 | (uint32_t)newA);
	// color = (object->rgb[0] << 24 | object->rgb[1] << 16 | object->rgb[2] << 8 \
	// 	| (uint32_t)(255 * scene->ambient->ratio));
	return (color);
}

void	render(t_scene *scene)
{
	t_rederInfo	*rData;
	uint32_t	x;
	uint32_t	y;
	t_ray		camera2Ray;

	x = 0;
	y = 0;
	update_camera2(scene);
	print_camera2(*(scene->camera2));
	rData = malloc(sizeof(rData));
	if (!rData)
		exit_error(ERROR_MEM, NULL, scene);
	while (x < scene->image->width)
	{
		while (y < scene->image->height)
		{
			camera2Ray = generate_ray(scene, x, y);
			rData->hitObject = trace(camera2Ray, rData, scene);
			// if (rData->hitObject)
			// 	printf("o");
			// else
			// 	printf(".");
			// if (rData->hitObject && (camera2Ray.p2.x < scene->camera2->canvas_window.left || camera2Ray.p2.x > scene->camera2->canvas_window.right \
			// 	|| camera2Ray.p2.y < scene->camera2->canvas_window.bottom || camera2Ray.p2.y > scene->camera2->canvas_window.top))
			// 	printf("outside canvas\n");
			mlx_put_pixel(scene->image, x, y, getColor(*rData, scene));
			y++;
		}
		x++;
		y = 0;
		// printf("\n");
	}
}

void	renderTest(t_scene *scene)
{
	int			x;
	int			y;
	float		xscreen;
	float		yscreen;
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
			xscreen = (x * (screenSize / cam->image_size[0])); // incorrect
			yscreen = y * (screenSize / cam->image_size[1]);  // now assumes square fov
			camRay = ray(cam->pOrigin, v_add(cam->pCanvas_centre, v_create(xscreen, yscreen, cam->pCanvas_centre.z)));
			rData->hitObject = trace(camRay, rData, scene);
			mlx_put_pixel(scene->image, x, y, getColor(*rData, scene));
			y++;	
		}
		y = 0;
		x++;
	}
}
