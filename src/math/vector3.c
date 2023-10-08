/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:33:38 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:35:39 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief returns a normalized version of the vector that it is called with
 * by deviding all elements by the vector magnitude
 * @param a (t_xyz) vector to normalize
 */
t_xyz	v_normalize(t_xyz a)
{
	t_xyz	new;
	float	mag;
	float	mag_inv;

	mag = v_magnitude(a);
	if (mag > 0)
	{
		mag_inv = 1 / mag;
		new = v_create(a.x * mag_inv, a.y * mag_inv, a.z * mag_inv);
		return (new);
	}
	return (v_copy(a));
}

/**
 * @brief normalizes the vector that it is called with
 * by deviding all elements by the vector magnitude
 * @param a (t_xyz) vector to normalize
 */
void	v_normalizep(t_xyz *a)
{
	float	mag;
	float	mag_inv;

	mag = v_magnitude(*a);
	if (mag > 0)
	{
		mag_inv = 1 / mag;
		a->x *= mag_inv;
		a->y *= mag_inv;
		a->z *= mag_inv;
	}
}

/**
 * @brief Returns the sum of the squares of all components
 * 		in the vector.
 * 
 * @param a 
 * @return float 
 */
float	v_square_of_self(t_xyz a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

/**
 * @brief Returns the angle between to vectors in degrees
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float	v_angle(t_xyz a, t_xyz b)
{
	float	cos_angle;
	float	nom;
	float	denom;

	nom = v_dot(a, b);
	denom = v_magnitude(a) * v_magnitude(b);
	if (denom == 0)
		return (0);
	cos_angle = nom / denom;
	return (acos(cos_angle) / M_PI * 180);
}
