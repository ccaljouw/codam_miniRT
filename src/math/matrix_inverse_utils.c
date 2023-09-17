/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 23:46:37 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/17 00:01:06 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

void	swap_floats(float *a, float *b)
{
	float	buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

/**
 * @brief	Checks if the matrix provided is an identity matrix
 * 			(all pivots are 1, the rest 0)
 * 
 * @param matrix 
 * @return int 
 */
int	m44_is_identity_matrix(t_m44 matrix)
{
	int	rows;
	int	cols;

	rows = 0;
	while (rows < 4)
	{
		cols = 0;
		while (cols < 4)
		{
			if (rows == cols)
			{
				if (round(matrix.arr[rows][cols]) != 1)
					return (0);
			}
			else
				if (round(matrix.arr[rows][cols]) != 0)
					return (0);
			cols++;
		}
		rows++;
	}
	return (1);
}
