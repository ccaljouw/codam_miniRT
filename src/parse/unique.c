/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 12:30:58 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ambient(char **param, t_scene *data)
{
	int	i;

	if (data->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lightning", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->ambient = malloc(sizeof(t_ambient));
	if (!data->ambient)
		exit_error(ERROR_MEM, NULL, data);
	data->ambient->ratio = to_float(param[1], data);
	set_rgb(param[2], data->ambient->rgb, data);
	ft_putstr_fd("\033[34;1mAmbient lightning config: \033[0m", 1);
}

void	camera(char **param, t_scene *data)
{
	int	i;

	if (data->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->camera = malloc(sizeof(t_camera));
	if (!data->camera)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], data->camera->view_point, data);
	set_xyz(param[2], data->camera->orientation_v, data);
	data->camera->fov = ft_atoi(param[3]);
	if (!data->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, data);
	// printf("set to int:%d\n", data->camera->fov); // testing
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

void	light(char **param, t_scene *data)
{
	int	i;

	if (data->light)
		exit_error(ERROR_SCENE, "redefinition of light", data);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->light = malloc(sizeof(t_light));
	if (!data->light)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], data->light->light_point, data);
	data->light->brightness = to_float(param[2], data);
	set_rgb(param[3], data->light->rgb, data);
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}
