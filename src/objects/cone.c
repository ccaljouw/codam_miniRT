/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cone.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 19:23:25 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/08 21:11:28 by cariencaljo   ########   odam.nl         */
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

t_xyz	get_uvcoord_co(t_object co, t_px px, t_scene *scene)
{
	t_xyz		axis_hp;
	t_xyz		uv;


	(void)scene;
	axis_hp = v_add(co.pOrigin, v_multiply(co.vNormal, px.hit_height));
	uv = v_subtract(px.hitpoint, axis_hp);
	m44_multiply_vec3_dir(co.rotate_matrix, uv, &uv);
	uv.x = 0.5 + (atan2(uv.z, uv.x) / (2 * M_PI));
	uv.y = 1 - (px.hit_height / co.height);
	uv.z = 0;
	return (uv);
}

