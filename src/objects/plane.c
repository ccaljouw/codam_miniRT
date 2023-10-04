/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/04 18:05:53 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_plane(t_px *ray, t_object plane, float *hp_info)
{
	float	denominator;
	// t_xyz	uv;
	t_xyz	orig_to_center;

	denominator = v_dot(plane.vNormal, ray->direction);
	if (fabsf(denominator) > EPSILON)
	{
		orig_to_center = v_subtract(plane.pOrigin, ray->cam_origin);
		hp_info[0] = v_dot(plane.vNormal, orig_to_center) / denominator;
		// hp_info[0] = ray->cam_origin.y / -denominator;
		if (hp_info[0] > 0)
		{
			// uv = v_add(ray->cam_origin, v_multiply(ray->direction, hp_info[0]));
			// if (fabs(v_magnitude(uv)) < 1.0)
				return (1);
		}
	}
	hp_info[0] = 0;
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
		px->surface_normal = v_multiply(plane.vNormal, 1);
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
	uv.y = px.hit_distance;
	return (uv);
}

t_xyz	norm_uvcoord_pl(t_object pl, t_xyz uv)
{
	(void)pl;
	v_normalizep(&uv);
	uv.x = (uv.x + 1) * 0.5;
	uv.y = (uv.y + 1) * 0.5;
	return (uv);
}

