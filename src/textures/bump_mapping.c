/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bump_mapping.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/02 15:10:18 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/03 10:21:41 by cariencaljo   ########   odam.nl         */
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

float	get_text_val(t_xyz coord)
{
	(void)coord;
	return (0);
}

/**
 * @brief use the symmetric difference quotient to estimate the partial derivatives 
 * of the texture at the point uv
 * 
 * @param px 
 * @param uv 
 */
t_xyz	texture_diff(t_px *px, t_xyz uv)
{
	t_xyz	u_disp;
	t_xyz	v_disp;
	float	u_grad;
	float	v_grad;
	
	u_disp = v_create(SHADOW_BIAS, 0, 0);
	v_disp = v_create(0, 0, SHADOW_BIAS);
	(void)px;
	u_grad = get_text_val(v_divide(v_subtract(v_add(uv, u_disp),v_subtract(uv, u_disp)), 2 * SHADOW_BIAS));
	v_grad = get_text_val(v_divide(v_subtract(v_add(uv, v_disp),v_subtract(uv, v_disp)), 2 * SHADOW_BIAS));
	return(v_create(u_grad, v_grad, 0));
}
void	compute_pertubation(t_px *px, t_xyz uv, float scale, float reverse)
{
	float	x;
	float	y;
	float	z;
	t_xyz	gradient;

	z = 0;
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

void	map_normal(t_px *px)
{
	if (!px->hitobject->bump)
		return;
	if (px->hitobject->bump == 1)
		simple_rough(px, 0, 1);
}
