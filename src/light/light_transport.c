/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   light_transport.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 09:21:47 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/12 22:26:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int		blend_color(int c1, int c2, float fact_c1)
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
	b = ((c1 >> 8) & 0xFF)  * fact_c1;
	r += ((c2 >> 24) & 0xFF) * (1 - fact_c1);
	g += ((c2 >> 16) & 0xFF) * (1 - fact_c1);
	b += ((c2 >> 8) & 0xFF)  * (1 - fact_c1);
	return ((int)r << 24 | (int)g << 16 | (int)b << 8 | 255);
}

void	get_reflection_ray(t_px *px, t_px *refl_ray, t_scene *scene)
{
	float	dot;

	refl_ray->cam_origin = \
			v_add(px->hitpoint, px->surface_normal);
	dot = v_dot(px->direction, px->surface_normal);
	refl_ray->direction = v_subtract(px->direction, v_multiply(px->surface_normal, (2 * dot)));
	trace_ray(refl_ray, scene);
}

void	get_refraction_ray(t_px *px, t_px *refr_ray, t_scene *scene)
{
	float	refr;
	float	dot;
	float	root;
	t_xyz	direction;

	refr = 1 / px->hitobject->refr;
	dot = v_dot(px->direction, px->surface_normal);
	root = sqrt(1 - refr * refr * (1 - dot * dot));
	direction = v_multiply(px->surface_normal, refr * dot - root);
	direction = v_add(direction, v_multiply(px->direction, refr));
	refr_ray->cam_origin = v_multiply(px->hitpoint, 0.01);
	refr_ray->direction = v_normalize(direction);
	trace_ray(refr_ray, scene);
	// ft_printf("after trace refraction, hp:%p\n", refr_ray->hitpoint);
}

int	get_pixel_data_transport(t_px	*px, t_scene *scene, t_px *ray, int *count)
{
	int						color;
	static t_surface_data	*surface_data[4] = \
		{get_sphere_surface_data, get_plane_surface_data, \
		get_cylinder_surface_data, get_cone_surface_data};

	(void)px;
	if (ray->hitobject != NULL)
	{
		surface_data[ray->hitobject->id](ray->hitobject, ray);
		get_uv(ray, scene);
		map_texture(ray);
		map_procedure(ray);
		map_normal(ray);
		if ((ray->hitobject->refl && *count < REFL_DEPT))
			light_transport(ray, scene, count);
		loop_lights(scene, ray);
		color = get_color(ray, scene);
	}
	else
		color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	return (color);
}

void	light_transport(t_px *px, t_scene *scene, int *count)
{
	t_px	*refl_ray;
	t_px	*refr_ray;
	int		color1;
	int		color2;
	
	color1 = px->color;
	color2 = px->color;
	if (px->hitobject->refl && *count < REFL_DEPT)
	{
		*count += 1;
		refl_ray = calloc(1, sizeof(t_px));
		get_reflection_ray(px, refl_ray, scene);
		if (!(refl_ray->hitobject && refl_ray->hitobject->transp))
			color1 = get_pixel_data_transport(px, scene, refl_ray, count);
		else
		{
			px->hitobject = refl_ray->hitobject;
			light_transport(px, scene, count);
			color2 = refl_ray->color;
			color1 = blend_color(color1, color2, px->hitobject->refl);
		}
		free(refl_ray);
	}
	if (px->hitobject->transp && px->hitobject->refl != 1)
	{
		refr_ray = calloc(1, sizeof(t_px));
		get_refraction_ray(px, refr_ray, scene);
		color2 = get_pixel_data_transport(px, scene, refr_ray, count);
		free(refr_ray);
	}
	px->color = blend_color(color1, color2, px->hitobject->refl);
}
