/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:15:09 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/11 11:43:32 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
		draw_image(scene);
	}
}
