/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:39:58 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/09 22:12:28 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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
	if (i != 11)
		exit_error(ERROR_PLANE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_plane = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, scene);
	new_plane->id = PL;
	new_plane->p_origin = set_xyz(param[1], scene);
	new_plane->v_normal = set_xyz(param[2], scene);
	new_plane->rotate_matrix = m44_init();
	set_surface_properties(param, new_plane, 3, scene);
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
	if (i != 13)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cylinder = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, scene);
	new_cylinder->id = CY;
	new_cylinder->p_origin = set_xyz(param[1], scene);
	new_cylinder->v_normal = v_normalize(set_xyz(param[2], scene));
	new_cylinder->diameter = to_float(param[3], scene);
	new_cylinder->height = to_float(param[4], scene);
	new_cylinder->rotate_matrix = m44_rotate_axis(180, 'y');
	set_surface_properties(param, new_cylinder, 5, scene);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
}

/**
 * @brief Initialises a cylinder in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_cone(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_cone;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 13)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cone = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cone)
		exit_error(ERROR_MEM, NULL, scene);
	new_cone->id = CO;
	new_cone->p_origin = set_xyz(param[1], scene);
	new_cone->v_normal = v_normalize(set_xyz(param[2], scene));
	new_cone->diameter = to_float(param[3], scene);
	new_cone->height = to_float(param[4], scene);
	new_cone->rotate_matrix = m44_rotate_axis(180, 'y');
	set_surface_properties(param, new_cone, 5, scene);
	new_node->content = (void *)new_cone;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCone config:\t\t  \033[0m", 1);
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
	if (i != 11)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_sphere = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_sphere)
		exit_error(ERROR_MEM, NULL, scene);
	new_sphere->id = SP;
	new_sphere->v_normal = v_create(0, 1, 0);
	new_sphere->p_origin = set_xyz(param[1], scene);
	new_sphere->diameter = to_float(param[2], scene);
	new_sphere->rotate_matrix = m44_init();
	set_surface_properties(param, new_sphere, 3, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
}
