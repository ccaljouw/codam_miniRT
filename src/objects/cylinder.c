/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:26:44 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/09 21:59:09 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_xyz	get_abc_cyl(t_px *ray, t_xyz orig_to_center, t_object cylinder)
{
	t_xyz	abc;
	float	radius;

	radius = cylinder.diameter * 0.5;
	abc.x = v_dot(ray->direction, ray->direction) \
			- pow(v_dot(ray->direction, cylinder.v_normal), 2);
	abc.y = 2 * (v_dot(ray->direction, orig_to_center) \
			- (v_dot(ray->direction, cylinder.v_normal) \
			* v_dot(orig_to_center, cylinder.v_normal)));
	abc.z = v_dot(orig_to_center, orig_to_center) \
			- pow(v_dot(orig_to_center, cylinder.v_normal), 2) - pow(radius, 2);
	return (abc);
}

int	set_hp_info(float *hit_param, float height, float *hp_info)
{
	if (hit_param[0] > 0 && hit_param[2] < height && hit_param[2] > 0)
	{
		hp_info[0] = hit_param[0];
		hp_info[1] = hit_param[2];
		return (1);
	}
	else if (hit_param[1] > 0 && hit_param[3] < height && hit_param[3] > 0)
	{
		hp_info[0] = hit_param[1];
		hp_info[1] = hit_param[3];
		return (1);
	}
	hp_info[0] = 0;
	return (0);
}

/**
 * @brief Find the two hitpoints on the cylinder (it can be the same 
 * point twice). The calculation is similar to the sphere hit test 
 * but calculated for the radius on each point from the axis that falls
 * between origin and origin + height. 
 * calculate two m values (a scalar that determines the closest point on the 
 * axis to the hit point) and test whether they fall in the range of [0,maxm].
 * 
 * @param ray 
 * @param cylinder 
 * @param hp_info (float[2]) hp_info[0] = hit distance, hp_info[1] = hit height
 * @param hit_param (float[4]) [0]:distance1 [1]:distance2 [2]:height1, 
 * 					[3]:height2
 * @return int 
 */
int	test_cylinder(t_px *ray, t_object cylinder, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cylinder.p_origin);
	abc = get_abc_cyl(ray, orig_to_center, cylinder);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cylinder.v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cylinder.v_normal);
	hit_param[3] = (v_dot(ray->direction, cylinder.v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cylinder.v_normal);
	return (set_hp_info(hit_param, cylinder.height, hp_info));
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

	px->hitpoint = \
			v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	top = v_add(px->hitpoint, v_multiply(cy.v_normal, cy.height));
	if (v_magnitude(v_subtract(px->hitpoint, top)) < (cy.diameter * 0.5))
		px->surface_normal = cy.v_normal;
	else if (v_magnitude(v_subtract(px->hitpoint, cy.p_origin)) \
					< (cy.diameter * 0.5))
		px->surface_normal = v_multiply(cy.v_normal, -1);
	else
	{
		v = v_subtract(cy.p_origin, px->hitpoint);
		px->surface_normal = v_cross(v, cy.v_normal);
		px->surface_normal = v_cross(px->surface_normal, cy.v_normal);
		v_normalizep(&px->surface_normal);
	}
	px->facing_ratio = fabsf(v_dot(px->surface_normal, px->direction));
	return (px->color);
}

t_xyz	get_uvcoord_cy(t_object cy, t_px px, t_scene *scene)
{
	// t_xyz		axis_hp;
	t_xyz		uv;
	// t_xyz		new_normal;

	(void)scene;
	t_xyz	ex;
	t_xyz	ez;
	t_xyz	v;
	t_xyz	xyz;

	ex = v_cross(cy.v_normal, scene->camera->orientation_v);
	ez = v_cross(cy.v_normal, ex);

	v = v_subtract(cy.p_origin, px.hitpoint);
	xyz.y = v_dot(cy.v_normal, v);
	v_normalizep(&v);
	
	xyz.x = v_dot(ex, v);
	xyz.z = v_dot(ez, v);
		m44_multiply_vec3_dir(cy.rotate_matrix, xyz, &xyz);
	uv.x = (atan2(xyz.x, xyz.z) / (2 * M_PI)) + 0.5;
	uv.y = (xyz.y / cy.height) + 1;
	// uv.z = 0;
	// v_normalizep(&uv);


	// m44_rota
	// axis_hp = v_add(cy.p_origin, v_multiply(cy.v_normal, px.hit_height));
	// // ft_printf("vnormal: ");
	// // print_vector(cy.v_normal);
	// uv = v_subtract(px.hitpoint, axis_hp);
	// // v_normalizep(&uv);
	// // ft_printf("before: ");
	// // print_vector(uv);
	// // m44_multiply_vec3_dir(cy.rotate_matrix, uv, &uv); 
	// // ft_printf("before: ");
	// // print_vector(uv);
	// // if (uv.z == 0)
	// // 	uv.z += .1;
	// // v_normalizep(&uv);
	// uv.x = 0.5 + (atan2(uv.z, uv.x) / (2 * M_PI)) ;
	// // uv.x = atan2()
	// uv.y = 1 - (px.hit_height / cy.height);
	// ft_printf("after: ");
	// print_vector(uv);
	// uv.z = 100;
	// v_normalizep(&uv);
	return (uv);
}
