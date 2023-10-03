/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 22:12:39 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	zoom(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->selected)
	{
		if (scene->selected->id == PL)
			return;
		if (keydata.key == ZOOM_IN)
			scene->selected->diameter++;
		if (keydata.key == ZOOM_OUT)
			scene->selected->diameter--;
		ft_printf("new diameter:%f\n", scene->selected->diameter); //for debugging
	}
	else if(scene->selected_light)
	{
		if (keydata.key == ZOOM_IN)
			((t_light *)(scene->selected_light->content))->brightness += .1;
		if (keydata.key == ZOOM_OUT)
			((t_light *)(scene->selected_light->content))->brightness -= .1;
		ft_printf("new brightness: %f\n", ((t_light *)(scene->selected_light->content))->brightness);
	}
	else
	{
		if (keydata.key == ZOOM_IN)
			scene->camera->fov -= 5;
		if (keydata.key == ZOOM_OUT)
			scene->camera->fov += 5;
		cameraGeometry(scene);
		ft_printf("new fov:%d\n", scene->camera->fov); //for debugging
	}
	render_image(scene);
}

void	rotate(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*orientation;

	if (scene->selected)
		orientation = &scene->selected->vNormal;
	else if (scene->selected_light)
		orientation = &((t_light *)scene->selected_light->content)->origin;
	else
		orientation = &scene->camera->orientation_v;
	if (keydata.key == MOVE_X_N)
		orientation->x -= 0.1;
	if (keydata.key == MOVE_X_P)
		orientation->x += 0.1;
	if (keydata.key == MOVE_Y_N)
		orientation->y -= 0.1;
	if (keydata.key == MOVE_Y_P)
		orientation->y += 0.1;
	if (keydata.key == MOVE_Z_N)
		orientation->z -= 0.1;
	if (keydata.key == MOVE_Z_P)
		orientation->z += 0.1;
	// v_normalizep(orientation);
	cameraGeometry(scene);
	render_image(scene);
	ft_printf("orientation/origin: ");
	print_vector(*orientation);
}

void	set_resize_flag(int width, int height, void	*param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->must_resize = 1;
	scene->n_width = width;
	scene->n_height = height;
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

void	key_input(mlx_key_data_t k, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (k.action == MLX_RELEASE)
	{
		if (k.key == MLX_KEY_ESCAPE)
			exit_error(SUCCESS, NULL, scene);	
		if (k.key == ZOOM_IN || k.key == ZOOM_OUT)
			zoom(k, scene);
		if (k.key == MOVE_X_N || k.key == MOVE_X_P \
			|| k.key == MOVE_Y_N || k.key == MOVE_Y_P \
			|| k.key == MOVE_Z_N || k.key == MOVE_Z_P)
			rotate(k, scene);
		if (k.key == MLX_KEY_L)
			select_light(scene);
		else
			return ;
	}
}

