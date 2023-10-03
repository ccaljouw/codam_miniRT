/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:18:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 12:08:57 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Procedural textures are calcultaed basd on x, y coordinates of the object space.

available procedures:
	1	checkered
	2	v_checkered
*/

int	checkered(t_px px, float x, float y, float z)
{

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 2;
	y = (int)y % 2;
	z = (int)z % 2;
	if (((int)x ^ (int)y) ^ (int)z)
		px.color = invert_color(px.color);
	return (px.color);
}

int	v_checkered(t_px px, float x, float y, float z)
{

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 3;
	y = (int)y % 3;
	z = (int)z % 3;
	if (!(((int)x ^ (int)y) ^ (int)z))
		px.color = invert_color(px.color);
	return (px.color);
}

int	map_procedure(t_px px, t_xyz uv)
{
	if (px.hitobject->text_proc == 1)
		return (checkered(px, uv.x, uv.y, uv.z));
	if (px.hitobject->text_proc == 2)
		return (v_checkered(px, uv.x, uv.y, uv.z));
	return (px.color);	
}