/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/02 09:37:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_plane(t_px *ray, t_object plane, float *hp_info)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(plane.vNormal, ray->direction);
	if (fabsf(denominator) > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(plane.pOrigin, ray->cam_origin);
		hp_info[0] = v_dot(plane.vNormal, diff_ray0_plane0) / denominator;
		if (hp_info[0] > 0)
			return (1);
	}
	return (0);
}

int	get_plane_surface_data(t_object plane, t_px *px)
{
	px->hitpoint =  v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	px->facing_ratio = v_dot(plane.vNormal, px->direction);
	if (px->facing_ratio > 0)
		px->surface_normal = v_multiply(plane.vNormal, -1);
	else
	{
		px->surface_normal = plane.vNormal;
		px->facing_ratio *= -1;
	}
	return (px->color);
}

int	get_color_plane(t_object object, t_px px)
{
	t_xyz		unit;
	float		u;
	float		v;

	if (object.text)
	{		
		unit = v_subtract(px.hitpoint, px.cam_origin);
		v_normalizep(&unit);
		u = unit.x;
		v = unit.y;
		u = (u + 1.0) * 0.5;
		v = (v + 1.0) * 0.5;
		px.color = get_text_pxcolor(object.text, u, v);
	}
	if (object.text_proc == 1)
	{
		unit = v_add(px.hitpoint, v_multiply(px.surface_normal, SHADOW_BIAS));
		px.color = checkered(px, unit.x, unit.y, unit.z);
	}
	return (px.color);
}

