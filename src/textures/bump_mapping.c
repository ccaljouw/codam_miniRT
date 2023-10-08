/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 15:10:18 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/08 23:58:44 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Bump maps are created by pertubating the surface normal at the hitpoint

available procedures:
	1	simple_rough	(a procedural bump map)
	2	bump_bumptext 	(uses the object->bumptext)
	3	bump_text		(uses the object->text that is also color mapped 
						onto the object)
*/

void	simple_rough(t_px *px, float min, float max)
{
	float	x;
	float	y;
	float	z;

	x = min + (((float)rand() / (float)(RAND_MAX)) * (max - min));
	y = min + (((float)rand() / (float)(RAND_MAX)) * (max - min));
	z = min + (((float)rand() / (float)(RAND_MAX)) * (max - min));
	perturb_normal(px, v_create(x, y, z));
}

void	bump_bumptext(t_px *px)
{
	t_xyz			fact;
	int				color;
	float			rgb[3];

	if (!px->hitobject->bump)
		return ;
	color = get_text_pxcolor(px->hitobject->bump, px->uv);
	rgb[0] = (float)((color >> 24) & 0xFF) / 255.0;
	rgb[1] = (float)((color >> 16) & 0xFF) / 255.0;
	rgb[2] = (float)((color >> 8) & 0xFF) / 255.0;
	fact = v_create(rgb[0] * 1, rgb[1] * 1, rgb[2] * 1);
	perturb_normal(px, fact);
}

void	bump_text(t_px *px)
{
	t_xyz			fact;
	int				color;
	float			rgb[3];

	if (!px->hitobject->text)
		return ;
	color = get_text_pxcolor(px->hitobject->text, px->uv);
	color = px->color - (0 >> 24 | 0 >> 16 | 255 >> 8 | 255);
	rgb[0] = (float)((color >> 24) & 0xFF) / 255.0;
	rgb[1] = (float)((color >> 16) & 0xFF) / 255.0;
	rgb[2] = (float)((color >> 8) & 0xFF) / 255.0;
	fact = v_create(rgb[0], rgb[1], rgb[2]);
	perturb_normal(px, fact);
}

void	perturb_normal(t_px *px, t_xyz perturbation)
{
	t_xyz	up;
	t_xyz	p_v;
	t_xyz	p_u;

	up = v_create(0, 1, 0);
	if (px->surface_normal.y > 0.99 || px->surface_normal.y < -0.99)
		up = v_create(1, 0, 0);
	p_v = v_normalize(v_cross(up, px->surface_normal));
	p_u = v_normalize(v_cross(px->surface_normal, p_v));
	p_u.x *= perturbation.x;
	p_v.y *= perturbation.y;
	px->surface_normal.z *= perturbation.z;
	px->surface_normal = \
			v_add(px->surface_normal, (v_add(p_u, p_v), px->surface_normal));
	px->surface_normal = v_normalize(px->surface_normal);
}

void	map_normal(t_px *px)
{
	if (!px->hitobject->bump_proc)
		return ;
	if (px->hitobject->bump_proc == 1)
		simple_rough(px, 0, 1);
	if (px->hitobject->bump_proc == 2)
		bump_bumptext(px);
	if (px->hitobject->bump_proc == 3)
		bump_text(px);
}
