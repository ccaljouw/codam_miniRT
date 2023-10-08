/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:32:07 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:35:49 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief Creates new vector (t_xyz), 
 * the result of vector a * scaler b
 * 
 * @param a (t_xyz)
 * @param b (float)
 * @return t_xyz 
 */
t_xyz	v_multiply(t_xyz a, float b)
{
	t_xyz	new;

	new.x = a.x * b;
	new.y = a.y * b;
	new.z = a.z * b;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), 
 * the result of vector a / scaler b
 * 
 * @param a (t_xyz)
 * @param b (float)
 * @return t_xyz 
 */
t_xyz	v_divide(t_xyz a, float b)
{
	t_xyz	new;

	new.x = a.x / b;
	new.y = a.y / b;
	new.z = a.z / b;
	return (new);
}

/**
 * @brief Creates scalar number (float), dot product of vector a and vector b.
 * The dot product, also called scalar product, is a measure of how closely 
 * two vectors align, in terms of the directions they point. It is the projection
 * of one vector onto another
 * (A dot B)
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return float
 */
float	v_dot(t_xyz a, t_xyz b)
{
	float	new;

	new = a.x * b.x + a.y * b.y + a.z * b.z;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), cross product of vector a and vector b.
 * It results in a vector that is perpendicular to the plane defined by a and b.
 * The order of the parameters affects (negates) the resulting vector.
 * Use hand to determine the orientation of resulting vector (c).
 * Index finger = a, middle finger = b, thumb = c
 * (A X B = C) (B X A = -C)
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_cross(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.y * b.z - b.y * a.z;
	new.y = b.x * a.z - a.x * b.z;
	new.z = a.x * b.y - b.x * a.y;
	return (new);
}

/**
 * @brief Calculates the length of a vector (|| V ||)
 * Vector lenth is also called norm
 * @param a 
 * @return float 
 */
float	v_magnitude(t_xyz a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}
