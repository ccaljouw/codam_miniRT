/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:32:55 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:10:52 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include <math.h>
# include <types.h>
# include <libft.h>
# include <vector.h>
# include <miniRT.h>

// MATRIX UTILS

t_m44	m44_init(void);
void	m44_print(t_m44 matrix);
void	m44_copy(t_m44	src, t_m44 *dst);
t_m44	m44_dot_product(t_m44 m1, t_m44 m2);

// MATRIX x VEC3 UTILS

void	m44_multiply_vec3(t_m44 matrix, t_xyz src, t_xyz *dst);
void	m44_multiply_vec3_dir(t_m44 matrix, t_xyz src, t_xyz *dst);
t_m44	m44_from_direction_vector(t_xyz orientation);
void	m44_translate_by_vector(t_m44 *matrix, t_xyz vector);

// MATRIX TRANSFORMATIONS

void	m44_rotate(t_m44 *matrix, float x, float y, float z);
void	m44_scale(t_m44 *matrix, float x, float y, float z);
void	m44_translate(t_m44 *matrix, float x, float y, float z);

// MATRIX INVERSION

int		m44_invert(t_m44 input, t_m44 *result);
int		m44_is_identity_matrix(t_m44 matrix);

// OTHER UTILS (could be put in generic util file)

float	ft_rad(float angle);
void	swap_floats(float *a, float *b);

#endif