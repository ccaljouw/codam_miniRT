/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 20:21:53 by cariencaljo   ########   odam.nl         */
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
bool	test_intersection(t_ray castRay, t_xyz intPoint, t_xyz localNormal, int *localColor)
{
	t_xyz	vhat;
	// float	a;
	float	b;
	float	c;
	float	intersection;
	
	(void)intPoint;
	(void)localNormal;
	(void)localColor;
	//compute values a, b and c
	vhat = v_copy(castRay.p1_p2);
	v_normalize(&vhat);
	
	/* note that a is equal to the squared magnitude of the direction
	of the cast ray. As this will be a unit vector we can conclude that the valu of a
	will allways be 1 */
	// a = 1.0;
	
	b = 2.0 * v_dot(castRay.p1, vhat);
	// printf("\nb: %f\n", b);
	// taking dot product of same vector is the same as taking the squared magnitude
	c = v_dot(castRay.p1, castRay.p1) - 1.0;
	
	// test for intersection
	intersection = (b * b) - 4 * c;
	// printf("intersection: %f\n", intersection);
	if (intersection > 0.0)
		return 1;
	else
		return 0;
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
	set_rgb(param[3], &new_sphere->color, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->spheres, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}
