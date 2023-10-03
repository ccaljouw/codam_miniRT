/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procedural_textures.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/03 10:43:53 by cariencaljo   ########   odam.nl         */
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

int	map_procedure(t_px px, float x, float y, float z)
{
	if (px.hitobject->text_proc == 1)
		return (checkered(px, x, y, z));
	if (px.hitobject->text_proc == 2)
		return (v_checkered(px, x, y, z));
	return (px.color);	
}