/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/04 10:40:36 by cariencaljo   ########   odam.nl         */
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

t_xyz	get_uvcoord_pl(t_object pl, t_px px)
{
	t_xyz		uv;
	
	(void)pl;
	// unit = v_add(px.hitpoint, v_multiply(px.surface_normal, SHADOW_BIAS));
	uv = v_add(px.cam_origin, v_multiply(px.direction, px.hit_distance + SHADOW_BIAS));
	// uv.y = pl.text->height;
	return (uv);
}

t_xyz	norm_uvcoord_pl(t_object pl, t_xyz uv) // niet nodig?
{
	(void)pl;
	v_normalizep(&uv);
	if (uv.y < 0) // should by hp.x
		uv.y += 1;
	uv.x = 1 - (uv.x / 1);
	uv.y = uv.y / pl.text->height;
	return (uv);
}

