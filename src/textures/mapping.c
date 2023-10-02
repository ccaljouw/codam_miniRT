/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapping.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/02 09:53:23 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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

