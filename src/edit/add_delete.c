/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_delete.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 00:18:31 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 00:20:00 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	delete_object(t_scene *scene)
{
	t_list	*to_delete;

	if (!scene->selected && !scene->selected_light)
		return ;
	to_delete = scene->objects;
	while (to_delete)
	{
		if (to_delete->content == scene->selected)
			break ;
		to_delete = to_delete->next;
	}
	if (scene->selected && to_delete)
	{
		ft_lstdel_item(&scene->objects, to_delete, free);
		scene->selected = NULL;
	}
	else if (scene->selected_light)
	{
		ft_lstdel_item(&scene->lights, scene->selected_light, free);
		scene->selected_light = NULL;
		if (ft_lstsize(scene->lights) == 1)
			scene->single_light = true;
	}
	render_image(scene);
}

static t_xyz	get_new_object_origin(t_scene *s, int distance)
{
	t_xyz	offset;

	offset.x = s->camera->orientation_v.x * -distance;
	offset.y = s->camera->orientation_v.y * -distance;
	offset.z = s->camera->orientation_v.z * distance;
	return (v_add(s->camera->origin, offset));
}

void	add_object(t_scene *scene, int id)
{
	t_list		*new_node;
	t_object	*new_object;

	new_object = ft_calloc(1, sizeof(t_object));
	new_node = ft_lstnew(new_object);
	if (!new_node || !new_object)
		return (free(new_node), free(new_object));
	new_object->id = id;
	new_object->diameter = 1;
	new_object->p_origin = get_new_object_origin(scene, 6);
	if (id == PL)
		new_object->p_origin.y -= 2;
	new_object->v_normal = v_create(0, 1, 0);
	new_object->height = 2;
	new_object->albedo = ALBEDO;
	new_object->rgb[0] = 255;
	new_object->rgb[1] = 255;
	new_object->rgb[2] = 255;
	ft_lstadd_back(&scene->objects, new_node);
	scene->selected = new_object;
	render_image(scene);
}

void	add_light(t_scene *scene)
{
	t_list	*new_node;
	t_light	*new_light;

	new_light = ft_calloc(1, sizeof(t_light));
	new_node = ft_lstnew(new_light);
	if (!new_light || !new_node)
		return (free(new_light), free(new_node));
	new_light->origin = get_new_object_origin(scene, 10);
	new_light->brightness = .2;
	new_light->rgb[0] = 255;
	new_light->rgb[1] = 255;
	new_light->rgb[2] = 255;
	new_light->rgb_ratios = v_create(1, 1, 1);
	scene->single_light = false;
	ft_lstadd_back(&scene->lights, new_node);
	scene->selected = NULL;
	scene->selected_light = new_node;
	render_image(scene);
}
