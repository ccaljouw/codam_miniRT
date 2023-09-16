/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 22:32:55 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/16 15:23:11 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include <stdlib.h>
# include <math.h>
# include "../../libs/libft/libft.h"
# include "../../includes/miniRT.h"

typedef struct s_m44
{
	float	arr[4][4];
}	t_m44;

// MATRIX UTILS

t_m44	m44_init(void);
void	m44_print(t_m44 matrix);
void	m44_copy(t_m44	src, t_m44 *dst);
t_m44	m44_dot_product(t_m44 m1, t_m44 m2);
void	m44_multiply_vec3(t_m44 matrix, t_xyz *point);


// MATRIX TRANSFORMATIONS

void	m44_rotate(t_m44 *matrix, float angle, char axis);
void	m44_scale(t_m44 *matrix, float x, float y, float z);
void	m44_translate(t_m44 *matrix, float x, float y, float z);

// THIS SHOULD BE IN MATH.H

float	ft_rad(float angle);

#endif