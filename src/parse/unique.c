/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/23 21:47:17 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	cameraGeometry(t_scene *scene)
{
	t_camera	*cam;
	t_m44	direction;

	cam = scene->camera;
	cam->image_width = scene->p_width;
	cam->image_height = scene->p_height;
	cam->aspect_ratio = (float)scene->p_width / scene->p_height;
	cam->fov_scale = tan(ft_rad(cam->fov * 0.5));
	cam->cam2world = m44_init();
	m44_translate(&cam->cam2world, \
				cam->view_point.x, cam->view_point.y, cam->view_point.z);
	direction = m44_from_direction_vector(cam->orientation_v);
	cam->cam2world = m44_dot_product(direction, cam->cam2world);
	m44_multiply_vec3(cam->cam2world, v_create(0, 0, 0), &cam->origin);
	cam->fov_scale = tan(ft_rad(cam->fov * 0.5));
}

void	init_camera(char **param, t_scene *scene)
{
	int	i;

	if (scene->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		exit_error(ERROR_MEM, NULL, scene);
	scene->camera->view_point = set_xyz(param[1], scene);
	scene->camera->orientation_v = set_xyz(param[2], scene);
	scene->camera->fov = ft_atoi(param[3]);
	if (!scene->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, scene);
	cameraGeometry(scene);
	// print_camera(*(scene->camera)); //testing
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

/**
 * @brief Initialises ambient lighting in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_ambient(char **param, t_scene *scene)
{
	int			i;
	t_ambient	*ambient; // added this to keep the lines under 80 chars.

	if (scene->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lighting", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	ambient = malloc(sizeof(t_ambient));
	if (!ambient)
		exit_error(ERROR_MEM, NULL, scene);
	ambient->ratio = to_float(param[1], scene);
	set_rgb(param[2], ambient->rgb, scene);
	ambient->rgb_ratio[0] = ((float)ambient->rgb[0] / 255) * ambient->ratio;	// calculate ratios here to assure its only done once
	ambient->rgb_ratio[1] = ((float)ambient->rgb[1] / 255) * ambient->ratio;
	ambient->rgb_ratio[2] = ((float)ambient->rgb[2] / 255) * ambient->ratio;
	scene->ambient = ambient;
	ft_putstr_fd("\033[34;1mAmbient lighting config: \033[0m", 1);
}

/**
 * @brief Initialises the light in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_light(char **param, t_scene *scene)
{
	int	i;

	if (scene->light)
		exit_error(ERROR_SCENE, "redefinition of light", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_LIGHT, "incorrect number of arguments", scene);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		exit_error(ERROR_MEM, NULL, scene);
	scene->light->light_point = set_xyz(param[1], scene);
	scene->light->brightness = to_float(param[2], scene);
	set_rgb(param[3], scene->light->rgb, scene);
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}

void	init_resolution(char **param, t_scene *scene)
{
	int	i;

	i = 0;
	if (scene->p_width)
		exit_error(ERROR_SCENE, "redefinition of resolution", scene);
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RES, "incorrect number of arguments", scene);
	set_image_size(scene, to_float(param[1], scene),to_float(param[2], scene));
	ft_putstr_fd("\033[34;1mResolution config:\t\t  \033[0m", 1);
}
