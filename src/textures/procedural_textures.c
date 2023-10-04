/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procedural_textures.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/04 18:21:16 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Procedural textures are calcultaed basd on x, y coordinates of the object space.

available procedures:
	1	checkered
	2	v_checkered
	3	gradient;
*/

int	checkered(t_px *px, t_xyz uv)
{
	px->text_coord.x = fabs(floor(uv.x));
	px->text_coord.y = fabs(floor(uv.y));
	px->text_coord.z = fabs(floor(uv.z));
	px->text_coord.x = (int)px->text_coord.x % 2;
	px->text_coord.y = (int)px->text_coord.y % 2;
	px->text_coord.z = (int)px->text_coord.z % 2;
	if (((int)px->text_coord.x ^ (int)px->text_coord.y) ^ (int)px->text_coord.z)
		px->color = invert_color(px->color);
	return (px->color);
}

int	v_checkered(t_px *px, t_xyz uv)
{
	px->text_coord.x = fabs(floor(uv.x));
	px->text_coord.y = fabs(floor(uv.y));
	px->text_coord.z = fabs(floor(uv.z));
	px->text_coord.x = (int)px->text_coord.x % 3;
	px->text_coord.y = (int)px->text_coord.y % 3;
	px->text_coord.z = (int)px->text_coord.z % 3;
	if (!(((int)px->text_coord.x ^ (int)px->text_coord.y) ^ (int)px->text_coord.z))
		px->color = invert_color(px->color);
	return (px->color);
}

int	gradient(t_px *px, t_xyz uv)
{
	static t_n_uv	*norm_uv[4] = {norm_uvcoord_sp, norm_uvcoord_pl, \
		norm_uvcoord_cy , norm_uvcoord_co};
	int		r;
	int		g;
	int		b;
	t_xyz	fact;


	uv = norm_uv[px->hitobject->id](*px->hitobject, uv);
	fact = color_map_5s(fabs(uv.x));
	r = (int)(fact.x * 255.0);
	g = (int)(fact.y * 255.0);
	b =	(int)(fact.z * 255.0);
	// ft_printf("r:%d, g:%d, b:%d\n", r, g, b);
	px->color = (r << 24 | g << 16 | b << 8 | 255);
	return (px->color);
}

