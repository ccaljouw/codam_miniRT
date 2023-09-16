/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:32:58 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/16 15:23:04 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief	Initialize a 4x4 matrix as identity matrix
 * 			(so all pivots are set to 1, the rest to 0)
 * 
 * @return float** 
 */
t_m44	m44_init(void)
{
	t_m44		res;
	int			rows;
	int			cols;

	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			if (cols == rows)
				res.arr[rows][cols] = 1;
			else
				res.arr[rows][cols] = 0;
			cols++;
		}
		cols = 0;
		rows++;
	}
	return (res);
}

// /**
//  * @brief Free a 4x4 matrix
//  * 
//  * @param matrix 
//  */
// void	m44_free(float **matrix)
// {
// 	int	rows;

// 	rows = 0;
// 	while (matrix[rows] && rows < 4)
// 		free(matrix[rows++]);
// 	free (matrix);
// 	matrix = NULL;
// }

/**
 * @brief	Copies a 4*4 matrix.
 * 
 * @param matrix 
 * @return float** 
 */
void	m44_copy(t_m44	src, t_m44 *dst)
{
	int		rows;
	int		cols;

	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			dst->arr[rows][cols] = src.arr[rows][cols];
			cols++;
		}
		cols = 0;
		rows++;
	}
}

/**
 * @brief	Returns dot product of two matrices. Set free_m1 to 1
 * 			to free the first input matrix, so you can write
 * 
 * 			m1 = m44_dot_product(m1, m2, 1);
 * 
 * 			without leaking memory.
 * 
 * @param m1 
 * @param m2 
 * @param free_m1 
 * @return float** 
 */
t_m44	m44_dot_product(t_m44 m1, t_m44 m2)
{
	t_m44	product;
	int		rows;
	int		cols;

	product = m44_init();
	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			product.arr[rows][cols] = m1.arr[rows][0] * m2.arr[0][cols] + \
									m1.arr[rows][1] * m2.arr[1][cols] + \
									m1.arr[rows][2] * m2.arr[2][cols] + \
									m1.arr[rows][3] * m2.arr[3][cols];
			cols++;
		}
		cols = 0;
		rows++;
	}
	return (product);
}

// void	m44_to_identity_matrix(float **matrix)
// {
// 	int	rows;
// 	int	cols;

// 	rows = 0;
// 	while (rows < 4)
// 	{
// 		cols = 0;
// 		while (cols < 4)
// 		{
// 			if (rows == cols)
// 				matrix[rows][cols] = 1;
// 			else
// 				matrix[rows][cols] = 0;
// 			cols++;
// 		}
// 		rows++;
// 	}
// }

/**
 * @brief	Print a 4x4 matrix
 * 
 * @param matrix 
 */
void	m44_print(t_m44 matrix)
{
	int	rows;
	int	cols;

	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		while (cols < 4)
		{
			ft_printf("| % 7.3f |", matrix.arr[rows][cols]);
			cols++;
		}
		ft_printf("\n");
		cols = 0;
		rows++;
	}
	ft_printf("\n");
}

/**
 * @brief	Multiply a point (3 dimension vector) by a 4x4 matrix
 * 
 * @param m the matrix
 * @param p the point
 */
void	m44_multiply_vec3(t_m44 matrix, t_xyz *point)
{
	point->x = point->x * matrix.arr[0][0] \
				+ point->y * matrix.arr[1][0] \
				+ point->z * matrix.arr[2][0] \
				+ matrix.arr[3][0];
	point->y = point->x * matrix.arr[0][1] \
				+ point->y * matrix.arr[1][1] \
				+ point->z * matrix.arr[2][1] \
				+ matrix.arr[3][1];
	point->z = point->x * matrix.arr[0][2] \
				+ point->y * matrix.arr[1][2] \
				+ point->z * matrix.arr[2][2] + \
				matrix.arr[3][2];
}


// int	m44_is_identity_matrix(float **matrix)
// {
// 	int	rows;
// 	int	cols;

// 	rows = 0;
// 	while (rows < 4)
// 	{
// 		cols = 0;
// 		while (cols < 4)
// 		{
// 			if (rows == cols)
// 			{
// 				if (matrix[rows][cols] != 1)
// 					return (0);
// 			}
// 			else
// 				if (matrix[rows][cols] != 0)
// 					return (0);
// 			cols++;
// 		}
// 		rows++;
// 	}
// 	return (1);
// }
