/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_types.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 23:24:44 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/13 16:35:30 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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

static t_xyz	reflect_ray(t_xyz normal, t_xyz angle)
{
	return (v_subtract(angle, \
			v_multiply(v_multiply(normal, v_dot(normal, angle)), 2)));
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

