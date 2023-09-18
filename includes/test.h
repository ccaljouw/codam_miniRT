/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:19:24 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/18 22:47:26 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/miniRT.h"
#include <stdio.h>

void	print_vector(t_xyz vector);
void	print_camera2(t_camera2 cam);
char	*vtostr(t_xyz vector);
void	compare(char *result, char *check, int test);

int		camera2test(int testnr);
#endif