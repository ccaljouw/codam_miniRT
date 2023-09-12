/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:29:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 22:12:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	parse_type(char *line, t_scene *data)
{
	int		i;
	char	**param;
	char	*type[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static 	t_function *parse[6] = {parse_ambient, parse_camera, parse_light, \
									parse_sphere, parse_plane, parse_cylinder};

	i = 0;
	param = ft_split(line, '\t');
	if (!param)
		exit_error(ERROR_MEM, NULL, data);
	while (i < 6)
	{
		if (!ft_strcmp(type[i], param[0]))
		{
			parse[i](param, data);
			ft_putstr_fd(line, 1);
			break;
		}
		i++;
	}
	if (i == 6)
		exit_error(ERROR_SCENE, line, data);
	free(param);
}
