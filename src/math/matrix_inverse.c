/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 17:09:52 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/17 00:00:50 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"

static int	set_pivot_to_nonzero(int col, t_m44 *matrix, t_m44 *inverse);
static void	reduce_under_diagonal(t_m44 *matrix, t_m44 *inverse);
static void	scale_pivots(t_m44 *matrix, t_m44 *inverse);
static void	reduce_above_diagnonal(t_m44 *matrix, t_m44 *inverse);

/**
 * @brief Invert matrix using the Gauss-Jordan method
 * 
 * @param input the matrix to be inverted
 * @param result the inverted matrix will be put here
 * @return int returns 0 on failure, 1 on succes
 */
int	m44_invert(t_m44 input, t_m44 *result)
{
	int		cols;

	*result = m44_init();
	cols = 0;
	while (cols < 4)
	{
		if (input.arr[cols][cols] == 0)
		{
			if (!set_pivot_to_nonzero(cols, &input, result))
				return (ft_dprintf(2, "Matrix inverse failed!\n"), 0);
		}
		cols++;
	}
	reduce_under_diagonal(&input, result);
	scale_pivots(&input, result);
	reduce_above_diagnonal(&input, result);
	if (!m44_is_identity_matrix(input))
		return (ft_dprintf(2, "Matrix inverse failed!\n"), 0);
	return (1);
}

/**
 * @brief	Subfunction for m44_inverse. Gets called whenever a pivot
 * 			of a matrix (ie m[1,1] or m[3,3]) is zero. Swaps it out for the 
 * 			highest absolute number in the column of the given pivot, unless
 * 			this puts a zero on a pivot place left of the current column.
 * 			Returns zero if no swap is possible.
 * 
 * @param col 
 * @param matrix 
 * @param inverse 
 * @return int 
 */
static int	set_pivot_to_nonzero(int col, t_m44 *matrix, t_m44 *inverse)
{
	int		i;
	int		biggest_row;
	int		row;

	biggest_row = col;
	row = 0;
	while (row < 4)
	{
		if (fabsf(matrix->arr[row][col]) > fabsf(matrix->arr[biggest_row][col]))
			if (!(row < col && matrix->arr[col][row] == 0))
				biggest_row = row;
		row++;
	}
	if (biggest_row == col)
		return (0);
	i = 0;
	while (i < 4)
	{
		swap_floats(&matrix->arr[biggest_row][i], &matrix->arr[col][i]);
		swap_floats(&inverse->arr[biggest_row][i], &inverse->arr[col][i]);
		i++;
	}
	return (1);
}

/**
 * @brief	Reduce all coefficients under the diagonal to zero.
 * 
 * @param matrix 
 * @param inverse 
 */
static void	reduce_under_diagonal(t_m44 *matrix, t_m44 *inverse)
{
	int		cols;
	int		rows;
	int		i;
	float	reducer;

	cols = 0;
	i = 0;
	while (cols < 3)
	{
		rows = cols + 1;
		while (rows < 4)
		{
			reducer = matrix->arr[rows][cols] / matrix->arr[cols][cols];
			while (i < 4)
			{
				matrix->arr[rows][i] -= reducer * matrix->arr[cols][i];
				inverse->arr[rows][i] -= reducer * inverse->arr[cols][i];
				i++;
			}
			matrix->arr[rows][cols] = 0;
			i = 0;
			rows++;
		}
		cols++;
	}
}

/**
 * @brief Scale all pivots to 1.
 * 
 * @param matrix 
 * @param inverse 
 */
static void	scale_pivots(t_m44 *matrix, t_m44 *inverse)
{
	int		cols;
	int		rows;
	float	reducer;

	rows = 0;
	cols = 0;
	while (rows < 4)
	{
		reducer = matrix->arr[rows][rows];
		while (cols < 4)
		{
			matrix->arr[rows][cols] /= reducer;
			inverse->arr[rows][cols] /= reducer;
			cols++;
		}
		cols = 0;
		rows++;
	}
}

/**
 * @brief	Reduce all coefficients above the diagonal to 0
 * 
 * 
 * @param matrix 
 * @param inverse 
 */
static void	reduce_above_diagnonal(t_m44 *matrix, t_m44 *inverse)
{
	int		rows;
	int		cols;
	int		i;
	float	reducer;

	rows = 0;
	i = 0;
	while (rows < 4)
	{
		cols = rows + 1;
		while (cols < 4)
		{
			reducer = matrix->arr[rows][cols];
			while (i < 4)
			{
				matrix->arr[rows][i] -= matrix->arr[cols][i] * reducer;
				inverse->arr[rows][i] -= inverse->arr[cols][i] * reducer;
				i++;
			}
			matrix->arr[rows][cols] = 0;
			i = 0;
			cols++;
		}
		rows++;
	}
}
