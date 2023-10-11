/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:42:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/11 11:51:31 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_resize_flag(int width, int height, void	*param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->must_resize = 1;
	scene->n_width = width;
	scene->n_height = height;
}

static void	free_pixels(t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->pixels)
	{
		while (i < scene->p_height)
		{
			free(scene->pixels[i]);
			scene->pixels[i] = NULL;
			i++;
		}
		free(scene->pixels);
		scene->pixels = NULL;
	}
}

void	scale_plane_z(t_list *objects, int height)
{
	t_object	*cur;

	while (objects)
	{
		cur = (t_object *)objects->content;
		if (cur->id == PL && cur->text)
			cur->plane_z = (cur->text->height * sqrtf(height)) / 500;
		objects = objects->next;
	}
}

void	do_resize(void *param)
{
	t_scene		*scene;
	mlx_image_t	*buf;

	scene = (t_scene *)param;
	if (scene->must_resize)
	{
		free_pixels(scene);
		scene->p_width = scene->n_width;
		scene->p_height = scene->n_height;
		buf = scene->image;
		scene->image = \
				mlx_new_image(scene->mlx, scene->p_width, scene->p_height);
		scale_plane_z(scene->objects, scene->p_height);
		init_pixels(scene);
		camera_geo(scene);
		render_image(scene);
		image_to_window(scene);
		mlx_delete_image(scene->mlx, buf);
		scene->must_resize = 0;
	}
}
