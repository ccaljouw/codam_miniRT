/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/20 11:15:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


int	test_plane(t_px ray, t_object plane, float *hit_dist)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(plane.vNormal, ray.direction);
	if (denominator > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(ray.cam_origin, plane.pOrigin);
		*hit_dist = v_dot(diff_ray0_plane0, plane.vNormal) / denominator;
		if (*hit_dist >= 0)
			return (1);
	}
	return (0);
}


float	get_plane_surface_data(t_object plane, t_px px)
{
	(void)px;
	return (v_dot(v_normalize(plane.vNormal), v_normalize(px.direction)));
}