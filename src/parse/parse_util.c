/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:34:13 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/13 16:35:41 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (param[j] && param[j] == '.')
		j++;
	else if (param[j])
		exit_error(ERROR_F, NULL, scene);
	d = 0.0;
	while (param[j] && ft_isdigit(param[j]))
		d = (d * 10) + (param[j++] - '0');
	while (d >= 1)
		d /= 10;
	d += i;
	return ((float)(d * neg));
}

/**
 * @brief Set the rgb object based on string input
 * 
 * @param param (char **) comma seperated string input ("r,g,b")
 * @param rgb (int[3]) pointer to store the result
 * @param scene (t_scene) passed to clean up when input is invallid
 */
void	set_rgb(char *param, int *rgb, t_scene *scene)
{
	char		**input;
	int			i;

	i = 0;
	input = ft_split(param, ',');
	if (!input)
		exit_error(ERROR_MEM, NULL, scene);
	while (input[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RGB, NULL, scene);
	rgb[0] = ft_atou_base(input[0], "0123456789", "");
	rgb[1] = ft_atou_base(input[1], "0123456789", "");
	rgb[2] = ft_atou_base(input[2], "0123456789", "");
	if ((!rgb[0] && ft_strcmp(input[0], "0")) \
			|| (!rgb[1] && ft_strcmp(input[1], "0")) \
			|| (!rgb[2] && ft_strcmp(input[2], "0")))
		exit_error(ERROR_RGB, NULL, scene);
	if (rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
		exit_error(ERROR_RGB, NULL, scene);
	ft_clean_split_arr(&input);
}

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
	ft_clean_split_arr(&input);
	return (position);
}

void	print_param_line(char **param)
{
	int	i;

	i = 0;
	while (param[i])
	{
		ft_printf("%s", param[i]);
		if (param[i + 1])
			ft_printf("\t");
		i++;
	}
	ft_printf("\n");
}
