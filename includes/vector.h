/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:21:26 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/16 14:13:19 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

/**
 * @brief struct with points x, y and z. Can be used to represent 
 * either a point, vector or normal
 */
typedef struct xyz_s
{
	float	x;
	float	y;
	float	z;
}			t_xyz;

t_xyz	v_create(float x, float y, float z);
t_xyz	v_copy(t_xyz a);
void	v_copyValues(t_xyz a, t_xyz *b);
t_xyz	v_add(t_xyz a, t_xyz b);
t_xyz	v_subtract(t_xyz a, t_xyz b);
t_xyz	v_mulitply(t_xyz a, float b);
t_xyz	v_devide(t_xyz a, float b);
float	v_dot(t_xyz a, t_xyz b);
t_xyz	v_cross(t_xyz a, t_xyz b);
float	v_magnitude(t_xyz a);
t_xyz	v_normalize(t_xyz a);
void	v_normalizep(t_xyz *a);

#endif
