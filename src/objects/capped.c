/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capped.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:31:28 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/19 23:22:09 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_cap(t_object *object, t_px *ray, t_xyz origin, float *hp_info)
{
	float	angle;
	float	dist;
	t_xyz	hp;
	t_xyz	orig_to_center;

	angle = v_dot(object->v_normal, ray->direction);
	if (fabs(angle) < EPSILON)
		return (0);
	orig_to_center = v_subtract(origin, ray->cam_origin);
	dist = (v_dot(object->v_normal, orig_to_center) / angle) + SHADOW_BIAS;
	if (dist < 0)
		return (0);
	hp = v_add(ray->cam_origin, v_multiply(ray->direction, dist));
	if (fabs(v_magnitude(v_subtract(hp, origin))) < (object->diameter * 0.5))
	{
		if (dist < hp_info[0] || hp_info[0] == 0)
		{
			ray->cap = 1;
			hp_info[0] = dist;
		}
		return (1);
	}
	return (0);
}

int	test_capped_cylinder(t_px *ray, t_object *cyl, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	t_xyz	top;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cyl->p_origin);
	abc = get_abc_cyl(ray, orig_to_center, *cyl);
	top = v_add(cyl->p_origin, v_multiply(cyl->v_normal, cyl->height));
	get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]);
	hit_param[2] = (v_dot(ray->direction, cyl->v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cyl->v_normal);
	hit_param[3] = (v_dot(ray->direction, cyl->v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cyl->v_normal);
	set_hp_info(hit_param, cyl->height, hp_info);
	if (test_cap(cyl, ray, cyl->p_origin, hp_info))
		hp_info[1] = 0;
	if (test_cap(cyl, ray, top, hp_info))
		hp_info[1] = cyl->height;
	if (hp_info[0])
		return (1);
	return (0);
}

int	test_capped_cone(t_px *ray, t_object *cone, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	t_xyz	top;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cone->p_origin);
	abc = get_abc_cone(ray, cone);
	top = v_add(cone->p_origin, v_multiply(cone->v_normal, cone->height));
	get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]);
	hit_param[2] = (v_dot(ray->direction, cone->v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cone->v_normal);
	hit_param[3] = (v_dot(ray->direction, cone->v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cone->v_normal);
	set_hp_info(hit_param, cone->height, hp_info);
	if (test_cap(cone, ray, top, hp_info))
		hp_info[1] = cone->height;
	if (hp_info[0])
		return (1);
	return (0);
}
