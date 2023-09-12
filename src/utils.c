/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:44:22 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 16:54:29 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	exit_error(char *error_msg)
{
	ft_putendl_fd(error_msg, 2);
	exit (1);
}