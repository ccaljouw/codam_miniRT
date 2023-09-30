/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cone.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 19:23:25 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/30 21:30:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <miniRT.h>

t_xyz	get_abc_cone(t_px *ray, t_xyz orig_to_center, t_object cone, float *hp_info)
{
	t_xyz	abc;
	float	half_angle_corr;
	float	radius;

	/*
	a   = D|D - (1+k*k)*(D|V)^2
	b/2 = D|X - (1+k*k)*(D|V)*(X|V)
	c   = X|X - (1+k*k)*(X|V)^2
	*/
	half_angle_corr = 1 + hp_info[1] * hp_info[1];
	radius = cone.diameter * 0.5;
	abc.x = v_dot(ray->direction, ray->direction) \
			- (half_angle_corr \
			* pow(v_dot(ray->direction, cone.vNormal), 2));
	abc.y = 2 * (v_dot(ray->direction, orig_to_center) \
			- (half_angle_corr  \
			* (v_dot(ray->direction, cone.vNormal)) \
			* v_dot(orig_to_center, cone.vNormal)));
	abc.z = v_dot(orig_to_center, orig_to_center) \
			- (half_angle_corr \
			* pow(v_dot(orig_to_center, cone.vNormal), 2) - pow(radius, 2));
	return (abc);
}

int	test_cone(t_px *ray, t_object cone, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_param[5];

	test_cylinder(ray, cone, hp_info);
	if (hp_info[0])
	{
		orig_to_center = v_subtract(ray->cam_origin, cone.pOrigin);
		hit_param[4] = v_magnitude(v_subtract(orig_to_center, v_multiply(cone.vNormal, hp_info[1]))) / hp_info[1];
		abc = get_abc_cone(ray, orig_to_center, cone, hp_info);
		if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
			return (0);
		if (hit_param[0] < 0)
		{
			hit_param[0] = hit_param[1];
			if (hit_param[0] < 0)
				return (0);
		}
		return (1);
	}
	return (0);
}

int	get_cone_surface_data(t_object co, t_px *px)
{
	t_xyz		v;
	t_xyz		top;


	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	top = v_add(px->hitpoint, v_multiply(co.vNormal, co.height));
	if (v_magnitude(v_subtract(px->hitpoint, top)) < (co.diameter * 0.5))
		px->surface_normal = co.vNormal;
	if (v_magnitude(v_subtract(px->hitpoint, co.pOrigin)) < (co.diameter * 0.5))
		px->surface_normal = v_multiply(co.vNormal, -1);
	else
	{
		v = v_subtract(co.pOrigin, px->hitpoint);
		px->surface_normal = v_cross(v, co.vNormal);
		px->surface_normal = v_cross(px->surface_normal, co.vNormal);
		v_normalizep(&px->surface_normal);
	}
	px->facing_ratio = fabsf(v_dot(px->surface_normal, px->direction));
	return (px->color);
}

int	get_color_cone(t_object object, t_px px, mlx_texture_t *text)
{
	t_xyz		axis_hp;
	t_xyz		unit;
	float		u;
	float		v;

	axis_hp = v_add(object.pOrigin, v_multiply(object.vNormal, px.hit_height));
	unit = v_subtract(px.hitpoint, axis_hp);
	v_normalizep(&unit);
	u = atan2(unit.z, unit.x);
	v = px.hit_height / object.height;
	if (object.text == NR_TEXTURES + 1)
		px.color = checkered(px, u, px.hit_height, 0);
	else
	{		
		u = ((u + M_PI) / (2 * M_PI));
		v = 1 - ((v + 1) * 0.5);
		px.color = get_text_pxcolor(text, u, v);
	}
	return (px.color);
}