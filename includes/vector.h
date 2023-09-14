/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:21:26 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 09:17:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct xyz_s
{
	double	x;
	double	y;
	double	z;
}			t_xyz;

t_xyz	v_create(double x, double y, double z);
t_xyz	v_add(t_xyz a, t_xyz b);
t_xyz	v_subtract(t_xyz a, t_xyz b);
t_xyz	vs_mulitply(t_xyz a, double b);
double	v_dot(t_xyz a, t_xyz b);
t_xyz	v_cross(t_xyz a, t_xyz b);

#endif
