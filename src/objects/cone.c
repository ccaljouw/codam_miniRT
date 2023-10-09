/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:23:25 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/09 22:07:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int		set_hp_info(float *hit_param, float height, float *hp_info);

/**
 * @brief Get abc cone
 * 		NB: the a_ha_ht vector is the angle, half angle and hypotenuse, 
 * 		shortened because the norme says its more legible that way.
 * 
 * @param ray 
 * @param cone 
 * @return t_xyz 
 */
t_xyz	get_abc_cone(t_px *ray, t_object cone)
{
	t_xyz	abc;
	t_xyz	d;
	t_xyz	x;
	t_xyz	v;
	t_xyz	a_ha_ht;

	a_ha_ht.z = sqrt(pow(cone.diameter * 0.5, 2) + pow(cone.height * 0.5, 2));
	a_ha_ht.x = acos((cone.height * 0.5) / a_ha_ht.z);
	a_ha_ht.y = 1 + (a_ha_ht.x * 0.5) * (a_ha_ht.x * 0.5);
	d = ray->direction;
	x = v_subtract(ray->cam_origin, cone.p_origin);
	v = v_normalize(cone.v_normal);
	abc.x = v_dot(d, d) - (a_ha_ht.y * pow(v_dot(d, v), 2));
	abc.y = 2 * (v_dot(d, x) - (a_ha_ht.y * v_dot(d, v) * v_dot(x, v)));
	abc.z = v_dot(x, x) - ((a_ha_ht.y * pow(v_dot(x, v), 2)));
	return (abc);
}

int	test_cone(t_px *ray, t_object cone, float *hp_info)
{
	t_xyz	abc;
	t_xyz	orig_to_center;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cone.p_origin);
	abc = get_abc_cone(ray, cone);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cone.v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cone.v_normal);
	hit_param[3] = (v_dot(ray->direction, cone.v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cone.v_normal);
	return (set_hp_info(hit_param, cone.height, hp_info));
}

int	get_cone_surface_data(t_object co, t_px *px)
{
	t_xyz		hit_to_center;
	float		a;
	float		angle;
	float		hypotenuse;

	hypotenuse = sqrt(pow(co.diameter * 0.5, 2) + pow(co.height * 0.5, 2));
	angle = acos((co.height * 0.5) / hypotenuse);
	a = px->hit_height * (angle * 0.5) * (angle * 0.5);
	px->hitpoint = v_add(px->cam_origin, \
				v_multiply(px->direction, px->hit_distance));
	hit_to_center = v_subtract(px->hitpoint, co.p_origin);
	px->surface_normal = \
			v_subtract(hit_to_center, v_multiply(co.v_normal, px->hit_height));
	px->surface_normal = \
			v_subtract(px->surface_normal, v_multiply(co.v_normal, a));
	v_normalizep(&px->surface_normal);
	px->facing_ratio = fabsf(v_dot(px->surface_normal, px->direction));
	return (px->color);
}

t_xyz	get_uvcoord_co(t_object co, t_px px, t_scene *scene)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	z_plane;
	t_xyz	v;
	t_xyz	hp_in_object_space;

	x_plane = v_cross(co.v_normal, scene->camera->orientation_v);
	z_plane = v_cross(co.v_normal, x_plane);

	v = v_subtract(co.p_origin, px.hitpoint);
	hp_in_object_space.y = v_dot(co.v_normal, v);
	v_normalizep(&v);
	hp_in_object_space.x = v_dot(x_plane, v);
	hp_in_object_space.z = v_dot(z_plane, v);
	m44_multiply_vec3_dir(co.rotate_matrix, hp_in_object_space, \
												&hp_in_object_space);
	uv.x = (atan2(hp_in_object_space.x, hp_in_object_space.z) \
												/ (2 * M_PI)) + 0.5;
	uv.y = (hp_in_object_space.y / co.height) + 1;
	return (uv);
}
