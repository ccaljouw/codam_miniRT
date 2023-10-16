/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:42:48 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 16:21:30 by albertvanan      ###   ########.fr       */
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
	t_xyz	x_plane;
	t_xyz	y_plane;

	(void)scene;
	x_plane = v_normalize(v_cross(tr->v_normal, v_create(0, 1, 0)));
	if (x_plane.x == 0 && x_plane.y == 0 && x_plane.z == 0)
		x_plane = v_normalize(v_cross(tr->v_normal, v_create(1, 0, 0)));
	y_plane = v_normalize(v_cross(x_plane, tr->v_normal));
	uv.x = fmod(v_dot(px->hitpoint, x_plane), tr->plane_x);
	uv.y = fmod(v_dot(px->hitpoint, y_plane), tr->plane_y);
	uv.x = 1 - ((uv.x + tr->plane_x) / (tr->plane_x * 2));
	uv.y = 1 - ((uv.y + tr->plane_y) / (tr->plane_y * 2));
	uv.z = 0;
	return (uv);
}

int	p_is_outside(t_xyz p1, t_xyz p2, t_xyz	p3, t_xyz p)
{
	t_xyz	v1;
	t_xyz	v2;
	t_xyz	vp;
	t_xyz	a;
	t_xyz	b;

	v1 = v_subtract(p2, p1);
	v2 = v_subtract(p3, p1);
	vp = v_subtract(p, p1);
	a = v_cross(v1, v2);
	b = v_cross(v1, vp);
	if ((v_dot(v_normalize(a), b)) < 0)
		return (1);
	return (0);
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
