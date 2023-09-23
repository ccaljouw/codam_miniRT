/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/23 10:43:32 by cariencaljo   ########   odam.nl         */
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
	v_normalizep(&cylinder.vNormal);
	hit_dist1 = 0;
	hit_dist2 = 0;
	orig_to_center = v_subtract(ray.cam_origin, cylinder.pOrigin);
	abc.x = v_dot(ray.direction, ray.direction) - pow(v_dot(ray.direction, cylinder.vNormal), 2);
	abc.y = 2 * (v_dot(ray.direction, orig_to_center) - (v_dot(ray.direction, cylinder.vNormal) * v_dot(orig_to_center, cylinder.vNormal)));
	abc.z = v_dot(orig_to_center, orig_to_center) - pow(v_dot(orig_to_center, cylinder.vNormal), 2) - pow(radius, 2);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	m1 = (v_dot(ray.direction, cylinder.vNormal) * hit_dist1) + v_dot(orig_to_center, cylinder.vNormal);
	m2 = (v_dot(ray.direction, cylinder.vNormal) * hit_dist2) + v_dot(orig_to_center, cylinder.vNormal);
	if (hit_dist1 < 0)
	{
		hit_dist1 = hit_dist2;
		if (hit_dist1 < 0)
			return (0);
	}
	if ((m1 < cylinder.height && m2 > 0) || (m2 < cylinder.height && m1 > 0))
	{
		if (m1 < cylinder.height && m1 > 0)
			*hit_dist = hit_dist1;
		else
			*hit_dist = hit_dist2;
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
int	get_cylinder_surface_data(t_object cy, t_px px, t_scene scene)
{
	t_xyz		surface_normal_at_hitpoint;
	t_xyz		hitpoint;
	t_xyz		nAxis;
	float		facing_ratio;
	float		t;
	t_xyz		pt;
	t_xyz		top;

	nAxis = v_normalize(cy.vNormal);
	hitpoint = v_add(px.cam_origin, v_multiply(px.direction, px.hit_distance));
	top = v_add(hitpoint, v_multiply(nAxis, cy.height));
	if (v_magnitude(v_subtract(hitpoint, top)) < (cy.diameter * 0.5))
		surface_normal_at_hitpoint = cy.vNormal;
	if (v_magnitude(v_subtract(hitpoint, cy.pOrigin)) < (cy.diameter * 0.5))
		surface_normal_at_hitpoint = v_multiply(cy.vNormal, -1);
	else
	{
		t = v_dot(v_subtract(hitpoint, px.cam_origin), nAxis);
		pt = v_add(cy.pOrigin, v_multiply(nAxis, t));
		surface_normal_at_hitpoint = v_subtract(hitpoint, pt);
	}
	v_normalizep(&surface_normal_at_hitpoint);
	facing_ratio = fabs(v_dot(surface_normal_at_hitpoint, px.direction));
	return \
		((int)(cy.rgb[0] * scene.ambient->rgb_ratio[0] * facing_ratio) << 24 \
		| (int)(cy.rgb[1] * scene.ambient->rgb_ratio[1] * facing_ratio) << 16 \
		| (int)(cy.rgb[2] * scene.ambient->rgb_ratio[2] * facing_ratio) << 8 \
		| 255);
}
