/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:19:24 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/17 13:36:33 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "miniRT.h"
#include <stdio.h>

void	print_vector(t_xyz vector);
void	print_camera(t_camera cam);
char	*vtostr(t_xyz vector);
void	compare(char *result, char *check, int test);

int		cameratest(int testnr);
#endif