/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/16 16:56:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/17 07:20:06 by cariencaljo   ########   odam.nl         */
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
	
	int localColor = 0;
	
	while (temp)
	{
		if (test_spIntersection(cameraRay, &localColor, temp->content, &t))
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
	float		newAmbient;

	sphere = (t_sphere *)rData.hitObject;
	if (!sphere)
		return(0 << 24 | 0 << 16 | 0 << 8 | 255);
	(void)scene;
	// if (rData.hitObject == scene->spheres->content)
		// newAmbient = 255 - ((rData.tNear / (9.499230 + sphere->pC.y + scene->camera->view_point.y + 1)) * 255);
		// newAmbient = 255 - ((255 / (6.861813)) * rData.tNear);
	// else if (rData.hitObject == scene->spheres->next->content)
		// newAmbient = 255 - ((255 / 4.269890) * rData.tNear);
	// else
		// newAmbient = 255 - (255 * (9.499230 / rData.tNear));
	newAmbient = 255;
	color = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | (uint32_t)newAmbient);
	return (color);
}

void	render(t_scene *scene)
{
	t_rederInfo	*rData;
	uint32_t	x;
	uint32_t	y;
	float		xFact;
	float		yFact;
	t_ray		*cameraRay;
	float		normX;
	float		normY;


	x = 0;
	y = 0;
	xFact = 1.0 / ((float)scene->image->width / 2);
	yFact = 1.0 / ((float)scene->image->height / 2);
	rData = malloc(sizeof(rData));
	cameraRay = malloc(sizeof(t_ray));
	if (!cameraRay || !rData)
		exit_error(ERROR_MEM, NULL, scene);
	while (x < scene->image->width)
	{
		while (y < scene->image->height)
		{
			normX = ((float)x * xFact) - 1.0;
			normY = ((float)y * yFact) - 1.0;
			generate_ray(scene->camera, normX, normY, cameraRay);
			rData->hitObject = trace(*cameraRay, rData, scene);
			mlx_put_pixel(scene->image, x, y, getColor(*rData, scene));
			y++;
		}
		x++;
		y = 0;
	}
}

