/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 17:54:01 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 22:53:09 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief tests for intersection (based on hardcoded sphere)
 * 
 * @param castRay (t_xyz) ray cast from the camera viewpoint
 * @param intPoint (t_xyz) point of intersection
 * @param localNormal 
 * @param localColor 
 * @return true 
 * @return false 
 */
bool	test_intersection(t_ray castRay, t_xyz localNormal, int *localColor, t_sphere *sphere)
{
	t_xyz	vhat;
	t_xyz	abc;
	t_xyz	intPoint;
	float	intersection;
	float	t1;
	float	t2;
	// float	minDist;
	// float	maxDist;
	float	dist;
	float	newA;
	
	(void)localNormal;
	// minDist = exp(6);
	// maxDist = 0.0;
	vhat = v_copy(castRay.p1_p2);
	v_normalize(&vhat);
	abc = v_create(1.0, 2.0 * v_dot(castRay.p1, vhat), v_dot(castRay.p1, castRay.p1) - 1.0);
	intersection = (abc.y * abc.y) - 4 * abc.x * abc.z;
	if (intersection > 0.0)
	{
		t1 = (-abc.y + sqrt(intersection)) / 2.0;
		t2 = (-abc.y - sqrt(intersection)) / 2.0;
		if (t1 < 0 || t2 < 0)
			return false;
		else
		{
			if (t1 < t2)
				intPoint = v_copy(v_add(castRay.p1, v_mulitply(vhat, t1)));
			else
				intPoint = v_copy(v_add(castRay.p1, v_mulitply(vhat, t2)));
			dist = v_magnitude(v_subtract(intPoint, castRay.p1));
			newA = 255 - ((dist -9) / 0.94605) * 255;
			*localColor = (sphere->rgb[0] << 24 | sphere->rgb[1] << 16 | sphere->rgb[2] << 8 | (uint32_t)newA);
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
