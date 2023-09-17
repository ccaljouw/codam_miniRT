/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 16:32:58 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/17 18:06:33 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

/**
 * @brief	Initialize a 4x4 matrix as identity matrix
 * 			(so all pivots are set to 1, the rest to 0)
 * 
 * @return	t_m44
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

/**
 * @brief	Copies src 4x4 matrix to 4x4 matrix pointed to by dest
 * 
 * @param src 
 * @param dst 
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
 * @brief Returns dot product of two 4x4 matrices
 * 
 * @param m1 
 * @param m2 
 * @return t_m44 
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


