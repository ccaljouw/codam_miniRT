/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_select.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:15:09 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/09 00:14:50 by albertvanan      ###   ########.fr       */
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
		init_pixels(scene);
		camera_geo(scene);
		render_image(scene);
		image_to_window(scene);
		mlx_delete_image(scene->mlx, buf);
		scene->must_resize = 0;
	}
}

void	select_light(t_scene *scene)
{
	int		i;
	t_list	*li;

	if (scene->selected)
	{
		scene->selected = NULL;
		render_image(scene);
	}
	if (!scene->selected_light)
		scene->selected_light = scene->lights;
	else
		scene->selected_light = scene->selected_light->next;
	if (scene->selected_light)
	{
		li = scene->lights;
		i = 1;
		while (li && li != scene->selected_light)
		{
			li = li->next;
			i++;
		}
		ft_printf("light %i selected\n", i);
	}
	else
		ft_printf("no light selected\n");
}

void	select_object(mouse_key_t b, action_t a, modifier_key_t mod, void *p)
{
	t_scene	*scene;
	int		x;
	int		y;

	(void)mod;
	scene = (t_scene *)p;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		if (scene->selected == scene->pixels[y][x].hitobject)
			scene->selected = NULL;
		else
			scene->selected = scene->pixels[y][x].hitobject;
		// draw_image(scene);
		render_image(scene);
	}
}
