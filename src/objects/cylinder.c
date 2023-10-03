/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:26:44 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/03 13:11:14 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_xyz	get_abc_cyl(t_px *ray, t_xyz orig_to_center, t_object cylinder)
{
	t_xyz	abc;
	float	radius;

	radius = cylinder.diameter * 0.5;
	abc.x = v_dot(ray->direction, ray->direction) \
			- pow(v_dot(ray->direction, cylinder.vNormal), 2);
	abc.y = 2 * (v_dot(ray->direction, orig_to_center) \
			- (v_dot(ray->direction, cylinder.vNormal) \
			* v_dot(orig_to_center, cylinder.vNormal)));
	abc.z = v_dot(orig_to_center, orig_to_center) \
			- pow(v_dot(orig_to_center, cylinder.vNormal), 2) - pow(radius, 2);
	return (abc);
}

int	set_hp_info(float *hit_param, float height, float *hp_info)
{
	if ((hit_param[2] < height && hit_param[3] > 0) \
			|| (hit_param[3] < height && hit_param[2] > 0))
	{
		if (hit_param[2] < height && hit_param[2] > 0)
		{
			hp_info[0] = hit_param[0];
			hp_info[1] = hit_param[2];
			return (1);
		}
		else
		{
			hp_info[0] = hit_param[1];
			hp_info[1] = hit_param[3];
			return (1);
		}
	}
	hp_info[0] = 0;
	return (0);
}

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
int	test_cylinder(t_px *ray, t_object cylinder, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cylinder.pOrigin);
	abc = get_abc_cyl(ray, orig_to_center, cylinder);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cylinder.vNormal) * hit_param[0]) \
				+ v_dot(orig_to_center, cylinder.vNormal);
	hit_param[3] = (v_dot(ray->direction, cylinder.vNormal) * hit_param[1]) \
				+ v_dot(orig_to_center, cylinder.vNormal);
	if (hit_param[0] < 0)
	{
		hit_param[0] = hit_param[1];
		if (hit_param[0] < 0)
			return (0);
	}
	return(set_hp_info(hit_param, cylinder.height, hp_info));
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
	else if (v_magnitude(v_subtract(px->hitpoint, cy.pOrigin)) < (cy.diameter * 0.5))
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

t_xyz	get_uvcoord_cy(t_object cy, t_px px)
{
	t_xyz		axis_hp;
	t_xyz		unit;
	float		u;
	float		v;

	axis_hp = v_add(cy.pOrigin, v_multiply(cy.vNormal, px.hit_height));
	unit = v_subtract(px.hitpoint, axis_hp);
	u = atan2(unit.z, unit.x);
	v = px.hit_height;
	return (v_create(u, v, 0));
}

t_xyz	norm_uvcoord_cy(t_object cy, t_xyz uv)
{
	uv.x = (uv.x + M_PI) / (2 * M_PI);
	uv.y = 1 - (uv.y/cy.height);
	return (uv);
}

/**
 * @brief Get the color of the object by calculating uv coordinates.
 * for texture pixel color the uv coordinates are normalized 
 * 
 * @param object 
 * @param px 
 * @return int 
 */
int	get_color_cylinder(t_object object, t_px px)
{
	t_xyz	uv;
	
	uv = get_uvcoord_cy(object, px);
	if (object.text)
		px.color = get_text_pxcolor(&px, object.text, norm_uvcoord_cy(object, uv));
	// if (object.text_proc)
	// 	px.color = map_procedure(px, get_uvcoord_cy(object, px));
	return (px.color);
}


