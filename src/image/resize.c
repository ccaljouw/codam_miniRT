/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 11:42:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/18 09:45:43 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_resize_flag(int width, int height, void	*param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->must_resize = 1;
	mlx_resize_image(scene->render_image, width, height);
	mlx_delete_image(scene->mlx, scene->image);
	scene->n_width = width;
	scene->n_height = height;
	scene->frames = 0;
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

void	do_resize(void *param)
{
	t_scene		*s;

	s = (t_scene *)param;
	s->frames++;
	if (s->must_resize && s->frames > 50)
	{
		free_pixels(s);
		s->file_height = s->n_height;
		s->file_width = s->n_width;
		s->p_width = s->file_width + (s->aa - 1) * s->file_width;
		s->p_height = s->file_height + (s->aa - 1) * s->file_height;
		s->image = mlx_new_image(s->mlx, s->p_width, s->p_height);
		init_pixels(s);
		camera_geo(s);
		render_image(s);
		image_to_window(s, s->image);
		s->must_resize = 0;
	}
}
