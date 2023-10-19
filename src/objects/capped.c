/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capped.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:31:28 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/19 22:36:50 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <miniRT.h>

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

int	test_capped_cylinder(t_px *ray, t_object *cylinder, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	t_xyz	top;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cylinder->p_origin);
	abc = get_abc_cyl(ray, orig_to_center, *cylinder);
	top = v_add(cylinder->p_origin, v_multiply(cylinder->v_normal, cylinder->height));
	get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]);
	hit_param[2] = (v_dot(ray->direction, cylinder->v_normal) * hit_param[0]) \
				+ v_dot(orig_to_center, cylinder->v_normal);
	hit_param[3] = (v_dot(ray->direction, cylinder->v_normal) * hit_param[1]) \
				+ v_dot(orig_to_center, cylinder->v_normal);
	set_hp_info(hit_param, cylinder->height, hp_info);	
	if (test_cap(cylinder, ray, cylinder->p_origin, hp_info))
		hp_info[1] = 0;
	if (test_cap(cylinder, ray, top, hp_info))
		hp_info[1] = cylinder->height;
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
	// ft_printf("params: %f %f %f %f\n", hit_param[0], hit_param[1], hit_param[2], hit_param[3]);
	if (test_cap(cone, ray, top, hp_info))
		hp_info[1] = cone->height;
	if (hp_info[0])
		return (1);
	return (0);
}
