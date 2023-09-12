/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unique.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 22:17:27 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_ambient(char **param, t_scene *data)
{
	(void)param;
	if (data->ambient)
		exit_error(ERROR_SCENE, NULL, data);
	data->ambient = malloc(sizeof(t_ambient));
	if (!data->ambient)
		exit_error(ERROR_MEM, NULL, data);
	// set values
	ft_putstr_fd("\033[34;1mAmbient lightning config: \033[0m", 1);
}

void	parse_camera(char **param, t_scene *data)
{
	(void)param;
		if (data->camera)
		exit_error(ERROR_SCENE, NULL, data);
	data->camera = malloc(sizeof(t_camera));
	if (!data->camera)
		exit_error(ERROR_MEM, NULL, data);
	// set values
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}

void	parse_light(char **param, t_scene *data)
{
	(void)param;
	if (data->light)
		exit_error(ERROR_SCENE, NULL, data);
	data->light = malloc(sizeof(t_light));
	if (!data->light)
		exit_error(ERROR_MEM, NULL, data);
	// set values
	ft_putstr_fd("\033[34;1mLigt config:\t\t  \033[0m", 1);
}