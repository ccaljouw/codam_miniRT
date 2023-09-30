/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 18:26:44 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/30 15:34:40 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Find the two hitpoints on the cylinder (it can be the same point twice). The calculation is 
 * similar to the sphere hit test but calculated for the radius on each point from the axis that falls
 * between origin and origin + height. 
 * calculate two m values (a scalar that determines the closest point on the axis to the hit point) 
 * and test whether they fall in the range of [0,maxm].
 * 
 * @param ray 
 * @param cylinder 
 * @param hit_dist 
 * @param m 
 * @return int 
 */
int	test_cylinder(t_px *ray, t_object cylinder, float *hit_dist)
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
	orig_to_center = v_subtract(ray->cam_origin, cylinder.pOrigin);
	abc.x = v_dot(ray->direction, ray->direction) - pow(v_dot(ray->direction, cylinder.vNormal), 2);
	abc.y = 2 * (v_dot(ray->direction, orig_to_center) - (v_dot(ray->direction, cylinder.vNormal) * v_dot(orig_to_center, cylinder.vNormal)));
	abc.z = v_dot(orig_to_center, orig_to_center) - pow(v_dot(orig_to_center, cylinder.vNormal), 2) - pow(radius, 2);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	m1 = (v_dot(ray->direction, cylinder.vNormal) * hit_dist1) + v_dot(orig_to_center, cylinder.vNormal);
	m2 = (v_dot(ray->direction, cylinder.vNormal) * hit_dist2) + v_dot(orig_to_center, cylinder.vNormal);
	if (hit_dist1 < 0)
	{
		hit_dist1 = hit_dist2;
		if (hit_dist1 < 0)
			return (0);
	}
	if ((m1 < cylinder.height && m2 > 0) || (m2 < cylinder.height && m1 > 0))
	{
		if (m1 < cylinder.height && m1 > 0)
		{
			*hit_dist = hit_dist1;
			ray->m_cylinder = m1;
		}
		else
		{
			*hit_dist = hit_dist2;
			ray->m_cylinder = m2;	
		}
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
int	get_cylinder_surface_data(t_object cy, t_px *px)
{
	t_xyz		v;
	t_xyz		top;


	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	top = v_add(px->hitpoint, v_multiply(cy.vNormal, cy.height));
	if (v_magnitude(v_subtract(px->hitpoint, top)) < (cy.diameter * 0.5))
		px->surface_normal = cy.vNormal;
	if (v_magnitude(v_subtract(px->hitpoint, cy.pOrigin)) < (cy.diameter * 0.5))
		px->surface_normal = v_multiply(cy.vNormal, -1);
	else
	{
		v = v_subtract(cy.pOrigin, px->hitpoint);
		px->surface_normal = v_cross(v, cy.vNormal);
		px->surface_normal = v_cross(px->surface_normal, cy.vNormal);
		v_normalizep(&px->surface_normal);
	}
	px->facing_ratio = fabsf(v_dot(px->surface_normal, px->direction));
	return (px->color);
}

int	get_color_cylinder(t_object object, t_px px, mlx_texture_t *text)
{
	t_xyz		axis_hp;
	t_xyz		unit;
	float		u;
	float		v;

	axis_hp = v_add(object.pOrigin, v_multiply(v_normalize(object.vNormal), px.m_cylinder));
	unit = v_subtract(px.hitpoint, axis_hp);
	v_normalizep(&unit);
	u = atan2(unit.z, unit.x);
	v = px.m_cylinder / object.height;
	if (object.text == NR_TEXTURES + 1)
		px.color = checkered(px, u, px.m_cylinder, 0);
	else
	{		
		u = 1 - ((u + M_PI) / (2 * M_PI));
		v = 1 - ((v + 1) * 0.5);
		px.color = get_text_pxcolor(text, u, v);
	}
	return (px.color);
}

