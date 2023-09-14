/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 11:50:11 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Initialises ambient lighting in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	ambient(char **param, t_scene *scene)
{
	int	i;

	if (scene->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lighting", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	scene->ambient = malloc(sizeof(t_ambient));
	if (!scene->ambient)
		exit_error(ERROR_MEM, NULL, scene);
	scene->ambient->ratio = to_float(param[1], scene);
	set_rgb(param[2], scene->ambient->rgb, scene);
	ft_putstr_fd("\033[34;1mAmbient lighting config: \033[0m", 1);
}

/**
 * @brief Initialises the camera in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	camera(char **param, t_scene *scene)
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
	// printf("set to int:%d\n", scene->camera->fov); // testing
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

/**
 * @brief Initialises the light in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	light(char **param, t_scene *scene)
{
	int	i;

	if (scene->light)
		exit_error(ERROR_SCENE, "redefinition of light", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	scene->light = malloc(sizeof(t_light));
	if (!scene->light)
		exit_error(ERROR_MEM, NULL, scene);
	scene->light->light_point = set_xyz(param[1], scene);
	scene->light->brightness = to_float(param[2], scene);
	set_rgb(param[3], scene->light->rgb, scene);
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}
