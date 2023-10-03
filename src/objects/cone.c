/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:23:25 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 12:33:20 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <miniRT.h>

int		set_hp_info(float *hit_param, float height, float *hp_info);

t_xyz	get_abc_cone(t_px *ray, t_object cone)
{
	t_xyz	abc;
	t_xyz	D;
	t_xyz	X;
	t_xyz	V;
	float	angle;
	float	half_angle;
	float	hypotenuse;

	hypotenuse = sqrt(pow(cone.diameter * 0.5, 2) + pow(cone.height * 0.5, 2));
	angle = acos((cone.height * 0.5) / hypotenuse);
	half_angle = 1 + (angle  * 0.5) * (angle  * 0.5);
	D = ray->direction;
	X = v_subtract(ray->cam_origin, cone.pOrigin);
	V = v_normalize(cone.vNormal);
	abc.x = v_dot(D, D) - (half_angle * pow(v_dot(D, V), 2));
	abc.y = 2 * (v_dot(D, X) - (half_angle  * v_dot(D, V) * v_dot(X, V)));
	abc.z = v_dot(X, X) - ((half_angle * pow(v_dot(X, V), 2)));
	return (abc);
}

int	test_cone(t_px *ray, t_object cone, float *hp_info)
{
	t_xyz	abc;
	t_xyz	orig_to_center;
	float	hit_param[4];

	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cone.pOrigin);
	abc = get_abc_cone(ray, cone);
	if (!get_parabolic_hitpoints(abc, &hit_param[0], &hit_param[1]))
		return (0);
	hit_param[2] = (v_dot(ray->direction, cone.vNormal) * hit_param[0]) \
				+ v_dot(orig_to_center, cone.vNormal);
	hit_param[3] = (v_dot(ray->direction, cone.vNormal) * hit_param[1]) \
				+ v_dot(orig_to_center, cone.vNormal);
	if (hit_param[0] < 0)
	{
		hit_param[0] = hit_param[1];
		if (hit_param[0] < 0)
			return (0);
	}
	return(set_hp_info(hit_param, cone.height, hp_info));
}

int	get_cone_surface_data(t_object co, t_px *px)
{
	t_xyz		hit_to_center;
	float		a;
	float		angle;
	float		hypotenuse;

	hypotenuse = sqrt(pow(co.diameter * 0.5, 2) + pow(co.height * 0.5, 2));
	angle = acos((co.height * 0.5) / hypotenuse);
	a = px->hit_height * (angle  * 0.5) * (angle  * 0.5);
	px->hitpoint = v_add(px->cam_origin, v_multiply(px->direction, px->hit_distance));
	hit_to_center = v_subtract(px->hitpoint, co.pOrigin);
	px->surface_normal = v_subtract(hit_to_center, v_multiply(co.vNormal, px->hit_height));
	px->surface_normal = v_subtract(px->surface_normal, v_multiply(co.vNormal, a));
	v_normalizep(&px->surface_normal);
	px->facing_ratio = fabsf(v_dot(px->surface_normal, px->direction));
	return (px->color);
}

t_xyz	get_uvcoord_co(t_object co, t_px px)
{
	t_xyz		axis_hp;
	t_xyz		unit;
	float		u;
	float		v;

	axis_hp = v_add(co.pOrigin, v_multiply(co.vNormal, px.hit_height));
	unit = v_subtract(px.hitpoint, axis_hp);
	u = atan2(unit.z, unit.x);
	v = px.hit_height;
	return (v_create(u, v, 0));
}

t_xyz	norm_uvcoord_co(t_object co, t_xyz uv)
{
	uv.x = (uv.x + M_PI) / (2 * M_PI);
	uv.y = 1 - (uv.y/co.height);
	return (uv);
}

/**
 * @brief Get the color of the object by calculating uv coordinates.
 * for texture pixel color the uv coordinates are normalized 
 * 
 * @param object 
 * @param px 
 * @return int 
 */
int	get_color_cone(t_object object, t_px px)
{
	t_xyz		uv;

	uv = get_uvcoord_co(object, px);
	if (object.text)
		px.color = get_text_pxcolor(object.text, norm_uvcoord_co(object, uv));
	if (object.text_proc)
		px.color = map_procedure(px, uv);
	return (px.color);
}
