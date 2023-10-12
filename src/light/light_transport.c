/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_transport.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 09:21:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/12 13:19:29 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int		blend_color(int c1, int c2, float fact_c1)
{
	float	r;
	float	g;
	float	b;
	
	r = ((c1 >> 24) & 0xFF) * fact_c1;
	g = ((c1 >> 16) & 0xFF) * fact_c1;
	b = ((c1 >> 8) & 0xFF)  * fact_c1;
	r += ((c2 >> 24) & 0xFF) * (1 - fact_c1);
	g += ((c2 >> 16) & 0xFF) * (1 - fact_c1);
	b += ((c2 >> 8) & 0xFF)  * (1 - fact_c1);
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | 255);
}

void	get_reflection_ray(t_px *px, t_px *refl_ray)
{
	float	dot;

	refl_ray->cam_origin = \
			v_add(px->hitpoint, px->surface_normal);
	dot = v_dot(px->direction, px->surface_normal);
	refl_ray->direction = v_subtract(px->direction, v_multiply(px->surface_normal, (2 * dot)));
}

void	get_refraction_ray(t_px *px, t_px *refl_ray)
{
	float	dot;

	refl_ray->cam_origin = \
			v_add(px->hitpoint, px->surface_normal);
	dot = v_dot(px->direction, px->surface_normal);
	refl_ray->direction = v_subtract(px->direction, v_multiply(px->surface_normal, \
			(2 * dot * px->hitobject->refr)));
}

int	get_pixel_data_transport(t_px	*px, t_scene *scene, t_px *ray)
{
	int						color;
	static t_surface_data	*surface_data[4] = \
		{get_sphere_surface_data, get_plane_surface_data, \
		get_cylinder_surface_data, get_cone_surface_data};

	color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	px->refl_count++;
	trace_ray(ray, scene);
	if (ray->hitobject != NULL)
	{
		surface_data[ray->hitobject->id](ray->hitobject, ray);
		get_uv(ray, scene);
		map_texture(ray);
		map_procedure(ray);
		map_normal(ray);
		if ((ray->hitobject->refl && px->refl_count < REFL_DEPT) \
			|| (ray->hitobject->transp && ray->hitobject->refl != 1))
			light_transport(ray, scene);
		loop_lights(scene, ray);
		color = get_color(ray, scene);
	}
	return (color);
}

void	light_transport(t_px *px, t_scene *scene)
{
	t_px	*refl_ray;
	t_px	*refr_ray;
	int		color1;
	int		color2;
	
	color1 = px->color;
	if (px->hitobject->refl)
	{
		refl_ray = calloc(1, sizeof(t_px));
		get_reflection_ray(px, refl_ray);
		color1 = get_pixel_data_transport(px, scene, refl_ray);
		free(refl_ray);
	}
	if (px->hitobject->transp && px->hitobject->refl != 1)
	{
		refr_ray = calloc(1, sizeof(t_px));
		get_refraction_ray(px, refr_ray);
		color2 = get_pixel_data_transport(px, scene, refr_ray);
		free(refr_ray);
	}
	else
		color2 = px->color;
	px->color = blend_color(color1, color2, px->hitobject->refl);
}
