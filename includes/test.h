/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:19:24 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/21 21:53:18 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "miniRT.h"
#include <stdio.h>

void	print_vector(t_xyz vector);
// void	print_camera(t_camera cam);
char	*vtostr(t_xyz vector);
void	compare(char *result, char *check, int test);

#endif