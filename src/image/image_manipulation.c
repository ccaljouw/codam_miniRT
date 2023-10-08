/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/08 22:51:48 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	zoom(mlx_key_data_t keydata, t_scene *s)
{
	if (s->selected)
	{
		if (keydata.key == ZOOM_IN)
			s->selected->diameter++;
		if (keydata.key == ZOOM_OUT)
			s->selected->diameter--;
	}
	else if (s->selected_light)
	{
		if (keydata.key == ZOOM_IN)
			((t_light *)(s->selected_light->content))->rgb_ratios = v_multiply \
			(((t_light *)(s->selected_light->content))->rgb_ratios, 1.1);
		if (keydata.key == ZOOM_OUT)
			((t_light *)(s->selected_light->content))->rgb_ratios = v_multiply \
			(((t_light *)(s->selected_light->content))->rgb_ratios, 0.9);
	}
	else
	{
		if (keydata.key == ZOOM_IN)
			s->camera->fov -= 5;
		if (keydata.key == ZOOM_OUT)
			s->camera->fov += 5;
		cameraGeometry(s);
	}
	render_image(s);
}

void	set_rotation(t_xyz *rotation, mlx_key_data_t keydata)
{
	if (keydata.key == ROT_X_P)
		rotation->x = 10;
	if (keydata.key == ROT_X_N)
		rotation->x = -10;
	if (keydata.key == ROT_Y_N)
		rotation->y = 10;
	if (keydata.key == ROT_Y_P)
		rotation->y = -10;
	if (keydata.key == ROT_Z_N)
		rotation->z = 10;
	if (keydata.key == ROT_Z_P)
		rotation->z = -10;
}

void	rotate(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*orientation;
	t_xyz	rotation;
	t_m44	rotation_matrix;

	rotation = v_create(0, 0, 0);
	if (scene->selected)
		orientation = &scene->selected->vNormal;
	else
		orientation = &scene->camera->orientation_v;
	set_rotation(&rotation, keydata);
	rotation_matrix = m44_init();
	m44_rotate(&rotation_matrix, -rotation.y, rotation.x, rotation.z);
	if (scene->selected && scene->selected->id == SP)
		scene->selected->rotate_matrix = \
			m44_dot_product(rotation_matrix, scene->selected->rotate_matrix);
	else
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	print_vector(*orientation);
	cameraGeometry(scene);
	render_image(scene);
}

void	move(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*pos;

	if (scene->selected)
		pos = &scene->selected->pOrigin;
	else if (scene->selected_light)
		pos = &((t_light *)scene->selected_light->content)->origin;
	else
		pos = &scene->camera->view_point;
	if (keydata.key == MOVE_UP)
		pos->y += .5;
	if (keydata.key == MOVE_DOWN)
		pos->y -= .5;
	if (keydata.key == MOVE_LEFT)
		pos->x -= .5;
	if (keydata.key == MOVE_RIGHT)
		pos->x += .5;
	if (keydata.key == MOVE_FRONT)
		pos->z += .5;
	if (keydata.key == MOVE_BACK)
		pos->z -= .5;
	cameraGeometry(scene);
	render_image(scene);
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

void	adjust_ambient(t_scene *scene, mlx_key_data_t key_data)
{
	t_ambient	*a;

	a = scene->ambient;
	if (key_data.key == MLX_KEY_MINUS)
		a->ratio -= .05;
	if (key_data.key == MLX_KEY_EQUAL)
		a->ratio += .05;
	a->rgb_ratio[0] = ((float)a->rgb[0] / 255) * a->ratio;
	a->rgb_ratio[1] = ((float)a->rgb[1] / 255) * a->ratio;
	a->rgb_ratio[2] = ((float)a->rgb[2] / 255) * a->ratio;
	ft_printf("ambient brightness: %f\n", a->ratio);
	render_image(scene);
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
		if (k.key == ROT_X_N || k.key == ROT_X_P \
			|| k.key == ROT_Y_N || k.key == ROT_Y_P \
			|| k.key == ROT_Z_N || k.key == ROT_Z_P)
			rotate(k, scene);
		if (k.key == MOVE_UP || k.key == MOVE_DOWN \
			|| k.key == MOVE_LEFT || k.key == MOVE_RIGHT \
			|| k.key == MOVE_FRONT || k.key == MOVE_BACK)
			move(k, scene);
		if (k.key == MLX_KEY_L)
			select_light(scene);
		if (k.key == MLX_KEY_MINUS || k.key == MLX_KEY_EQUAL)
			adjust_ambient(scene, k);
		else
			return ;
	}
}

