/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/21 23:14:59 by cariencaljo   ########   odam.nl         */
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
	orig_to_center = v_subtract(ray.cam_origin, cylinder.pOrigin);
	abc.x = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, cylinder.vAxis), 2);
	abc.y = 2 * (v_dot(ray.direction, orig_to_center) - (v_dot(ray.direction, cylinder.vAxis) * v_dot(orig_to_center, cylinder.vAxis)));
	abc.z = v_dot(orig_to_center, orig_to_center) - pow(v_dot(orig_to_center, cylinder.vAxis), 2) - pow(radius, 2);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	m1 = (v_dot(ray.direction, cylinder.vAxis) * hit_dist1) + v_dot(orig_to_center, cylinder.vAxis);
	m2 = (v_dot(ray.direction, cylinder.vAxis) * hit_dist1) + v_dot(orig_to_center, cylinder.vAxis);
	if ((m1 < cylinder.height && m2 > 0) || (m2 < cylinder.height && m1 > 0))
	{
		if (hit_dist1 < 0)
		{
			hit_dist1 = hit_dist2;
			if (hit_dist1 < 0)
				return (0);
		}
		if (m1 < m2)
			ray.m_axis = m1;
		else
			ray.m_axis = m2;
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
	t_xyz		surface_normal_at_hitpoint;
	
	t_xyz		hitpoint;
	float		facing_ratio;

	hitpoint = v_add(px.cam_origin, v_mulitply(px.direction, px.hit_distance));
	// surface normal = P - C - V * m
	surface_normal_at_hitpoint = v_mulitply(v_subtract(v_subtract(hitpoint, cy.pOrigin), cy.vAxis), px.m_axis);
	v_normalizep(&surface_normal_at_hitpoint);
	// facing_ratio = v_dot(surface_normal_at_hitpoint, px.direction);
	facing_ratio = 0.8;
	return \
		((int)(cy.rgb[0] * scene.ambient->rgb_ratio[0] * facing_ratio) << 24 \
		| (int)(cy.rgb[1] * scene.ambient->rgb_ratio[1] * facing_ratio) << 16 \
		| (int)(cy.rgb[2] * scene.ambient->rgb_ratio[2] * facing_ratio) << 8 \
		| 255);
}
