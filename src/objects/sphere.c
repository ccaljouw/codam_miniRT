/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/15 22:07:06 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


bool solveQuadratic(float a, float b, float c, t_t *t)
{
	float discr;
	float q;
	
	discr = b * b - 4 * a * c;
	if (discr < 0)
		return false;
	else if (discr == 0)
	{
		t->t0 = -0.5 * b / a;
		t->t1 = t->t0;
	}
	else
	{
		if (b > 0)
			q = -0.5 * (b + sqrt(discr));
		else
			q = -0.5 * (b - sqrt(discr));
		t->t0 = q / a;
		t->t1 = c / q;
	}
	return true;	
}

bool	sphere_0(t_t *t, t_xyz _L, t_xyz _D, t_sphere *sphere)
{
	float t_ca;
	float t_hc;
	float d2;
	
	t_ca = v_dot(_L, _D);
	if (t_ca < 0)
		return false;
	
	d2 = v_dot(_L, _L) - (t_ca * t_ca);
	if (d2 > pow(sphere->diameter/2, 2))
		return false;
	
	t_hc = sqrt(pow(sphere->diameter/2, 2) - d2);
	t->t0 = t_ca - t_hc;
	t->t1 = t_ca + t_hc;
	if (t->t0 > t->t1)
		swap(&t->t0, &t->t1);
	if (t->t0 < 0)
	{
		t->t0 = t->t1;
		if (t->t0 < 0)
			return false;
	}
	return true;
}

bool	sphere_offCentre(t_t *t, t_ray castRay, t_sphere *sphere)
{
	t_xyz _D;
	float a;
	float b;
	float c;
	
	_D = v_copy(castRay.p1_p2);
	v_normalize(&_D);
	a = v_dot(castRay.p1_p2, castRay.p1_p2);
	b = v_dot(v_subtract(castRay.p1, sphere->center), v_mulitply(_D, 2.0));
	c = v_dot(v_subtract(castRay.p1, sphere->center), v_subtract(castRay.p1, sphere->center)) - pow(sphere->diameter / 2, 2);
	if (!solveQuadratic(a, b, c, t))
		return false;
	if (t->t0 > t->t1)
		swap(&t->t0, &t->t1);
	if (t->t0 < 0)
	{
		t->t0 = t->t1;
		if (t->t0 < 0)
			return false;
	}
	return true;
}

bool	test_spIntersection(t_ray castRay, int *localColor, t_sphere *sphere)
{
	t_xyz 	_L;
	t_xyz 	_D;
	t_t		t;
	
	_L = v_subtract(sphere->center , castRay.p1);
	_D = v_copy(castRay.p1_p2);
	v_normalize(&_D);
	t.t0 = 0;
	t.t1 = 0;
	if (sphere->center.x == 0 && sphere->center.y == 0 && sphere->center.z == 0)
	{
		if (sphere_0(&t, _L, _D, sphere) == false)
			return false;
	}
	else
	{
		if (sphere_offCentre(&t, castRay, sphere) == false)
			return false;
	}
	// keep track of t0 for rendering multiple objects
	*localColor = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | 255);
	return true;
}

