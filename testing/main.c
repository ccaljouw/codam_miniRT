/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:38:15 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/16 15:24:51 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"

void leaks(void)
{
	system("leaks miniRT -q");
}

int main(void)
{
	int i;

	// atexit(leaks);
	i = 1;
	i += cameratest(i);

	t_m44	test;
	t_m44	p_test;
	t_xyz	point;

	test = m44_init();
	m44_copy(test, &p_test);
	m44_print(test);
	m44_print(p_test);
	m44_rotate(&test, 23.0, 'x');
	m44_rotate(&p_test, 23.0, 'z');
	m44_print(test);
	m44_print(p_test);
	// prod = 
	point = v_create(1.0, 2.0, 3.0);
	m44_print(m44_dot_product(p_test, test));
	print_vector(point);
	m44_multiply_vec3(test, &point);
	print_vector(point);
	m44_print(p_test);
	m44_copy(test, &p_test);
	m44_print(p_test);
	// free(p_test);
	return (0);
}