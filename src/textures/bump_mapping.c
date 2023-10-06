/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bump_mapping.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:10:18 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/06 09:22:59 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Bump maps are created by pertubating the surface normal at the hitpoint

available procedures:
	1	simple_rough
*/

void	simple_rough(t_px *px, float min, float max)
{
	float	x;
	float	y;
	float	z;
	
	x = min + (((float)rand()/(float)(RAND_MAX)) * (max - min));
	y = min + (((float)rand()/(float)(RAND_MAX)) * (max - min));
	z = min + (((float)rand()/(float)(RAND_MAX)) * (max - min));
	perturb_normal(px, v_create(x, y, z));
}

void bump_gradient(t_px *px, t_scene *scene)
{
	t_xyz			uv;
	t_xyz			fact;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	static t_n_uv	*norm_uv[4] = {norm_uvcoord_sp, norm_uvcoord_pl, \
		norm_uvcoord_cy , norm_uvcoord_co};

	uv = get_uv[px->hitobject->id](*px->hitobject, *px, scene);
	uv = norm_uv[px->hitobject->id](*px->hitobject, uv);
	fact = color_map_5s(fabs(uv.x));
	perturb_normal(px, fact);
}

void	compute_pertubation(t_px *px, t_xyz uv, float scale, float reverse)
{
	float	x;
	float	y;
	float	z;
	t_xyz	gradient;

	z = 0;
	if (!px->hitobject->text)
		return ;
	gradient = texture_diff(px, uv);
	if (!reverse)
	{
		x = -gradient.x * scale;
		y = -gradient.y * scale;
	}
	else
	{
		x = gradient.x * scale;
		y = gradient.y * scale;
	}
	perturb_normal(px, v_create(x, y, z));
}

void	perturb_normal(t_px *px, t_xyz perturbation)
{
	t_xyz	up;
	t_xyz	pV;
	t_xyz	pU;

	up = v_create(0, 1, 0);
	if (px->surface_normal.y > 0.99 || px->surface_normal.y < -0.99)
		up = v_create(1, 0, 0);
	pV = v_normalize(v_cross(up, px->surface_normal));
	pU = v_normalize(v_cross(px->surface_normal, pV));
	pU.x *= perturbation.x;
	pV.y *= perturbation.y;
	px->surface_normal.z *= perturbation.z;
	px->surface_normal = v_add(px->surface_normal,(v_add(pU, pV), px->surface_normal));
	px->surface_normal = v_normalize(px->surface_normal);
}

void	map_normal(t_px *px, t_scene *scene)
{
	if (!px->hitobject->bump)
		return;
	if (px->hitobject->bump == 1)
		simple_rough(px, 0, 1);
	if (px->hitobject->bump == 2)
		bump_gradient(px, scene);
}
