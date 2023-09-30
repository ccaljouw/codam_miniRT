/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapping.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/30 16:48:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	checkered(t_px px, float x, float y, float z)
{
	int			color;

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 2;
	y = (int)y % 2;
	z = (int)z % 2;
	color = (px.hitobject->rgb[0] << 24 | px.hitobject->rgb[1] << 16 | px.hitobject->rgb[2] << 8 | 255);
	if (((int)x ^ (int)y) ^ (int)z)
		color = invert_color(color);
	return (color);
}

