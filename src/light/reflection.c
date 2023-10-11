/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 09:21:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/11 21:25:24 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int		blend_color(int c1, int c2, int fact_b)
{
	int						r;
	int						g;
	int						b;
	
	r = ((c1 >> 24) & 0xFF) + (((c2 >> 24) & 0xFF) * fact_b);
	g = ((c1 >> 16) & 0xFF) + (((c2 >> 16) & 0xFF) * fact_b);
	b = ((c1 >> 8) & 0xFF) + (((c2 >> 8) & 0xFF)* fact_b);
	r /= (1 + fact_b);
	g /= (1 + fact_b);
	b /= (1 + fact_b);
	return (r << 24 | g << 16 | b << 8 | 255);
}

void	get_reflection_ray(t_px *px, t_px *refl_ray)
{
	float	dot;

	refl_ray->cam_origin = \
			v_add(px->hitpoint, v_multiply(px->surface_normal, SHADOW_BIAS));
	dot = v_dot(px->direction, px->surface_normal);
	refl_ray->direction = v_subtract(px->direction, v_multiply(px->surface_normal, (2 * dot)));
}

int	get_pixel_data_reflection(t_px	*px, t_scene *scene)
{
	int						color;
	t_px					*refl_ray;
	static t_surface_data	*surface_data[4] = \
		{get_sphere_surface_data, get_plane_surface_data, \
		get_cylinder_surface_data, get_cone_surface_data};

	refl_ray = calloc(1, sizeof(t_px));
	color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	if (!px->hitobject)
		return (0 << 24 | 0 << 16 | 0<< 8 | 255);
	px->refl_count++;
	get_reflection_ray(px, refl_ray);
	trace_ray(refl_ray, scene);
	if (refl_ray->hitobject != NULL)
	{
		surface_data[refl_ray->hitobject->id](*refl_ray->hitobject, refl_ray);
		get_uv(refl_ray, scene);
		map_texture(refl_ray);
		map_procedure(refl_ray);
		map_normal(refl_ray);
		if (refl_ray->hitobject->refl && px->refl_count < REFL_DEPT)
			color = get_pixel_data_reflection(refl_ray, scene);
		else
		{
			loop_lights(scene, refl_ray);
			color = get_color(refl_ray, scene);
		}
	}
	free(refl_ray);
	return (blend_color(px->color, color, px->hitobject->refl));
}
