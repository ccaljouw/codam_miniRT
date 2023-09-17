/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 14:38:15 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/17 15:42:59 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"
// # include "../includes/miniRT.h"

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
	t_m44	invert;
	t_xyz	point;

	test = m44_init();
	m44_copy(test, &p_test);
	m44_print(test);
	m44_print(p_test);
	m44_rotate(&test, 23.0, 20.0, 100.0);
	m44_rotate(&p_test, 23.0, 20.0, 100.0);
	ft_printf("after rotate\n");
	m44_print(test);
	m44_print(p_test);
	point = v_create(1.0, 2.0, 3.0);
	m44_print(m44_dot_product(p_test, test));
	print_vector(point);
	m44_multiply_vec3(test, point, &point);
	print_vector(point);
	m44_print(p_test);
	m44_copy(test, &p_test);
	m44_print(p_test);
	m44_invert(p_test, &invert);
	m44_print(invert);
	ft_printf("first invert\n");
	m44_print(m44_dot_product(p_test, invert));
	m44_scale(&test, 10, 10, 10);
	ft_printf("scaled\n");
	m44_print(test);
	m44_translate(&test, 10, 10, 10);
	ft_printf("translated\n");
	m44_print(test);
	m44_invert(test, &invert);
	ft_printf("scaled inverted\n");
	m44_print(invert);
	ft_printf("last invert\n");
	m44_print(m44_dot_product(test, invert));
	m44_print(test);
	m44_rotate(&test, 10, 0 , 0);
	m44_print(test);
	return (0);
	
}