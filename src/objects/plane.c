/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:41 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/26 16:21:14 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	test_plane(t_px ray, t_object plane, float *hit_dist)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(plane.vNormal, ray.direction);
	if (fabsf(denominator) > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(plane.pOrigin, ray.cam_origin);
		*hit_dist = v_dot(plane.vNormal, diff_ray0_plane0) / denominator;
		if (*hit_dist > 0)
			return (1);
	}
	return (0);
}

int	get_plane_surface_data(t_object plane, t_px *px)
{
	px->facing_ratio = fabsf(v_dot(plane.vNormal, px->direction));
	px->surface_normal = plane.vNormal;
	px->hitpoint =  v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	return (px->color);
}
