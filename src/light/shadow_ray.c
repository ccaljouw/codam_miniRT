/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:58:06 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/06 00:26:07 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	trace_shadow(t_px *px, t_scene *s)
{
	float				hp[2];
	static t_hit_test	*hit_test[4] = {test_sphere, test_plane, test_cylinder, test_cone};
	t_list				*objects;
	t_object			*object;

	objects = s->objects;
	ft_bzero(hp, sizeof(float) * 2);
	while (objects)
	{
		object = (t_object *)objects->content;
		if (hit_test[object->id](px, *object, hp))
		{
			if (px->hit_distance > hp[0])
			{
				px->hitobject = object;
				px->hit_distance = hp[0];
				return (1);
			}
		}
		objects = objects->next;
	}
	return (0);
}

float	get_shadow_ray(t_px *shadow_ray, t_light *light, t_px *px)
{
	float	light_radius;

	shadow_ray->cam_origin = \
			v_add(px->hitpoint, v_multiply(px->surface_normal, SHADOW_BIAS));
	shadow_ray->direction = v_subtract(light->origin, shadow_ray->cam_origin);
	light_radius = v_square_of_self(shadow_ray->direction);
	shadow_ray->hit_distance = sqrtf(light_radius);
	shadow_ray->direction.x /= shadow_ray->hit_distance ;
	shadow_ray->direction.y /= shadow_ray->hit_distance ;
	shadow_ray->direction.z /= shadow_ray->hit_distance ;
	return (light_radius);
}

t_xyz	reflect_ray(t_xyz normal, t_xyz angle)
{
	return (v_subtract(angle, \
			v_multiply(v_multiply(normal, v_dot(normal, angle)), 2)));
}

void	diffuse(t_light *light, t_px *px, t_px *shadow_ray, float light_radius)
{
	t_xyz	ratio;

	ratio = v_divide(light->rgb_ratios, \
										(4 * M_PI * light_radius));
	ratio = v_multiply(ratio, LIGHT_BOOST);
	ratio = v_multiply(ratio, \
				ft_fmax(0.0, v_dot(shadow_ray->direction, px->surface_normal)));
	ratio = v_multiply(ratio, px->hitobject->albedo);
	px->diffuse = v_add(px->diffuse, ratio);
}

void	specular(t_light *light, t_px *shadow_ray, t_px *px)
{
	t_xyz	reflect;
	t_xyz	ratio;

	reflect = reflect_ray(px->surface_normal, shadow_ray->direction);
	ratio = v_multiply(light->rgb_ratios, \
			powf(ft_fmax(0.0, v_dot(reflect, px->direction)), \
								px->hitobject->specular_size));
	ratio = v_multiply(ratio, px->hitobject->specular_weight);
	px->specular = v_add(px->specular, ratio);
}

void	trace_light(t_light *light, t_px *px, t_scene *scene)
{
	t_px	shadow_ray;
	float	light_radius;

	ft_bzero(&shadow_ray, sizeof(shadow_ray));
	light_radius = get_shadow_ray(&shadow_ray, light, px);
	if (trace_shadow(&shadow_ray, scene))
		return ;
	diffuse(light, px, &shadow_ray, light_radius);
	specular(light, &shadow_ray, px);
}


void	loop_lights(t_scene *scene, t_px *px)
{
	t_list	*lights;

	px->diffuse = v_create(0, 0, 0);
	lights = scene->lights;
	while (lights)
	{
		trace_light((t_light *)lights->content, px, scene);
		lights = lights->next;
	}
}
