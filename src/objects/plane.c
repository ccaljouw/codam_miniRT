/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:41 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/05 17:02:24 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_plane(t_px *ray, t_object plane, float *hp_info)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(plane.vNormal, ray->direction);
	if (fabsf(denominator) > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(plane.pOrigin, ray->cam_origin);
		hp_info[0] = v_dot(plane.vNormal, diff_ray0_plane0) / denominator;
		if (hp_info[0] > 0)
			return (1);
	}
	return (0);
}

int	get_plane_surface_data(t_object plane, t_px *px)
{
	px->hitpoint =  v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	px->facing_ratio = v_dot(plane.vNormal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(plane.vNormal, -1);
	else
	{
		px->surface_normal = plane.vNormal;
		px->facing_ratio *= -1;
	}
	return (px->color);
}

bool	v_compare(t_xyz a, t_xyz b)
{
	if (a.x != b.x)
		return (false);
	if (a.y != b.y)
		return (false);
	if (a.z != b.z)
		return (false);
	return (true);
}

t_xyz	get_uvcoord_pl(t_object pl, t_px px)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	y_plane;
	t_xyz	z_plane;
	t_xyz	hp_in_object_space;

	y_plane = pl.vNormal;
	x_plane = v_cross(y_plane, v_create(0,0,1)); // this v_create should be scene->camera->orientation_v
	z_plane = v_cross(x_plane, y_plane);
	v_normalizep(&x_plane);
	v_normalizep(&z_plane);
	v_normalizep(&y_plane);
	hp_in_object_space = v_subtract(px.hitpoint, pl.pOrigin);
	uv.x = v_dot(hp_in_object_space, x_plane);
	uv.y = v_dot(hp_in_object_space, z_plane);
	uv.z = 800 / 40;
	return (uv);
}

t_xyz	norm_uvcoord_pl(t_object pl, t_xyz uv)
{
	(void)pl;
	// uv.z = 50;
	v_normalizep(&uv);
	uv.x = ((uv.x + 1.0) * 0.5);
	uv.y =  (uv.y + 1.0) * 0.5;
	return (uv);
}

