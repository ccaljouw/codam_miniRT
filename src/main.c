/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 16:53:16 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		exit_error(ERROR_ARGS);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH);
}

int	main(int argc, char **argv)
{
	check_args(argc, argv);
	return (0);
}
