/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:47:02 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:49:28 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	set_procedure(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > TEXT_PROCEDURES)
		exit_error("error texture procedure", "id invallid", scene);
	return (n);
}

int	set_bump_procedure(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > BUMP_PROCEDURES)
		exit_error("error bump map", "id invallid", scene);
	return (n);
}

float	set_albedo(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error albedo", "provide positive integer", scene);
	return ((float)n / 100.0);
}

float	set_specular_size(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error specular size", "provide positive integer", scene);
	return (300 / (float)n);
}

float	set_specular_weight(char *param, t_scene *scene)
{
	int	n;

	n = ft_atoi(param);
	if (n < 0)
		exit_error("error specular weight", "provide positive integer", scene);
	return ((float)n / 100);
}
