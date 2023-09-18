/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/18 20:18:34 by cariencaljo   ########   odam.nl         */
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

bool	sphere0(t_t *t, t_ray camRay, t_object *sphere)
{
	t_xyz distance; //cam origin to sphere origin
	float t_ca;
	float t_hc;
	float d2;
	
	distance = v_subtract(sphere->pOrigin, camRay.p1); // distance between sphere origin & cam origin
	t_ca = v_dot(distance, v_normalize(camRay.p1_p2)); // distance * direction
	if (t_ca < 0)
		return false;
	
	d2 = v_dot(distance, distance) - (t_ca * t_ca); // squared magnitude distance - t_ca suared
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

bool	sphereOffCentre(t_t *t, t_ray castRay, t_object *sphere)
{
	float a;
	float b;
	float c;
	
	a = v_dot(castRay.p1_p2, castRay.p1_p2);
	b = v_dot(v_subtract(castRay.p1, sphere->pOrigin), v_mulitply(v_normalize(castRay.p1_p2), 2.0));
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
	t_t		t;
	
	t.t0 = 0;
	t.t1 = 0;
	if (sphere->pOrigin.x == 0 && sphere->pOrigin.y == 0 && sphere->pOrigin.z == 0)
	{
		if (sphere0(&t, castRay, sphere) == false)
			return false;
	}
	else
	{
		if (sphereOffCentre(&t, castRay, sphere) == false)
			return false;
	}
	*intPoint = t.t0;
	return true;
}

