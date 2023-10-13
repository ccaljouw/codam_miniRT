/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 11:42:35 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/13 13:09:06 by cariencaljo   ########   odam.nl         */
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

// void	scale_plane(t_list *objects, int height, int width)
// {
// 	t_object	*cur;

// 	while (objects)
// 	{
// 		cur = (t_object *)objects->content;
// 		if (cur->id == PL && cur->text)
// 		{
// 			cur->plane_y = (cur->text->height * sqrtf(height)) / 500;
// 			cur->plane_x = (cur->text->width * sqrtf(width)) / 500;
// 		}
// 		objects = objects->next;
// 	}
// }

void	do_resize(void *param)
{
	t_scene		*s;
	mlx_image_t	*buf;

	s = (t_scene *)param;
	if (s->must_resize)
	{
		free_pixels(s);
		s->file_height = s->n_height;
		s->file_width = s->n_width;
		s->p_width = s->file_width + AA * (AA_SAMPLES - 1) * s->file_width;
		s->p_height = s->file_height + AA * (AA_SAMPLES - 1) * s->file_height;
		buf = s->image;
		s->image = mlx_new_image(s->mlx, s->p_width, s->p_height);
		// scale_plane(s->objects, s->file_height, s->file_width);
		init_pixels(s);
		camera_geo(s);
		render_image(s);
		image_to_window(s);
		mlx_delete_image(s->mlx, buf);
		s->must_resize = 0;
	}
}
