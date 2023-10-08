/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 08:31:28 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/08 23:35:31 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief Creates new vector (t_xyz) with input values x, y, and z
 * 
 * @param x (float)
 * @param y (float)
 * @param z (float)
 * @return t_xyz 
 */
t_xyz	v_create(float x, float y, float z)
{
	t_xyz	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

/**
 * @brief Creates and returs a copy of the provided vector
 * 
 * @param a (t_xyz);
 * @return t_xyz 
 */
t_xyz	v_copy(t_xyz a)
{
	t_xyz	new;

	new.x = a.x;
	new.y = a.y;
	new.z = a.z;
	return (new);
}

/**
 * @brief  copies values from a into pointer b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz *)
 */
void	v_copy_values(t_xyz a, t_xyz *b)
{
	b->x = a.x;
	b->y = a.y;
	b->z = a.z;
}

/**
 * @brief Creates new vector (t_xyz), 
 * the sum of vector a and vector b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_add(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.x + b.x;
	new.y = a.y + b.y;
	new.z = a.z + b.z;
	return (new);
}

/**
 * @brief Creates new vector (t_xyz), 
 * the result of vector a minus vector b
 * 
 * @param a (t_xyz)
 * @param b (t_xyz)
 * @return t_xyz 
 */
t_xyz	v_subtract(t_xyz a, t_xyz b)
{
	t_xyz	new;

	new.x = a.x - b.x;
	new.y = a.y - b.y;
	new.z = a.z - b.z;
	return (new);
}
