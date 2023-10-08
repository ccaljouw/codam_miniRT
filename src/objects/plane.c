/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 11:14:41 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/08 21:27:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	test_plane(t_px *ray, t_object plane, float *hp_info)
{
	float	denominator;
	t_xyz	orig_to_center;

	denominator = v_dot(plane.vNormal, ray->direction);
	if (fabsf(denominator) > EPSILON)
	{
		orig_to_center = v_subtract(plane.pOrigin, ray->cam_origin);
		hp_info[0] = v_dot(plane.vNormal, orig_to_center) / denominator;
		if (hp_info[0] > 0)
			return (1);
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

t_xyz	get_uvcoord_pl(t_object pl, t_px px, t_scene *scene)
{
	t_xyz	uv;
	t_xyz	x_plane;
	t_xyz	y_plane;
	t_xyz	z_plane;
	t_xyz	hp_in_object_space;

	y_plane = pl.vNormal;
	x_plane = v_cross(y_plane, scene->camera->orientation_v);
	z_plane = v_cross(x_plane, y_plane);
	hp_in_object_space = px.hitpoint;
	// hp_in_object_space = v_subtract(px.hitpoint, pl.pOrigin); // weggehaald omdat het een bolling oplevert
	uv.x = v_dot(hp_in_object_space, x_plane);
	uv.y = v_dot(hp_in_object_space, z_plane);
	uv.z = scene->camera->image_height * 0.015;
	v_normalizep(&uv);
	uv.x = ((uv.x + 1.0) * 0.5);
	uv.y =  (uv.y + 1.0) * 0.5;
	uv.z = 0;
	return (uv);
}


