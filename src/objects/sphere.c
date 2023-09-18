/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/17 19:19:51 by cariencaljo   ########   odam.nl         */
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

bool	sphere0(t_t *t, t_xyz vL, t_xyz vD, t_object *sphere)
{
	float t_ca;
	float t_hc;
	float d2;
	
	t_ca = v_dot(vL, vD);
	if (t_ca < 0)
		return false;
	
	d2 = v_dot(vL, vL) - (t_ca * t_ca);
	if (d2 > pow(sphere->diameter / 2, 2))
		return false;
	
	t_hc = sqrt(pow(sphere->diameter / 2, 2) - d2);
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

bool	sphereOffCentre(t_t *t, t_ray castRay, t_object *sphere, t_xyz nD)
{
	float a;
	float b;
	float c;
	
	a = v_dot(castRay.p1_p2, castRay.p1_p2);
	b = v_dot(v_subtract(castRay.p1, sphere->pOrigin), v_mulitply(nD, 2.0));
	c = v_dot(v_subtract(castRay.p1, sphere->pOrigin), v_subtract(castRay.p1, sphere->pOrigin)) - pow(sphere->diameter/2, 2);
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

bool	testHitSP(t_ray castRay, t_object *sphere, float *intPoint)
{
	t_xyz 	vL;
	t_xyz 	nD;
	t_t		t;
	
	vL = v_subtract(sphere->pOrigin , castRay.p1);
	nD = v_normalize(castRay.p1_p2);
	t.t0 = INFINITY;
	t.t1 = INFINITY;
	if (sphere->pOrigin.x == 0 && sphere->pOrigin.y == 0 && sphere->pOrigin.z == 0)
	{
		if (sphere0(&t, vL, nD, sphere) == false)
			return false;
	}
	else
	{
		if (sphereOffCentre(&t, castRay, sphere, nD) == false)
			return false;
	}
	*intPoint = t.t0;
	return true;
}

