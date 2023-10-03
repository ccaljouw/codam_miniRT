/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:41 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/03 13:33:13 by ccaljouw         ###   ########.fr       */
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

t_xyz	get_uvcoord_pl(t_object pl, t_px px)
{
	t_xyz		unit;
	
	(void)pl;
	unit = v_add(px.hitpoint, v_multiply(px.surface_normal, SHADOW_BIAS));
	return (v_create(unit.x, unit.y, unit.z));
}

t_xyz	norm_uvcoord_pl(t_object pl, t_xyz uv)
{
	(void)pl;
	uv.x = (uv.x + 1.0) * 0.5;
	uv.y = (uv.y + 1.0) * 0.5;
	return (uv);
}

