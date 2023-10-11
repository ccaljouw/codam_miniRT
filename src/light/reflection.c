/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reflection.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 09:21:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/11 13:49:41 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

t_px	get_reflection_ray(t_px *px)
{
	t_px	refl_ray;

	refl_ray.cam_origin = \
			v_add(px->hitpoint, v_multiply(px->surface_normal, SHADOW_BIAS));
	refl_ray.direction = v_add(px->direction, px->surface_normal);
	return (refl_ray);
}

int	get_pixel_data_reflection(t_px	*px, t_scene *scene)
{
	int						color;
	t_px					refl_ray;
	static t_surface_data	*surface_data[4] = \
		{get_sphere_surface_data, get_plane_surface_data, \
		get_cylinder_surface_data, get_cone_surface_data};

	if (!px->hitobject)
		return (0 << 24 | 0 << 16 | 0<< 8 | 255);
	ft_bzero(&refl_ray, sizeof(t_px));
	px->refl_count++;
	refl_ray = get_reflection_ray(px);
	trace_ray(&refl_ray, scene);
	if (refl_ray.hitobject != NULL)
	{
		surface_data[refl_ray.hitobject->id](*refl_ray.hitobject, &refl_ray);
		get_uv(&refl_ray, scene);
		map_texture(&refl_ray);
		map_procedure(&refl_ray);
		map_normal(&refl_ray);
		if (refl_ray.hitobject->refl && px->refl_count < REFL_DEPT)
			color = get_pixel_data_reflection(&refl_ray, scene);
		else
		{
			loop_lights(scene, &refl_ray);
			color = get_color(&refl_ray, scene);
		}
		return (color);
	}
	return (0 << 24 | 0 << 16 | 0 << 8 | 255);
}
