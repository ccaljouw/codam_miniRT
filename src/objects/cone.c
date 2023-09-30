/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cone.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/30 19:23:25 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/30 20:54:03 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include <miniRT.h>

/*
cylinder:
   a   = D|D - (D|V)^2
   b/2 = D|X - (D|V)*(X|V)
   c   = X|X - (X|V)^2 - r*r
cone:
   k   = len( P-C-V*m )/m
   a   = D|D - (1+k*k)*(D|V)^2
   b/2 = D|X - (1+k*k)*(D|V)*(X|V)
   c   = X|X - (1+k*k)*(X|V)^2
*/

t_xyz	get_abc_cyl(t_px *ray, t_xyz orig_to_center, t_object cylinder);
int		set_hp_info(float *hit_param, float height, float *hp_info);

int	test_cone(t_px *ray, t_object cone, float *hp_info)
{
	t_xyz	orig_to_center;
	t_xyz	abc;
	float	hit_param[5];

	v_normalizep(&cone.vNormal);
	ft_bzero(hit_param, 4 * sizeof(float));
	orig_to_center = v_subtract(ray->cam_origin, cone.pOrigin);
	abc = get_abc_cyl(ray, orig_to_center, cone);
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
	hp_info[0] = set_hp_info(hit_param, cone.height, hp_info);
	if (hp_info[0])
	{
		hit_param[4] = v_magnitude(v_subtract(orig_to_center, v_multiply(cone.vNormal, hp_info[1]))) / hp_info[1];
		return (1);
	}
	return (0);
}

int	get_cone_surface_data(t_object co, t_px *px)
{
	(void)co;
	(void)px;
	return (0);
}

int	get_color_cone(t_object object, t_px px, mlx_texture_t *text)
{
	(void)object;
	(void)px;
	(void)text;
	return (0);
}