/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:29:40 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/13 16:39:03 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

static int	type_loop(char **param, char **type, t_f **parse, t_scene *scene)
{
	int	i;

	i = 0;
	while (param[0] && i < 10)
	{
		if (!ft_strcmp(type[i], param[0]))
		{
			parse[i](param, scene);
			print_param_line(param);
			break ;
		}
		i++;
	}
	return (i);
}

/**
 * @brief Takes an input line and parses this into the correct type
 * 
 * @param line (char **) input line
 * @param scene (t_scene) passed to clean up when input is invallid
 */
void	parse_type(char *line, t_scene *scene)
{
	int			i;
	char		**param;
	static char	*type[10] = {"A", "C", "l", "L", "sp", \
							"pl", "cy", "R", "co", "tr"};
	static t_f	*parse[10] = {init_ambient, init_camera, init_lights, \
							init_lights, init_sphere, init_plane, init_cyl, \
							init_resolution, init_cone, init_triangle};

	replace(line, ' ', '\t');
	param = ft_split(line, '\t');
	if (!param)
		exit_error(ERROR_MEM, NULL, scene);
	i = type_loop(param, type, parse, scene);
	if (i == 10)
		exit_error(ERROR_SCENE, "incorrect type", scene);
	ft_clean_split_arr(&param);
}

void	parse_file(char *file, t_scene *scene)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line)
		{
			if (line[0] == '\n' || line[0] == '#')
			{
				free(line);
				continue ;
			}
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			parse_type(line, scene);
			free(line);
		}
		else
			break ;
	}
	close(fd);
}
