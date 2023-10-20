/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:39:58 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/19 23:21:26 by albertvanan      ###   ########.fr       */
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
	if (i != 4 && i != 4 + BONUS * BONUS_SPECS)
		exit_error(ERROR_PLANE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_plane = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_plane)
		exit_error(ERROR_MEM, NULL, scene);
	new_plane->id = PL;
	new_plane->p_origin = set_xyz(param[1], scene);
	new_plane->v_normal = set_xyz(param[2], scene);
	new_plane->rotate_matrix = m44_init();
	new_plane->plane_y = scene->file_height * 0.05;
	new_plane->plane_x = scene->file_width * 0.05;
	set_surface_properties(&param[3], new_plane, i - BONUS_SPECS, scene);
	new_node->content = (void *)new_plane;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mPlane config:\t\t\033[0m", 1);
}

static void	set_cylco_params(char **p, t_scene *scene, t_object *cylco, int i)
{
	cylco->p_origin = set_xyz(p[1], scene);
	cylco->v_normal = v_normalize(set_xyz(p[2], scene));
	cylco->diameter = to_float(p[3], scene);
	cylco->height = to_float(p[4], scene);
	cylco->rotate_matrix = m44_rotate_axis(180, 'y');
	set_surface_properties(&p[5], cylco, i - BONUS_SPECS, scene);
}

/**
 * @brief Initialises a cylinder in the scene.
 * 
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_cyl(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_cylinder;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 6 && i != 6 + BONUS * BONUS_SPECS)
		exit_error(ERROR_CYLINDER, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cylinder = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cylinder)
		exit_error(ERROR_MEM, NULL, scene);
	if (!ft_strcmp(param[0], "cy"))
		new_cylinder->id = CY;
	else
		new_cylinder->id = CCY;
	set_cylco_params(param, scene, new_cylinder, i);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t\033[0m", 1);
}

/**
 * @brief Initialises a cone in the scene.
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
	if (!BONUS)
		exit_error(ERROR_CONE, "cone not implemented in mandatory", scene);
	while (param[i])
		i++;
	if (i != 6 && i != 6 + BONUS_SPECS)
		exit_error(ERROR_CONE, "incorrect number of arguments", scene);
	new_node = ft_lstnew(NULL);
	new_cone = ft_calloc(1, sizeof(t_object));
	if (!new_node || !new_cone)
		exit_error(ERROR_MEM, NULL, scene);
	if (!ft_strcmp(param[0], "co"))
		new_cone->id = CO;
	else
		new_cone->id = CCO;
	set_cylco_params(param, scene, new_cone, i);
	new_node->content = (void *)new_cone;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCone config:\t\t\033[0m", 1);
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
	if (i != 4 && i != 4 + BONUS * BONUS_SPECS)
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
	set_surface_properties(&param[3], new_sphere, i - BONUS_SPECS, scene);
	new_node->content = (void *)new_sphere;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mSphere config:\t\t\033[0m", 1);
}
