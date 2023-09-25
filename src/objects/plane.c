/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:14:41 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/25 12:31:23 by albertvanan      ###   ########.fr       */
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

int	get_plane_surface_data(t_object plane, t_px *px, t_scene scene)
{
	float	facing_ratio;
	t_xyz	ratios;

	facing_ratio = fabsf(v_dot(plane.vNormal, px->direction));
	ratios = v_create(0, 0, 0);
	// print_vector(ratios);
	loop_lights(scene, plane.vNormal, v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance)), &ratios, "plane");
	// ft_printf("--> ");
	// print_vector(ratios);
	px->color = ((int)(plane.rgb[0] * ft_clamp(0, 1, ((scene.ambient->rgb_ratio[0] * facing_ratio) + ratios.x * (0.18 / M_PI)))) << 24 \
	| (int)(plane.rgb[1] * ft_clamp(0, 1, ((scene.ambient->rgb_ratio[1] * facing_ratio) + ratios.y * (0.18 / M_PI)))) << 16 \
	| (int)(plane.rgb[2] * ft_clamp(0, 1, ((scene.ambient->rgb_ratio[2] * facing_ratio) + ratios.z * (0.18 / M_PI)))) << 8 \
	| 255);
	return (px->color);
}
