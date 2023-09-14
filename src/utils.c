/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:44:22 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 14:02:41 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *error_msg, char *optional_str, t_scene *scene)
{
	ft_putendl_fd("\033[31;1mError", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": \033[0m", 2);
	if (optional_str)
		ft_putendl_fd(optional_str, 2);
	else
		ft_putchar_fd('\n', 2);
	(void)scene; //remove
	// if (scene)
	// 		cleanup scene
	exit (1);
}
