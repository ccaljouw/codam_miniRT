/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:18:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/09 00:01:05 by albertvanan      ###   ########.fr       */
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

int	checkered(t_px *px, int mod)
{
	t_xyz	coord;

	px->uv.x *= 20;
	px->uv.y *= 20;
	coord.x = fabs(floor(px->uv.x));
	coord.y = fabs(floor(px->uv.y));
	coord.z = fabs(floor(px->uv.z));
	coord.x = (int)coord.x % mod;
	coord.y = (int)coord.y % mod;
	coord.z = (int)coord.z % mod;
	if (!(((int)coord.x ^ (int)coord.y) ^ (int)coord.z))
		px->color = invert_color(px->color);
	return (px->color);
}

int	gradient(t_px *px)
{
	int		r;
	int		g;
	int		b;
	float	pos;
	t_xyz	fact;

	pos = bilinear_interpolation(px->uv.x, px->uv.y);
	fact = color_map_5s(fabs(pos));
	r = (int)(fact.x * 255.0);
	g = (int)(fact.y * 255.0);
	b = (int)(fact.z * 255.0);
	px->color = (r << 24 | g << 16 | b << 8 | 255);
	return (px->color);
}
