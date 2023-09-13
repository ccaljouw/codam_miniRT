/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:29:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 10:05:24 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_xyz(char *param, t_xyz *position, t_scene *data)
{
	char	**input;
	int		i;

	i = 0;
	input = ft_split(param, ',');
	if (!input)
		exit_error(ERROR_MEM, NULL, data);
	while (input[i])
		i++;
	if (i != 3)
		exit_error(ERROR_XYZ, NULL, data);
	(void)position;
	printf("set xyz\n");
}

void	set_rgb(char *param, uint32_t *rgb, t_scene *data)
{
	char	**input;
	int		i;

	i = 0;
	input = ft_split(param, ',');
	if (!input)
		exit_error(ERROR_MEM, NULL, data);
	while (input[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RGB, NULL, data);
	rgb[0] = ft_atou_base(input[0], "0123456789", "");
	rgb[1] = ft_atou_base(input[1], "0123456789", "");
	rgb[2] = ft_atou_base(input[2], "0123456789", "");
	printf("rbg set to:%u, %u, %u\n", rgb[0], rgb[1], rgb[2]);
	if ((!rgb[0] && ft_strcmp(input[0], "0")) \
			|| (!rgb[1] && ft_strcmp(input[1], "0")) \
			|| (!rgb[2] && ft_strcmp(input[2], "0")) )
		exit_error(ERROR_RGB, NULL, data);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		exit_error(ERROR_RGB, NULL, data);
}

float	to_float(char *param)
{
	float n;
	n = 0;
	(void)param;
	printf("convert to float\n");
	return n;
}

void	parse_type(char *line, t_scene *data)
{
	int			i;
	char		**param;
	static char	*type[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static t_f	*parse[6] = {ambient, camera, light, sphere, plane, cylinder};

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
			break ;
		}
		i++;
	}
	if (i == 6)
		exit_error(ERROR_SCENE, line, data);
	free(param);
}
