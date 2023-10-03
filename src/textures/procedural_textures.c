/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:18:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 13:56:17 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Procedural textures are calcultaed basd on x, y coordinates of the object space.

available procedures:
	1	checkered
	2	v_checkered
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
