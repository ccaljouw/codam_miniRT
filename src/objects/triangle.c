/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/12 14:42:48 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/21 19:54:54 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	get_triangle_surface_data(t_object *tr, t_px *px)
{
	px->hitpoint = \
			v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	px->facing_ratio = v_dot(tr->v_normal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(tr->v_normal, -1);
	else
	{
		px->surface_normal = tr->v_normal;
		px->facing_ratio *= -1;
	}
	return (1);
}

t_xyz	get_uvcoord_tr(t_object *tr, t_px *px, t_scene *scene)
{
	t_xyz	uv;

	(void)scene;
	uv = v_subtract(px->hitpoint, tr->p_origin);
	m44_multiply_vec3_dir(tr->rotate_matrix, uv, \
												&uv);
	uv.x = (uv.x / tr->plane_x);
	uv.y = 1 - (uv.y / tr->plane_y);
	uv.z = 0;
	return (uv);
}

int	check_inside_triangle(t_object *tr, t_xyz p)
{
	t_xyz	cur;
	int		i;

	i = 0;
	while (i < 3)
	{
		cur = v_cross(tr->edge[i], v_subtract(p, tr->p[i]));
		if (v_dot(tr->v_normal, cur) < 0)
			return (0);
		i++;
	}
	return (1);
}

int	test_triangle(t_px *ray, t_object *tr, float *hp_info)
{
	float	surface_norm_dot_dir;
	float	d;
	float	t;
	t_xyz	p;

	surface_norm_dot_dir = v_dot(tr->v_normal, ray->direction);
	if (fabsf(surface_norm_dot_dir) < EPSILON)
		return (0);
	d = -v_dot(tr->v_normal, tr->p[0]);
	t = -(v_dot(ray->cam_origin, tr->v_normal) + d) / surface_norm_dot_dir;
	if (t < EPSILON)
		return (0);
	p = v_add(ray->cam_origin, v_multiply(ray->direction, t));
	if (!check_inside_triangle(tr, p))
		return (0);
	hp_info[0] = t;
	return (1);
}
