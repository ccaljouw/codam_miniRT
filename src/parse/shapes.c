/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:39:58 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 21:23:43 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_sphere(char **param, t_scene *data)
{
	printf("print sphere id:%s\n", param[0]);
	(void)data;
}

void	parse_plane(char **param, t_scene *data)
{
	printf("print plane, id:%s\n", param[0]);
	(void)data;
}

void	parse_cylinder(char **param, t_scene *data)
{
	printf("print cylinder id:%s\n", param[0]);
	(void)data;
}

