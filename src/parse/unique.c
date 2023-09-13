/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 00:25:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	ambient(char **param, t_scene *data)
{
	int	i;
		
	if (data->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lightning", data);
	i = 0;
	while(param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->ambient = malloc(sizeof(t_ambient));
	if (!data->ambient)
		exit_error(ERROR_MEM, NULL, data);
	data->ambient->ratio = to_float(param[1]);
	set_rgb(param[2], data->ambient->rgb);
	// if (!data->ambient->ratio || !data->ambient->rgb)
	// 	exit_error(ERROR_AMB, NULL, data);
	ft_putstr_fd("\033[34;1mAmbient lightning config: \033[0m", 1);
}

void	camera(char **param, t_scene *data)
{
	int	i;
	if (data->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", data);
	i = 0;
	while(param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->camera = malloc(sizeof(t_camera));
	if (!data->camera)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], data->camera->view_point);
	set_xyz(param[2], data->camera->orientation_v);
	data->camera->fov = to_float(param[3]);
	// if (!data->camera->view_point || !data->camera->orientation_v || !data->camera->fov)
	// 	exit_error(ERROR_CAM, NULL, data);
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

void	light(char **param, t_scene *data)
{
	int	i;

	if (data->light)
		exit_error(ERROR_SCENE, "redefinition of light", data);
	i = 0;
	while(param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", data);
	data->light = malloc(sizeof(t_light));
	if (!data->light)
		exit_error(ERROR_MEM, NULL, data);
	set_xyz(param[1], data->light->light_point);
	data->light->brightness = to_float(param[2]);
	set_rgb(param[3], data->light->rgb);
	// if (!data->light->light_point || !data->light->brightness || !data->light->rgb)
	// 	exit_error(ERROR_LIGHT, NULL, data);;
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}
