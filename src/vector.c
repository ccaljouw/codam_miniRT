/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 08:31:28 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 09:55:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

t_xyz	v_create(double x, double y, double z)
{
	t_xyz new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_xyz	v_add(t_xyz a, t_xyz b)
{
	t_xyz new;
	
	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

t_xyz	v_subtract(t_xyz a, t_xyz b)
{
	t_xyz new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}

t_xyz	vs_mulitply(t_xyz a, double b)
{
	t_xyz new;

	new.x = a.x * b;
	new.y = a.y * b;
	new.z = a.z * b;
	return (new);
}

double	v_dot(t_xyz a, t_xyz b)
{
	double new;

	new = a.x * b.x + a.y * b.y + a.z * b.z;
	return (new);
}

t_xyz	v_cross(t_xyz a, t_xyz b)
{
	t_xyz	new;
	
	new.x = a.y * b.z - b.y * a.z;
	new.y = b.x * a.z - a.x * b.z;
	new.z = a.x * b.y - b.x * a.y;
	return (new);
}