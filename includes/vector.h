/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 17:21:26 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 13:14:02 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct xyz_s
{
	float	x;
	float	y;
	float	z;
}			t_xyz;

t_xyz	v_create(float x, float y, float z);
t_xyz	v_add(t_xyz a, t_xyz b);
t_xyz	v_subtract(t_xyz a, t_xyz b);
t_xyz	v_mulitply(t_xyz a, float b);
float	v_dot(t_xyz a, t_xyz b);
t_xyz	v_cross(t_xyz a, t_xyz b);
float	v_magnitude(t_xyz a);
void	v_normalize(t_xyz *a);

#endif
