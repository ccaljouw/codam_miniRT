/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/20 21:57:23 by cariencaljo   ########   odam.nl         */
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
	t_xyz	hitPoint;
	t_xyz	abc;
	float	radius;


	radius = cylinder.diameter * 0.5;
	hit_dist1 = 0;
	hit_dist2 = 0;
	
	// use axis
	abc.x = pow(ray.direction.x, 2) + pow(ray.direction.y, 2);
	abc.y = 2 * (pow(ray.cam_origin.x, 2) + pow(ray.cam_origin.y, 2));
	abc.z = pow(ray.cam_origin.x, 2) - pow(ray.cam_origin.y, 2) - pow(radius, 2);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	hitPoint = v_add(ray.cam_origin, v_mulitply(ray.direction, hit_dist1));
	if (v_magnitude(hitPoint) < 1)
	{
		if (hit_dist1 < 0)
		{
			hit_dist1 = hit_dist2;
			if (hit_dist1 < 0)
				return (0);
		}
		*hit_dist = hit_dist1;
		// printf("hit distance:%f\n", *hit_dist);
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
	return (1);
}
