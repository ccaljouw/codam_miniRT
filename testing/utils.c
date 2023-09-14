/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:03:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 17:02:26 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"

void	print_vector(t_xyz vector)
{
	printf("[%.3f, %.3f, %.3f]", vector.x, vector.y, vector.z);
}

char	*vtostr(t_xyz vector)
{
	char *str;
	
	str = malloc(sizeof(char) * 50);
	snprintf(str, 50, "%.3f,%.3f,%.3f", vector.x, vector.y, vector.z);
	return (str);
}

void	compare(char *result, char *check, int test)
{
	if (!ft_strcmp(result, check))
		printf("\033[32;1mTest %d:\tOK!\n\033[0m", test);
	else
		printf("\033[31;1mTest %d:\tKO!\033[0m\n   expected:\t%s\n   result:\t%s\n", test, check, result);
		
}