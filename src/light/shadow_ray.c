/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:58:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/25 02:57:03 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define SHADOW_BIAS 0.001

int	trace_shadow(t_px *px, t_scene s);

float	v_square_of_self(t_xyz a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}


float	get_shadow_ray(t_px *shadow_ray, t_xyz hitpoint, t_xyz hp_normal, t_scene scene)
{
	t_light	light;
	float	light_radius;

	ft_bzero(shadow_ray, sizeof(shadow_ray));
	light = *scene.light;
	shadow_ray->cam_origin = v_add(hitpoint, v_multiply(hp_normal, SHADOW_BIAS));
	shadow_ray->direction = v_subtract(shadow_ray->cam_origin, light.origin);
	light_radius = v_square_of_self(shadow_ray->direction);
	shadow_ray->hit_distance = sqrt(light_radius);
	shadow_ray->direction.x /= shadow_ray->hit_distance * -1;
	shadow_ray->direction.y /= shadow_ray->hit_distance * -1;
	shadow_ray->direction.z /= shadow_ray->hit_distance * -1;
	return (light_radius);
}


void	loop_lights(t_px *px, t_scene scene)
{
	t_xyz	ratios;
	t_light	light;
	t_px	shadow_ray;
	float	light_radius;
	float	fallof;
	
	static int	count_lights = 0;
	static int	count_shadows = 0;
	static	float	biggest_fallof = 0;
	int		sphere = 0;
	
	if (!scene.light || px->hitobject->id == CY)
		return;
	ratios = v_create(0, 0, 0);
	if (px->hitobject->id == SP)
		sphere = 1;
	light = *scene.light;
	light_radius = get_shadow_ray(&shadow_ray, px->hitpoint, px->surface_normal, scene);
	fallof = (light.brightness / (4 * M_PI * light_radius) * 200);
	if (fallof > biggest_fallof)
		biggest_fallof = fallof;
	if (trace_shadow(&shadow_ray, scene))
	{
		if (!count_shadows)
			count_shadows++;
		return;
	}
	if (!count_lights)
		count_lights++;
	px->ratios = v_add(ratios, v_multiply(light.rgb_ratios, fallof));
}

int	trace_shadow(t_px *px, t_scene s)
{
	float				hp_distance;
	static t_hit_test	*hit_test[3] = {test_sphere, test_plane, test_cylinder};
	t_object			*object;

	object = (t_object *)s.objects->content;
	if (hit_test[object->id](*px, *object, &hp_distance))
	{
		if (px->hit_distance > hp_distance)
		{
			px->hitobject = object;
			px->hit_distance = hp_distance;
			return (1);
		}
	}
	return (0);
}
