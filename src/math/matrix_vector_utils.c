/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vector_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 15:35:38 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/17 18:06:42 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"

/**
 * @brief	Multiply a src.3 dimension vector) by a 4x4 matrix
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
