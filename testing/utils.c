/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   testutils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:03:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 14:38:07 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_vector(t_xyz vector)
{
	printf("[%f, %f, %f]", vector.x, vector.y, vector.z);
}

char	*vtostr(t_xyz vector)
{
	char *str;
	
	str = malloc(sizeof(char) * 50);
	snprintf(str, 50, "%f,%f,%f", vector.x, vector.y, vector.z);
	return (str);
}

void	compare(char *result, char *check, char *test)
{
	if (!ft_strcmp(result, check))
		printf("%s:\tOK!\n", test);
	else
		printf("%s:\tKO!, should be: %s, is: %s\n", test, check, result);
		
}