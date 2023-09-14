/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:38:15 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 19:10:53 by cariencaljo   ########   odam.nl         */
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
	printf("%f\n", 1e6);
	printf("%f\n", exp(6));
	return (0);
}