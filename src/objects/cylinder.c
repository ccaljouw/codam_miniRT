/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/20 19:21:02 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

// t1 = (-b + sqrt(b^2 - 4ac)) / 2a
// t2 = (-b - sqrt(b^2 - 4ac)) / 2a

// z1 = origin.z + (t1 * direction.z)
// z2 = origin.z + (t2 * direction.z)

// if (zmin < z1 < zmax && zmin < z2 < zmax)
// {
// 	if (t1 < 0)
// 	{
// 		t1 = t2;
// 		if (t1 < 0)
// 			return (0);
// 	}
// }

int	test_cylinder(t_px ray, t_object cylinder, float *hit_dist)
{
	float	hit_dist1;
	float	hit_dist2;
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	z1;
	float	z2;
	float	zmin;
	float	zmax;

	hit_dist1 = 0;
	hit_dist2 = 0;
	// use axis
	orig_to_center = v_subtract(ray.cam_origin, cylinder.pOrigin);
	abc.x = pow(orig_to_center.x, 2) + pow(orig_to_center.y, 2);
	abc.y = (2 * ray.cam_origin.x * orig_to_center.x) + (2 * ray.cam_origin.y * orig_to_center.y);
	abc.z = pow(ray.cam_origin.x, 2) + pow(ray.cam_origin.y, 2) - 1;
	// print_vector(orig_to_center);
	// printf("a:%f, b:%f, c:%f\n", abc.x , abc.y, abc.z);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	z1 = ray.cam_origin.z + (hit_dist1 * ray.direction.z);
	z2 = ray.cam_origin.z + (hit_dist2 * ray.direction.z);
	zmin = cylinder.pOrigin.z;
	zmax = cylinder.pOrigin.z + cylinder.height;
	if (zmin < z1 < zmax && zmin < z2 < zmax)
	{
		if (hit_dist1 < 0)
		{
			hit_dist1 = hit_dist2;
			if (hit_dist1 < 0)
				return (0);
		}
		*hit_dist = hit_dist1;
		return (1);
	}
	return (0);
}

/**
 * @brief 
 * 
 * @param hp_distance 
 * @param s 
 * @param px 
 * @return float 
 */
float	get_cylinder_surface_data(t_object cy, t_px px)
{
	(void)cy;
	(void)px;
	return (255);
}
