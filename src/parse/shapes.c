/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/17 19:13:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Initialises a plane in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_plane(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_plane;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_PLANE, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_plane = malloc(sizeof(t_object));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, scene);
	new_plane->id = PL;
	new_plane->pOrigin = set_xyz(param[1], scene);
	new_plane->vNormal = set_xyz(param[2], scene);
	set_rgb(param[3], new_plane->rgb, scene);
	new_node->content = (void *)new_plane;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mPlane config:\t\t  \033[0m", 1);
}

/**
 * @brief Initialises a cylinder in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_cylinder(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_cylinder;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 6)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_cylinder = malloc(sizeof(t_object));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, scene);
	new_cylinder->id = CY;
	new_cylinder->pOrigin = set_xyz(param[1], scene);
	new_cylinder->vAxis = set_xyz(param[2], scene);
	new_cylinder->diameter = to_float(param[3], scene);
	new_cylinder->height = to_float(param[4], scene);
	set_rgb(param[5], new_cylinder->rgb, scene);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
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
	t_object	*new_sphere;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_sphere = malloc(sizeof(t_object));
	if (!new_node || !new_sphere)
		exit_error(ERROR_MEM, NULL, scene);
	new_sphere->id = SP;
	new_sphere->pOrigin = set_xyz(param[1], scene);
	new_sphere->diameter = to_float(param[2], scene);
	set_rgb(param[3], new_sphere->rgb, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}
