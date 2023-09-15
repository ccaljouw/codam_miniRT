/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:38:15 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/15 10:38:45 by cariencaljo   ########   odam.nl         */
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
	return (0);
}