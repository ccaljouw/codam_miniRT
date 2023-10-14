/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   refl_refr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/14 16:14:06 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/14 17:37:20 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <miniRT.h>

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

int	reflection(t_px *px, t_scene *scene)
{
	float	dot;
	t_px	*refl_ray;
	int		color;
	
	refl_ray = calloc(1, sizeof(t_px));
	if (!refl_ray)
		exit_error(ERROR_MEM, NULL, scene);
	refl_ray->cam_origin = \
			v_add(px->hitpoint, px->surface_normal);
	dot = v_dot(px->direction, px->surface_normal);
	refl_ray->direction = v_subtract(px->direction, \
				v_multiply(px->surface_normal, (2 * dot)));
	trace_ray(refl_ray, scene);
	if (refl_ray->hit_distance)
		color = get_pixel_data(refl_ray, scene);
	else
		color = 255;
	free(refl_ray);
	return (color);
}

int	refraction(t_px *px, t_scene *scene)
{
	float	refr;
	float	dot;
	float	root;
	t_px	*refr_ray;
	int		color;

	color = 255;
	refr_ray = calloc(1, sizeof(t_px));
	if (!refr_ray)
		exit_error(ERROR_MEM, NULL, scene);
	refr = 1 / px->hitobject->refr;
	dot = v_dot(px->direction, px->surface_normal);
	root = sqrt(1 - refr * refr * (1 - dot * dot));
	refr_ray->cam_origin = v_multiply(px->hitpoint, 0.01);
	refr_ray->direction = v_multiply(px->surface_normal, refr * dot - root);
	refr_ray->direction = v_add(refr_ray->direction , \
									v_multiply(px->direction, refr));
	refr_ray->direction = v_normalize(refr_ray->direction );
	trace_ray(refr_ray, scene);
	if (refr_ray->hitobject == px->hitobject)
		return (0);
	else if (refr_ray->hitobject)
		color = get_pixel_data(refr_ray, scene);
	free(refr_ray);
	return (color);
}

/**
 * @brief function that processes reflection and refraction at hitpoint
 * 
 * @param px 
 * @param scene 
 */
void	light_transport(t_px *px, t_scene *scene)
{
	int	color_refl;
	int	color_refr;

	color_refl = 0;
	color_refr = 0;
	if ((!px->hitobject->refl && !px->hitobject->transp) \
							|| px->refl_count > REFL_DEPT)
		return ;
	px->refl_count++;
	if (px->hitobject->refl)
		color_refl = reflection(px, scene);
	if (px->hitobject->transp)
		color_refr = refraction(px, scene);
	if (color_refl && color_refr)
		px->color = blend_color(color_refl, color_refr, px->hitobject->refl);
	else if (color_refl)
		px->color = color_refl;
	else
		px->color = color_refr;
}
