/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:58:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/26 12:54:02 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

#define SHADOW_BIAS 0.001

float	v_square_of_self(t_xyz a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}


float	get_shadow_ray(t_px *shadow_ray, t_light light, t_px *px, t_scene scene)
{
	float	light_radius;

	(void)scene;
	ft_bzero(shadow_ray, sizeof(shadow_ray));
	shadow_ray->cam_origin = v_add(px->hitpoint, v_multiply(px->surface_normal, SHADOW_BIAS));
	shadow_ray->direction = v_subtract(light.origin, shadow_ray->cam_origin);
	light_radius = v_square_of_self(shadow_ray->direction);
	shadow_ray->hit_distance = sqrtf(light_radius);
	shadow_ray->direction = v_divide(shadow_ray->direction, shadow_ray->hit_distance);
	return (light_radius);
}

int	trace_shadow(t_px *shadow_ray, t_scene s)
{
	float				hp_distance;
	static t_hit_test	*hit_test[3] = {test_sphere, test_plane, test_cylinder};
	t_list				*objects;
	t_object			*object;

	objects = s.objects;
	while (objects)
	{
		object = (t_object *)objects->content;
		if (hit_test[object->id](*shadow_ray, *object, &hp_distance))
		{
			if (object->id == SP)
				ft_printf("imma call %i function\n", object->id);
			if (shadow_ray->hit_distance > hp_distance)
				return (1);
		}
		objects = objects->next;
	}
	return (0);
}

void	loop_lights(t_px *px, t_scene scene)
{
	t_light	*light;
	t_px	shadow_ray;
	float	light_radius;
	float	fallof;

	px->ratios = v_create(0, 0, 0);
	if (!scene.lights)
		return ;
	// while (scene.lights)
	// {
		light = (t_light *)scene.lights->content;
		light_radius = get_shadow_ray(&shadow_ray, *light, px, scene);
		fallof = (light->brightness / (4 * M_PI * light_radius) * 1000);
		if (trace_shadow(&shadow_ray, scene))
			return ;
		px->ratios = v_add(px->ratios, v_multiply(light->rgb_ratios, fallof));
		px->ratios = v_multiply(px->ratios, v_dot(shadow_ray.direction, px->surface_normal));
		// scene.lights = scene.lights->next;
	// }
}
