/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 20:22:08 by cariencaljo   ########   odam.nl         */
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
	t_plane		*new_plane;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_PLANE, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_plane = malloc(sizeof(t_plane));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, scene);
	new_plane->point = set_xyz(param[1], scene);
	new_plane->normal_v = set_xyz(param[2], scene);
	set_rgb(param[3], &new_plane->color, scene);
	new_node->content = (void *)new_plane;
	ft_lstadd_back(&scene->planes, new_node);
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
	t_cylinder	*new_cylinder;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 6)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = malloc(sizeof(t_list));
	new_cylinder = malloc(sizeof(t_cylinder));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, scene);
	new_cylinder->center = set_xyz(param[1], scene);
	new_cylinder->axis_v = set_xyz(param[2], scene);
	new_cylinder->diameter = to_float(param[3], scene);
	new_cylinder->height = to_float(param[4], scene);
	set_rgb(param[5], &new_cylinder->color, scene);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->cylinders, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
}
