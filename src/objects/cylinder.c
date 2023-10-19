/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:26:44 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/19 13:02:06 by ccaljouw         ###   ########.fr       */
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
int	test_cylinder(t_px *ray, t_object *cylinder, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cylinder->p_origin);
	abc = get_abc_cyl(ray, orig_to_center, *cylinder);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cylinder->v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cylinder->v_normal);
	hit_param[3] = (v_dot(ray->direction, cylinder->v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cylinder->v_normal);
	return (set_hp_info(hit_param, cylinder->height, hp_info));
}

/**
 * @brief 
 * 
 * @param hp_distance 
 * @param s 
 * @param px 
 * @return float 
 */
int	get_cylinder_surface_data(t_object *cy, t_px *px)
{
	t_xyz		v;

	px->hitpoint = \
			v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	if (px->cap)
		px->surface_normal = cy->v_normal;
	else
	{
		v = v_subtract(cy->p_origin, px->hitpoint);
		px->surface_normal = v_cross(v, cy->v_normal);
		px->surface_normal = v_cross(px->surface_normal, cy->v_normal);
		v_normalizep(&px->surface_normal);
	}
	px->facing_ratio = v_dot(px->surface_normal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(px->surface_normal, -1);
	else
		px->facing_ratio *= -1;
	return (px->color);
}

t_xyz	get_uvcoord_cy(t_object *cy, t_px *px, t_scene *scene)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	z_plane;
	t_xyz	v;
	t_xyz	hp_in_object_space;

	//fix uv coordinates caps;
	x_plane = v_cross(cy->v_normal, scene->camera->orientation_v);
	z_plane = v_cross(cy->v_normal, x_plane);
	v = v_subtract(cy->p_origin, px->hitpoint);
	hp_in_object_space.y = v_dot(cy->v_normal, v);
	v_normalizep(&v);
	hp_in_object_space.x = v_dot(x_plane, v);
	hp_in_object_space.z = v_dot(z_plane, v);
	m44_multiply_vec3_dir(cy->rotate_matrix, hp_in_object_space, \
												&hp_in_object_space);
	uv.x = (atan2(hp_in_object_space.x, hp_in_object_space.z) \
												/ (2 * M_PI)) + 0.5;
	uv.y = (hp_in_object_space.y / cy->height) + 1;
	return (uv);
}
