/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 18:29:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/30 19:28:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <fcntl.h>

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
			|| (!rgb[1]  && ft_strcmp(input[1], "0")) \
			|| (!rgb[2] && ft_strcmp(input[2], "0")))
		exit_error(ERROR_RGB, NULL, scene);
	if (rgb[0] > 255 || rgb[1]  > 255 || rgb[2] > 255)
		exit_error(ERROR_RGB, NULL, scene);
	ft_clean_split_arr(&input);
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
	static char	*type[9] = {"A", "C", "l", "sp", "pl", "cy", "R", "co"};
	static t_f	*parse[9] = {init_ambient, init_camera, init_lights, \
							init_sphere, init_plane, init_cylinder, \
							init_resolution, init_cone};

	i = 0;
	replace(line, ' ', '\t');
	param = ft_split(line, '\t');
	if (!param)
		exit_error(ERROR_MEM, NULL, scene);
	while (param[0] && i < 8)
	{
		if (!ft_strcmp(type[i], param[0]))
		{
			parse[i](param, scene);
			ft_putendl_fd(line, 1);
			break ;
		}
		i++;
	}
	if (i == 8)
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
