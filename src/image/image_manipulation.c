/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/15 00:47:35 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	adjust_diameter_height(mlx_key_data_t keydata, t_object *obj)
{
	if (keydata.key == ZOOM_IN)
	{
		if (keydata.modifier == MLX_SHIFT)
			obj->height += .2;
		else
			obj->diameter += .2;
	}
	if (keydata.key == ZOOM_OUT)
	{
		if (keydata.modifier == MLX_SHIFT)
			obj->height -= .2;
		else
			obj->diameter -= .2;
	}
}

void	scale_triangle(t_object *tr, mlx_key_data_t k)
{
	t_m44	scale;
	int		i;

	scale = m44_init();
	if (k.key == ZOOM_IN)
		m44_scale(&scale, 1.1, 1.1, 1.1);
	if (k.key == ZOOM_OUT)
		m44_scale(&scale, 0.9, 0.9, 0.9);
	i = -1;
	while (++i < 3)
	{
		m44_multiply_vec3(scale, tr->p[i], &tr->p[i]);
	}
}

void	zoom(mlx_key_data_t keydata, t_scene *s)
{
	if (s->selected && s->selected->id != TR)
		adjust_diameter_height(keydata, s->selected);
	else if (s->selected && s->selected->id == TR)
		scale_triangle(s->selected, keydata);
	else if (s->selected_light)
		adjust_light_brightness(keydata, (t_light *)s->selected_light->content);
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
		rotation->y = 10;
	if (keydata.key == ROT_X_N)
		rotation->y = -10;
	if (keydata.key == ROT_Y_N)
		rotation->x = 10;
	if (keydata.key == ROT_Y_P)
		rotation->x = -10;
	if (keydata.key == ROT_Z_N)
		rotation->z = 10;
	if (keydata.key == ROT_Z_P)
		rotation->z = -10;
}

void	rotate_object(t_scene *s, t_m44 r_m, t_xyz rot, t_xyz *orientation)
{
	int	i;

	if (s->selected->id == TR)
	{
		i = -1;
		while (++i < 3)
			m44_multiply_vec3_dir(r_m, s->selected->p[i], &s->selected->p[i]);
		triangle_vectors(s->selected);
	}
	else if (s->selected->id == SP || rot.y != 0)
	{
		s->selected->rotate_matrix = \
				m44_dot_product(r_m, s->selected->rotate_matrix);
	}
	if (s->selected->id != TR)
		m44_multiply_vec3_dir(r_m, *orientation, orientation);
}

void	rotate(mlx_key_data_t keydata, t_scene *s)
{
	t_xyz	*orientation;
	t_xyz	rotation;
	t_m44	rotation_matrix;

	rotation = v_create(0, 0, 0);
	if (s->selected)
		orientation = &s->selected->v_normal;
	else
		orientation = &s->camera->orientation_v;
	set_rotation(&rotation, keydata);
	rotation_matrix = m44_init();
	m44_rotate(&rotation_matrix, rotation.x, rotation.y, -rotation.z);
	if (s->selected)
	{
		rotate_object(s, rotation_matrix, rotation, orientation);
	}
	else
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	ft_printf("new orientation: ");
	print_vector(*orientation);
	camera_geo(s);
	render_image(s);
}

void	adjust_position(t_xyz *pos, mlx_key_data_t keydata)
{
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
}

void	translate_triangle(t_scene *s, mlx_key_data_t k)
{
	t_xyz	pos;
	t_m44	translate;
	int		i;

	adjust_position(&pos, k);
	translate = m44_init();
	m44_translate_by_vector(&translate, pos);
	i = -1;
	while (++i < 3)
		m44_multiply_vec3(translate, s->selected->p[i], &s->selected->p[i]);
}

void	move(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*pos;

	if (scene->selected && scene->selected->id == TR)
	{
		translate_triangle(scene, keydata);
	}
	else
	{
		if (scene->selected && scene->selected->id != TR)
			pos = &scene->selected->p_origin;
		else if (scene->selected_light)
			pos = &((t_light *)scene->selected_light->content)->origin;
		else
			pos = &scene->camera->view_point;
		adjust_position(pos, keydata);
		ft_printf("new position: ");
		print_vector(*pos);
	}
	camera_geo(scene);
	render_image(scene);
}
