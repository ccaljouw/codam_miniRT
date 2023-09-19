/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:28:29 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/17 18:06:26 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fdf.h"
#include "matrix.h"

static t_m44	m44_rotate_axis(float angle, char axis);

void	m44_rotate(t_m44 *matrix, float x, float y, float z)
{
	if (x > 0)
		*matrix = m44_dot_product(*matrix, m44_rotate_axis(x, 'x'));
	if (y > 0)
		*matrix = m44_dot_product(*matrix, m44_rotate_axis(y, 'y'));
	if (z > 0)
		*matrix = m44_dot_product(*matrix, m44_rotate_axis(z, 'z'));
}

/**
 * @brief Return a rotation matrix for the given angle, rotated 
 * 		by the angle in degrees
 * 
 * @param matrix 
 * @param angle angle in degrees
 * @param axis axis to rotate on
 */
static t_m44	m44_rotate_axis(float angle, char axis)
{
	t_m44	matrix;

	matrix = m44_init();
	if (axis == 'x')
	{
		matrix.arr[1][1] = cos(ft_rad(angle));
		matrix.arr[1][2] = sin(ft_rad(angle));
		matrix.arr[2][1] = -1 * sin(ft_rad(angle));
		matrix.arr[2][2] = cos(ft_rad(angle));
	}
	if (axis == 'y')
	{
		matrix.arr[0][0] = cos(ft_rad(angle));
		matrix.arr[0][2] = -1 * sin(ft_rad(angle));
		matrix.arr[2][0] = sin(ft_rad(angle));
		matrix.arr[2][2] = cos(ft_rad(angle));
	}
	if (axis == 'z')
	{
		matrix.arr[0][0] = cos(ft_rad(angle));
		matrix.arr[0][1] = sin(ft_rad(angle));
		matrix.arr[1][0] = -1 * sin(ft_rad(angle));
		matrix.arr[1][1] = cos(ft_rad(angle));
	}
	return (matrix);
}

/**
 * @brief Scale matrix
 * 
 * @param matrix 
 * @param x multiply x by this value
 * @param y multiply y by this value
 * @param z multiply z by this value
 */
void	m44_scale(t_m44 *matrix, float x, float y, float z)
{
	matrix->arr[0][0] *= x;
	matrix->arr[1][1] *= y;
	matrix->arr[2][2] *= z;
}

/**
 * @brief Translate matrix
 * 
 * @param matrix 
 * @param x movement across x axis
 * @param y movement across y axis
 * @param z movement across z axis
 */
void	m44_translate(t_m44 *matrix, float x, float y, float z)
{
	matrix->arr[3][0] += x;
	matrix->arr[3][1] += y;
	matrix->arr[3][2] += z;
}

float	ft_rad(float angle)
{
	return (angle * (M_PI / 180.0));
}
