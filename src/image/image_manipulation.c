/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/08 23:51:38 by albertvanan      ###   ########.fr       */
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
		camera_geo(s);
	}
	render_image(s);
}

static void	set_rotation(t_xyz *rotation, mlx_key_data_t keydata)
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
		orientation = &scene->selected->v_normal;
	else
		orientation = &scene->camera->orientation_v;
	set_rotation(&rotation, keydata);
	rotation_matrix = m44_init();
	m44_rotate(&rotation_matrix, -rotation.y, rotation.x, rotation.z);
	if (scene->selected)
	{
		scene->selected->rotate_matrix = \
			m44_dot_product(rotation_matrix, scene->selected->rotate_matrix);
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	}
	else
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	print_vector(*orientation);
	camera_geo(scene);
	render_image(scene);
}

void	move(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*pos;

	if (scene->selected)
		pos = &scene->selected->p_origin;
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
	camera_geo(scene);
	render_image(scene);
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
