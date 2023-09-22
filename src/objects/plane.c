/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/22 21:47:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


int	test_plane(t_px ray, t_object plane, float *hit_dist)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(ray.direction, plane.vNormal);
	if (fabs(denominator) > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(ray.cam_origin, plane.pOrigin);
		*hit_dist = -v_dot(diff_ray0_plane0, plane.vNormal) / denominator;
		if (*hit_dist > 0)
			return (1);
	}
	return (0);
}


int	get_plane_surface_data(t_object plane, t_px px, t_scene scene)
{
	float	facing_ratio;

	facing_ratio = v_dot(v_normalize(plane.vNormal), v_normalize(px.direction));
	return \
	((int)(plane.rgb[0] * scene.ambient->rgb_ratio[0] * facing_ratio) << 24 \
	| (int)(plane.rgb[1] * scene.ambient->rgb_ratio[1] * facing_ratio) << 16 \
	| (int)(plane.rgb[2] * scene.ambient->rgb_ratio[2] * facing_ratio) << 8 \
	| 255);
}
