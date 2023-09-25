/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:58:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/25 13:36:27 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define SHADOW_BIAS .001

int	trace_shadow(t_px *px, t_scene s);

float	v_square_of_self(t_xyz a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

int	loop_lights(t_scene scene, t_xyz hp_normal, t_xyz hitpoint, t_xyz *ratios, char* caller)
{
	// t_list	*lights;
	t_light	light;
	t_px	shadow_ray;
	float	light_radius;
	float	fallof;
// static int	count_lights = 0;
// static int	count_shadows = 0;
// static	float	biggest_fallof = 0;
// int		sphere = 0;
	// *ratios = v_create(1,1,1);
	// return (0);
	// if (!ft_strcmp("sphere", caller))
	// 	sphere = 1;
	// if (sphere)
	// 	ft_printf("a");
	if (scene.light == NULL)
		return (0);
	(void)caller;
	// ratios = v_create(fr, fr, fr);
	// lights = scene.light;
	// while (lights)
	// {
		// light = *(t_light *)lights->content;
		ft_bzero(&shadow_ray, sizeof(shadow_ray));
		light = *scene.light;
		shadow_ray.cam_origin = v_add(hitpoint, v_multiply(hp_normal, SHADOW_BIAS));
		shadow_ray.direction = v_subtract(light.origin, shadow_ray.cam_origin);
		light_radius = v_square_of_self(shadow_ray.direction);
		shadow_ray.hit_distance = sqrtf(light_radius);
		// if (sphere)
		// 	ft_printf("%f %p", shadow_ray.hit_distance);
		// ft_printf("dist: %f", shadow_ray.hit_distance);
		shadow_ray.direction.x /= shadow_ray.hit_distance ;
		shadow_ray.direction.y /= shadow_ray.hit_distance ;
		shadow_ray.direction.z /= shadow_ray.hit_distance ;
		// v_normalizep(&shadow_ray.direction);
		fallof = ((light.brightness * 10000 / (4 / M_PI * light_radius)));
		// fallof =1;
		// if (fallof > biggest_fallof)
		// {
		// 	// ft_printf("fallof %f * %f\n", fallof, v_dot(hp_normal, shadow_ray.direction));
		// 	biggest_fallof = fallof;
		// }
		// fallof = 0.5;
		// ratios = v_add(ratios, v_multiply)
		if (trace_shadow(&shadow_ray, scene))
		{
			return (0);
		}

		*ratios = v_add(*ratios, v_multiply(light.rgb_ratios, fallof));
		*ratios = v_multiply(*ratios, v_dot(shadow_ray.direction, hp_normal));
		// print_vector(*ratios);
		// lights = lights->next;
	// }
	return (1);
}

int	trace_shadow(t_px *px, t_scene s)
{
	float				hp_distance;
	static t_hit_test	*hit_test[3] = {test_sphere, test_plane, test_cylinder};
	t_list				*objects;
	t_object			*object;

	objects = s.objects;
	while (objects)
	{
		object = (t_object *)objects->content;
		if (hit_test[object->id](*px, *object, &hp_distance))
		{
			if (px->hit_distance > hp_distance)
			{
				px->hitobject = object;
				px->hit_distance = hp_distance;
				return (1);
			}
		}
		objects = objects->next;
	}
	return (0);
}
