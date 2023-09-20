/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 17:54:01 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/21 00:30:11 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief	Back to those old quadratic math lessons!
 * 			solves x for ax^2 + bx + c (where abc are
 * 			given y the test_sphere function and pasted
 * 			into a vector for Norminette's sake, so
 * 			abc.x = a, abc.y = b, abc.z = c).
 * 			Calculates the discriminant (b^2 - 4ac, remember?)
 * 			if this is below zero, the ray doesn't hit the sphere
 * 			
 * 
 * @param abc abc constants in vector form
 * @param hp1 pointer to first hitpoint
 * @param hp2 pointer to second hitpoint
 * @return int 1 on hit, 0 on no hit
 */
int	get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2)
{
	float	discriminant;
	float	quotient;

	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (0);
	if (discriminant == 0)
		return (*hp1 = -0.5 * abc.y / abc.x, *hp2 = *hp1, 1);
	if (abc.y > 0)
		quotient = -0.5 * (abc.y + sqrt(discriminant));
	else
		quotient = -0.5 * (abc.y - sqrt(discriminant));
	*hp1 = quotient / abc.x;
	*hp2 = abc.z / quotient;
	if (*hp1 > *hp2)
		swap_floats(hp1, hp2);
	return (1);
}

/**
 * @brief	Tests if the ray provided hits the sphere provided. Returns
 * 			1 of this is the case, and updates hit_dist to 
 * 
 * @param ray 
 * @param sphere 
 * @param hit_dist 
 * @return int 
 */
int	test_sphere(t_px ray, t_object sphere, float *hit_dist)
{
	float	hit_dist1;
	float	hit_dist2;
	t_xyz	orig_to_center;
	t_xyz	abc;

	hit_dist1 = 0;
	hit_dist2 = 0;
	orig_to_center = v_subtract(ray.cam_origin, sphere.pOrigin);
	abc.x = v_dot(ray.direction, ray.direction);
	abc.y = 2 * v_dot(ray.direction, orig_to_center);
	abc.z = v_dot(orig_to_center, orig_to_center) - sphere.diameter;
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	if (hit_dist1 < 0)
	{
		hit_dist1 = hit_dist2;
		if (hit_dist1 < 0)
			return (0);
	}
	return (*hit_dist = hit_dist1, 1);
}

/**
 * @brief Calculate the normal of the sphere at the hitpoint (ie the vector
		perpendicular to the surface at that point).
		do this by subtracting the sphere center coordinate from the hitpoint
		coordinate (which is in turn calulated by origin + direction * distance)
		the 'facing ratio' (or how directly the ray hits the sphere
		normal) is the dot product of the surface normal at the hitpoint and 
		the direction of the ray.
 * 
 * @param hp_distance 
 * @param s 
 * @param px 
 * @return float 
 */
int	get_sphere_surface_data(t_object sph, t_px px, t_scene scene)
{
	t_xyz		surface_normal_at_hitpoint;
	t_xyz		hitpoint;
	float		facing_ratio;

	hitpoint = v_add(px.cam_origin, v_mulitply(px.direction, px.hit_distance));
	surface_normal_at_hitpoint = v_subtract(sph.pOrigin, hitpoint);
	v_normalizep(&surface_normal_at_hitpoint);
	facing_ratio = v_dot(surface_normal_at_hitpoint, px.direction);
	return \
		((int)(sph.rgb[0] * scene.ambient->rgb_ratio[0] * facing_ratio) << 24 \
		| (int)(sph.rgb[1] * scene.ambient->rgb_ratio[1] * facing_ratio) << 16 \
		| (int)(sph.rgb[2] * scene.ambient->rgb_ratio[2] * facing_ratio) << 8 \
		| 255);
}
