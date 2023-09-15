/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:19:24 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 19:59:03 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "../includes/miniRT.h"
#include <stdio.h>

void	print_vector(t_xyz vector);
void	print_camera(t_camera cam);
char	*vtostr(t_xyz vector);
void	compare(char *result, char *check, int test);

int	cameratest(int testnr);
#endif