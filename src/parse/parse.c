/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:29:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/14 20:20:54 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

/**
 * @brief Returns the xyz object based on string input
 * 
 * @param param (char **) comma seperated string input ("x,y,z")
 * @param scene (t_scene) passed to clean up when input is invallid
 * @return t_xyz 
 */
t_xyz	set_xyz(char *param, t_scene *scene)
{
	char	**input;
	t_xyz	position;
	int		i;

	i = 0;
	input = ft_split(param, ',');
	if (!input)
		exit_error(ERROR_MEM, NULL, scene);
	while (input[i])
		i++;
	if (i != 3)
		exit_error(ERROR_XYZ, NULL, scene);
	position = v_create(to_float(input[0], scene), to_float(input[1], scene), \
				to_float(input[2], scene));
	free(input);
	return (position);
}

/**
 * @brief Set the rgb object based on string input
 * 
 * @param param (char **) comma seperated string input ("r,g,b")
 * @param rgb (int[3]) pointer to store the result
 * @param scene (t_scene) passed to clean up when input is invallid
 */
void	set_rgb(char *param, uint32_t *rgb, t_scene *scene)
{
	char		**input;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	int		i;

	i = 0;
	input = ft_split(param, ',');
	if (!input)
		exit_error(ERROR_MEM, NULL, scene);
	while (input[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RGB, NULL, scene);
	r = ft_atou_base(input[0], "0123456789", "");
	g = ft_atou_base(input[1], "0123456789", "");
	b = ft_atou_base(input[2], "0123456789", "");
	// printf("rbg set to:%u, %u, %u\n", r, g, b); // testing
	if ((!r && ft_strcmp(input[0], "0")) \
			|| (!g && ft_strcmp(input[1], "0")) \
			|| (!b && ft_strcmp(input[2], "0")))
		exit_error(ERROR_RGB, NULL, scene);
	if (r > 255 || g > 255 || b > 255)
		exit_error(ERROR_RGB, NULL, scene);
	*rgb = (r << 24 | g << 16 | b << 8 | 255);
	free(input);
}

/**
 * @brief Returs a float based on string input
 * 
 * @param param (char **) string input ("0.0")
 * @param scene 	(t_scene) passed to clean up when input is invallid
 * @return float 
 */
float	to_float(char *param, t_scene *scene)
{
	int		j;
	int		i;
	double	d;
	int		neg;

	j = 0;
	i = 0;
	neg = 1;
	if (param[j] == '-' && param[j++])
		neg = -1;
	while (ft_isdigit(param[j]))
		i = (i * 10) + (param[j++] - '0');
	if (param[j] == '.')
		j++;
	else if (param[j])
		exit_error(ERROR_F, NULL, scene);
	d = 0.0;
	while (param[j] && ft_isdigit(param[j]))
		d = (d * 10) + (param[j++] - '0');
	while (d >= 1)
		d /= 10;
	d += i;
	// printf("set to float:%f\n", d * neg); // testing
	return ((float)(d * neg));
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
	static char	*type[6] = {"A", "C", "L", "sp", "pl", "cy"};
	static t_f	*parse[6] = {init_ambient, init_camera, init_light, \
							init_sphere, init_plane, init_cylinder};

	i = 0;
	param = ft_split(line, '\t');
	if (!param)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < 6)
	{
		if (!ft_strcmp(type[i], param[0]))
		{
			parse[i](param, scene);
			ft_putstr_fd(line, 1);
			break ;
		}
		i++;
	}
	if (i == 6)
		exit_error(ERROR_SCENE, line, scene);
	free(param);
}
