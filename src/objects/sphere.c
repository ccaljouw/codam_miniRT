/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/30 15:41:42 by cariencaljo   ########   odam.nl         */
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
int	test_sphere(t_px *ray, t_object sphere, float *hit_dist)
{
	float	hit_dist1;
	float	hit_dist2;
	float	radius;
	t_xyz	orig_to_center;
	t_xyz	abc;

	hit_dist1 = 0;
	hit_dist2 = 0;
	radius = sphere.diameter * 0.5;
	orig_to_center = v_subtract(ray->cam_origin, sphere.pOrigin);
	abc.x = v_dot(ray->direction, ray->direction);
	abc.y = 2 * v_dot(ray->direction, orig_to_center);
	abc.z = v_dot(orig_to_center, orig_to_center) - (radius * radius);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	if (hit_dist1 < 0)
	{
		hit_dist1 = hit_dist2;
		if (hit_dist1 < 0)
			return (0);
	}
	*hit_dist = hit_dist1;
	return (1);
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
int	get_sphere_surface_data(t_object sph, t_px *px)
{
	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	px->surface_normal = v_subtract(sph.pOrigin, px->hitpoint);
	v_normalizep(&px->surface_normal);
	px->facing_ratio = v_dot(px->surface_normal, px->direction);
	px->surface_normal = v_multiply(px->surface_normal, -1);
	return (px->color);
}

int	get_color_sphere(t_object object, t_px px, mlx_texture_t *text)
{
	t_xyz		unit;
	float		u;
	float		v;

	unit = v_subtract(px.hitpoint, object.pOrigin);
	v_normalizep(&unit);
	u = atan2((pow(unit.y, 2) + pow(unit.z, 2)), unit.x);
	v = atan2(unit.z, unit.y);
	if (object.text == NR_TEXTURES + 1)
	{
		unit = v_add(px.hitpoint, v_multiply(px.surface_normal, SHADOW_BIAS));
		px.color = checkered(px, unit.x, unit.y, unit.z);
	}
	else
	{		
		u = 1 - ((u + M_PI) / (2 * M_PI));
		v = 1 - ((v + M_PI) / (2 * M_PI));
		px.color = get_text_pxcolor(text, u, v);
	}
	return (px.color);
}
