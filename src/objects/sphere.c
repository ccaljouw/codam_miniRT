/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/16 14:10:22 by cariencaljo   ########   odam.nl         */
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

bool	sphere0(t_t *t, t_xyz vL, t_xyz vD, t_sphere *sphere)
{
	float t_ca;
	float t_hc;
	float d2;
	
	t_ca = v_dot(vL, vD);
	if (t_ca < 0)
		return false;
	
	d2 = v_dot(vL, vL) - (t_ca * t_ca);
	if (d2 > pow(sphere->radius, 2))
		return false;
	
	t_hc = sqrt(pow(sphere->radius, 2) - d2);
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

bool	sphereOffCentre(t_t *t, t_ray castRay, t_sphere *sphere)
{
	t_xyz vD;
	float a;
	float b;
	float c;
	
	vD = v_normalize(castRay.p1_p2);
	a = v_dot(castRay.p1_p2, castRay.p1_p2);
	b = v_dot(v_subtract(castRay.p1, sphere->pC), v_mulitply(vD, 2.0));
	c = v_dot(v_subtract(castRay.p1, sphere->pC), v_subtract(castRay.p1, sphere->pC)) - pow(sphere->radius, 2);
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
	t_xyz 	vL;
	t_xyz 	vD;
	t_t		t;
	
	vL = v_subtract(sphere->pC , castRay.p1);
	vD = v_normalize(castRay.p1_p2);
	t.t0 = 0;
	t.t1 = 0;
	if (sphere->pC.x == 0 && sphere->pC.y == 0 && sphere->pC.z == 0)
	{
		if (sphere0(&t, vL, vD, sphere) == false)
			return false;
	}
	else
	{
		if (sphereOffCentre(&t, castRay, sphere) == false)
			return false;
	}
	// keep track of t0 for rendering multiple objects
	*localColor = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | 255);
	return true;
}

