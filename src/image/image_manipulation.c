/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_manipulation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/11 16:47:26 by cariencaljo   ########   odam.nl         */
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
		adjust_light_brightness(keydata, (t_light *)s->selected_light->content);
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
	m44_rotate(&rotation_matrix, rotation.x, rotation.y, -rotation.z);
	if (scene->selected)
	{
		if (scene->selected->id == SP || rotation.y != 0)
			scene->selected->rotate_matrix = m44_dot_product(rotation_matrix, \
											scene->selected->rotate_matrix);
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	}
	else
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
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
