/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   object.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 08:17:05 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 11:46:06 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

uint32_t	get_gradient_value(uint32_t x, uint32_t y, t_scene *scene)	// for testing purposes only
{
	uint32_t	r;
	uint32_t	g;

	r = (uint32_t)round(((float)x / (float)scene->image->width) * 255);
	g = (uint32_t)round(((float)y / (float)scene->image->height) * 255);
	return (r << 24 | g << 16 | 0 << 8 | 255);
}

void render(void *param)
{
	t_scene		*scene;
	uint32_t	x;
	uint32_t	y;

	scene = (t_scene *)param;
	x = 0;
	y = 0;
	while (x <= scene->image->width - 1)
	{
		while (y <= scene->image->height - 1)
		{
			mlx_put_pixel(scene->image, x, y, get_gradient_value(x, y, scene));
			y++;
		}
		x++;
		y = 0;
	}
}