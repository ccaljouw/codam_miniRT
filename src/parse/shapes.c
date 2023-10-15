/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/15 13:09:19 by cariencaljo   ########   odam.nl         */
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
	new_cylinder->id = CY;
	new_cylinder->p_origin = set_xyz(param[1], scene);
	new_cylinder->v_normal = v_normalize(set_xyz(param[2], scene));
	new_cylinder->diameter = to_float(param[3], scene);
	new_cylinder->height = to_float(param[4], scene);
	new_cylinder->rotate_matrix = m44_rotate_axis(180, 'y');
	set_surface_properties(&param[5], new_cylinder, i - BONUS_SPECS, scene);
	new_node->content = (void *)new_cylinder;
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mCylinder config:\t\033[0m", 1);
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
	new_cone->id = CO;
	new_cone->p_origin = set_xyz(param[1], scene);
	new_cone->v_normal = v_normalize(set_xyz(param[2], scene));
	new_cone->diameter = to_float(param[3], scene);
	new_cone->height = to_float(param[4], scene);
	new_cone->rotate_matrix = m44_rotate_axis(180, 'y');
	set_surface_properties(&param[5], new_cone, i - BONUS_SPECS, scene);
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

void min_max_values(float *min_max, t_object *tr)
{
	int		i;

	i = 0;
	min_max[0] = 1000000;
	min_max[1] = -1000000;
	min_max[2] = 1000000;
	min_max[3] = -1000000;
	while (i < 3)
	{
		if (tr->p[i].x < min_max[0])
			min_max[0] = tr->p[i].x;
		if (tr->p[i].x > min_max[1])
			min_max[1] = tr->p[i].x;
		if (tr->p[i].y < min_max[2])
			min_max[2] = tr->p[i].y;
		if (tr->p[i].y > min_max[3])
			min_max[3] = tr->p[i].y;
		i++;
	}
}

void	triangle_vectors(t_object *tr)
{
	t_xyz	p0p1;
	t_xyz	p0p2;
	float	min_max[4];

	p0p1 = v_subtract(tr->p[1], tr->p[0]);
	p0p2 = v_subtract(tr->p[2], tr->p[0]);
	tr->v_normal = v_normalize(v_cross(p0p1, p0p2));
	tr->edge[0] = v_subtract(tr->p[1], tr->p[0]);
	tr->edge[1] = v_subtract(tr->p[2], tr->p[1]);
	tr->edge[2] = v_subtract(tr->p[0], tr->p[2]);
	min_max_values(min_max, tr);
	tr->plane_y = min_max[3] - min_max[2];
	tr->plane_x = min_max[1] - min_max[0];
}

void	init_triangle(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_tr;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (!BONUS)
		exit_error(ERROR_TR, "triangle not implemented in mandatory", scene);
	if (i != 5 && i != 5 + BONUS_SPECS)
		exit_error(ERROR_TR, "incorrect number of arguments", scene);
	new_tr = ft_calloc(1, sizeof(t_object));
	new_node = ft_lstnew(new_tr);
	if (!new_tr || !new_node)
		exit_error(ERROR_MEM, NULL, scene);
	new_tr->id = TR;
	// new_tr->v_normal = set_xyz(param[1], scene);
	new_tr->p[0] = set_xyz(param[1], scene);
	new_tr->p[1] = set_xyz(param[2], scene);
	new_tr->p[2] = set_xyz(param[3], scene);
	new_tr->rotate_matrix = m44_init();
	triangle_vectors(new_tr);
	set_surface_properties(&param[4], new_tr, i - BONUS_SPECS, scene);
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mTriangle config:\t\033[0m", 1);
}
