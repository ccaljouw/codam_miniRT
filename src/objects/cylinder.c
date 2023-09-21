/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/21 11:18:59 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	test_cylinder(t_px ray, t_object cylinder, float *hit_dist)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_dist1;
	float	hit_dist2;
	float	m1;
	float	m2;
	float	radius;


	radius = cylinder.diameter * 0.5;
	hit_dist1 = 0;
	hit_dist2 = 0;	
	v_normalizep(&cylinder.vAxis);
	orig_to_center = v_subtract(ray.cam_origin, cylinder.pOrigin);
	abc.x = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, cylinder.vAxis), 2);
	abc.y = 2 * (v_dot(ray.direction, orig_to_center) - (v_dot(ray.direction, cylinder.vAxis) * v_dot(orig_to_center, cylinder.vAxis)));
	abc.z = v_dot(orig_to_center, orig_to_center) - pow(v_dot(orig_to_center, cylinder.vAxis), 2) - pow(radius, 2);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	m1 = (v_dot(ray.direction, cylinder.vAxis) * hit_dist1) + v_dot(orig_to_center, cylinder.vAxis);
	m2 = (v_dot(ray.direction, cylinder.vAxis) * hit_dist1) + v_dot(orig_to_center, cylinder.vAxis);
	if (m1 < cylinder.height && m2 < cylinder.height)
	{
		if (hit_dist1 < 0)
		{
			hit_dist1 = hit_dist2;
			if (hit_dist1 < 0)
				return (0);
		}
		*hit_dist =  hit_dist1;
		return (1);
	}
	// printf("hit distance:%f\n", *hit_dist);
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
int	get_cylinder_surface_data(t_object cy, t_px px, t_scene scene)
{
	(void)cy;
	(void)px;
	(void)scene;
	return (1);
}
