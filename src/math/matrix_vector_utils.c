/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vector_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:35:38 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/18 21:16:17 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"

/**
 * @brief	Multiply a dimension vector by a 4x4 matrix
 * 
 * @param m the matrix
 * @param p the src.*/
void	m44_multiply_vec3(t_m44 matrix, t_xyz src, t_xyz *dst)
{
	float	x;
	float	y;
	float	z;
	float	w;

	x = src.x * matrix.arr[0][0] + src.y * matrix.arr[1][0] \
				+ src.z * matrix.arr[2][0] + matrix.arr[3][0];
	y = src.x * matrix.arr[0][1] + src.y * matrix.arr[1][1] \
				+ src.z * matrix.arr[2][1] + matrix.arr[3][1];
	z = src.x * matrix.arr[0][2] + src.y * matrix.arr[1][2] \
				+ src.z * matrix.arr[2][2] + matrix.arr[3][2];
	w = src.x * matrix.arr[0][3] + src.y * matrix.arr[1][3] \
				+ src.z * matrix.arr[2][3] + matrix.arr[3][3];
	dst->x = x / w;
	dst->y = y / w;
	dst->z = z / w;
}

/**
 * @brief	Multply a direction vector with a matrix
 * 			(difference with normal mulptiplication is that the
 * 			'w'-column isn't calulated, and tranlation is not applied)
 * 
 * @param matrix 
 * @param src 
 * @param dst 
 */
void	m44_multiply_vec3_dir(t_m44 matrix, t_xyz src, t_xyz *dst)
{
	float	x;
	float	y;
	float	z;

	x = src.x * matrix.arr[0][0] + src.y * matrix.arr[1][0] \
				+ src.z * matrix.arr[2][0];
	y = src.x * matrix.arr[0][1] + src.y * matrix.arr[1][1] \
				+ src.z * matrix.arr[2][1];
	z = src.x * matrix.arr[0][2] + src.y * matrix.arr[1][2] \
				+ src.z * matrix.arr[2][2];
	dst->x = x;
	dst->y = y;
	dst->z = z;
}

/**
 * @brief	Creates a rotation matrix from an orientation vector,
 * 			this can then be applied to the cam2world matrix.
 * 			NB: this function assumes the 'y' axis is the UP direction.
 * 
 * @param orientation 
 * @return t_m44 
 */
t_m44	m44_from_direction_vector(t_xyz orientation)
{
	t_xyz	x_axis;
	t_xyz	y_axis;
	t_m44	matrix;

	matrix = m44_init();
	x_axis = v_normalize(v_cross(v_create(0, 1, 0), orientation));
	y_axis = v_normalize(v_cross(orientation, x_axis));
	matrix.arr[0][0] = x_axis.x;
	matrix.arr[0][1] = y_axis.x;
	matrix.arr[0][2] = orientation.x;
	matrix.arr[1][0] = x_axis.y;
	matrix.arr[1][1] = y_axis.y;
	matrix.arr[1][2] = orientation.y;
	matrix.arr[2][0] = x_axis.z;
	matrix.arr[2][1] = y_axis.z;
	matrix.arr[2][2] = orientation.z;
	return (matrix);
}
