/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refl_refr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:14:06 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/16 16:14:26 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	blend_color(int c1, int c2, float fact_c1)
{
	float	r;
	float	g;
	float	b;

	if (fact_c1 == 1)
		return (c1);
	if (fact_c1 == 0)
		return (c2);
	r = ((c1 >> 24) & 0xFF) * fact_c1;
	g = ((c1 >> 16) & 0xFF) * fact_c1;
	b = ((c1 >> 8) & 0xFF) * fact_c1;
	r += ((c2 >> 24) & 0xFF) * (1 - fact_c1);
	g += ((c2 >> 16) & 0xFF) * (1 - fact_c1);
	b += ((c2 >> 8) & 0xFF) * (1 - fact_c1);
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | 255);
}

t_px	*reflection(t_px *px, t_scene *scene)
{
	t_px	*refl_ray;

	refl_ray = ft_calloc(1, sizeof(t_px));
	if (!refl_ray)
		exit_error(ERROR_MEM, NULL, scene);
	refl_ray->refl_count = px->refl_count + 1;
	refl_ray->transp_count = px->transp_count;
	refl_ray->cam_origin = \
			v_add(px->hitpoint, px->surface_normal);
	refl_ray->direction = reflect_ray(px->surface_normal, px->direction);
	trace_ray(refl_ray, scene);
	if (refl_ray->hitobject)
		get_pixel_data(refl_ray, scene);
	else
		refl_ray->color = 255;
	return (refl_ray);
}

t_px	*refraction(t_px *px, t_scene *scene)
{
	t_px	*rfr_ray;

	rfr_ray = ft_calloc(1, sizeof(t_px));
	if (!rfr_ray)
		exit_error(ERROR_MEM, NULL, scene);
	rfr_ray->transp_count = px->transp_count + 1;
	rfr_ray->refl_count = px->refl_count;
	rfr_ray->cam_origin = v_add(px->hitpoint, \
				v_multiply(px->direction, SHADOW_BIAS));
	rfr_ray->direction = refract_ray(px, px->surface_normal);
	trace_ray(rfr_ray, scene);
	if (rfr_ray->hitobject)
		get_pixel_data(rfr_ray, scene);
	else
		rfr_ray->color = 255;
	return (rfr_ray);
}

/**
 * @brief function that processes reflection and refraction at hitpoint
 * 
 * @param px 
 * @param scene 
 */
void	light_transport(t_px *px, t_scene *scene)
{
	t_px	*refl_ray;
	t_px	*refr_ray;

	refl_ray = NULL;
	refr_ray = NULL;
	if (px->hitobject->refl && px->refl_count < scene->max_reflect)
		refl_ray = reflection(px, scene);
	if (px->hitobject->transp && px->transp_count < MAX_REFRACT)
		refr_ray = refraction(px, scene);
	if (refr_ray)
	{
		px->rfr_color = get_color(refr_ray, scene); 
		free(refr_ray); 
	}
	if (refl_ray)
	{
		px->refl_color = get_color(refl_ray, scene);
		free(refl_ray);
	}
}
