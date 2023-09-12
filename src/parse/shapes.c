/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 22:23:53 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_sphere(char **param, t_scene *data)
{
	// set values
	ft_putstr_fd("\033[34;1mSphere config:\t\t  \033[0m", 1);
	(void)data;
	(void)param;
}

void	parse_plane(char **param, t_scene *data)
{
	// set values
	ft_putstr_fd("\033[34;1mPlane config:\t\t  \033[0m", 1);
	(void)data;
	(void)param;
}

void	parse_cylinder(char **param, t_scene *data)
{
	// set values
	ft_putstr_fd("\033[34;1mCylinder config:\t  \033[0m", 1);
	(void)data;
	(void)param;
}

