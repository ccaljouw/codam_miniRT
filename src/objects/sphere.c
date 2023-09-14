/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 21:59:05 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief tests for intersection
 * 
 * @param castRay (t_xyz) ray cast from the camera viewpoint
 * @param intPoint 
 * @param localNormal 
 * @param localColor 
 * @return true 
 * @return false 
 */
bool	test_intersection(t_ray castRay, t_xyz *intPoint, t_xyz localNormal, int *localColor)
{
	t_xyz	vhat;
	t_xyz	temp;
	// float	a;
	float	b;
	float	c;
	float	intTest;
	float	testSqrt;
	float	t1;
	float	t2;
	
	(void)localNormal;
	(void)localColor;
	vhat = v_copy(castRay.p1_p2);
	v_normalize(&vhat);
	
	//compute values a, b and c
	// a = 1.0;
	b = 2.0 * v_dot(castRay.p1, vhat);
	c = v_dot(castRay.p1, castRay.p1) - 1.0;
	
	// test for intersection
	intTest = (b * b) - 4 * c;
	if (intTest > 0.0)
	{
		testSqrt = sqrt(intTest);
		t1 = (-b + testSqrt) / 2.0;
		t2 = (-b - testSqrt) / 2.0;
		if (t1 < 0 || t2 < 0)
			return false;
		else
		{
			if (t1 < t2)
				temp = v_add(castRay.p1, v_mulitply(vhat, t1));
			else
				temp = v_add(castRay.p1, v_mulitply(vhat, t2));
			intPoint->x = temp.x;
			intPoint->y = temp.y;
			intPoint->z = temp.z;
			return true;
		}
	}
	else
		return false;
}

/**
 * @brief Initialises a sphere in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_sphere(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_sphere	*new_sphere;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_sphere = malloc(sizeof(t_sphere));
	if (!new_node || !new_sphere)
		exit_error(ERROR_MEM, NULL, scene);
	new_sphere->center = set_xyz(param[1], scene);
	new_sphere->diameter = to_float(param[2], scene);
	set_rgb(param[3], new_sphere->rgb, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->spheres, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}
