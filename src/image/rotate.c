/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 16:17:07 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/21 19:58:04 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static void	set_rotation(t_xyz *rotation, mlx_key_data_t keydata)
{
	int	coarse;

	coarse = 1;
	if (keydata.modifier == MLX_SHIFT)
		coarse = 10;
	if (keydata.key == ROT_X_P)
		rotation->y = 10 / coarse;
	if (keydata.key == ROT_X_N)
		rotation->y = -10 / coarse;
	if (keydata.key == ROT_Y_N)
		rotation->x = 10 / coarse;
	if (keydata.key == ROT_Y_P)
		rotation->x = -10 / coarse;
	if (keydata.key == ROT_Z_N)
		rotation->z = 10 / coarse;
	if (keydata.key == ROT_Z_P)
		rotation->z = -10 / coarse;
}

void	rotate_object(t_object *cur, t_m44 rot_matrix, t_xyz rot, t_xyz *orient)
{
	int			i;
	t_m44		tr;
	t_m44		tr_i;

	if (cur->id == TR)
	{
		tr = m44_init();
		m44_translate_by_vector(&tr, v_subtract(v_create(0, 0, 0), cur->p[0]));
		m44_invert(tr, &tr_i);
		i = -1;
		while (++i < 3)
		{
			m44_multiply_vec3(tr, cur->p[i], &cur->p[i]);
			m44_multiply_vec3_dir(rot_matrix, cur->p[i], &cur->p[i]);
			m44_multiply_vec3(tr_i, cur->p[i], &cur->p[i]);
		}
		triangle_vectors(cur);
	}
	else if (cur->id == SP || rot.y != 0)
		cur->rotate_matrix = m44_dot_product(rot_matrix, cur->rotate_matrix);
	if (cur->id != TR)
		m44_multiply_vec3_dir(rot_matrix, *orient, orient);
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
		rotate_object(s->selected, rotation_matrix, rotation, orientation);
	else
		m44_multiply_vec3_dir(rotation_matrix, *orientation, orientation);
	ft_printf("new orientation: ");
	print_vector(*orientation);
	camera_geo(s);
	render_image(s);
}
