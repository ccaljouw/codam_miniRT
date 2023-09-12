/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:29:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 18:48:54 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

#include <stdio.h> //remove

void	parse_type(char *line, t_scene *data)
{
	int		i;
	char	**args;
	// char	*type[6] = {"A", "C", "L", "sp", "pl", "cy"};

	i = 0;
	args = ft_split(line, ' ');
	if (!args)
		exit_error(ERROR_MEM, data);
	while (args[i]) {
		printf("%s\n", args[i++]);
	}
	free(args);
}