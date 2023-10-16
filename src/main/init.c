/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:05:54 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 23:33:58 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief checks that there are 2 arguments provided 
 * and that argv[1] has an .rt extension
 * @param argc 
 * @param argv 
 */
void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc < 2 || argc > 3)
		exit_error(ERROR_ARGS, USAGE_MSG, NULL);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH, USAGE_MSG, NULL);
	if (argc == 3 && !(!ft_strcmp(argv[2], "-a")))
		exit_error(ERROR_FLAG, USAGE_MSG, NULL);
}

/**
 * @brief Init the pixel array
 * 
 * @param scene 
 */
void	init_pixels(t_scene *scene)
{
	int	i;

	i = 0;
	scene->pixels = ft_calloc(scene->p_height, sizeof(t_px *));
	if (!scene->pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < scene->p_height)
	{
		scene->pixels[i] = ft_calloc(scene->p_width, sizeof(t_px));
		if (!scene->pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
}

/**
 * @brief Load the textures
 * 
 * @param scene 
 */
void	init_textures(t_scene *scene)
{
	int	i;

	i = 0;
	scene->textures = ft_calloc(NR_TEXTURES, sizeof(mlx_texture_t *));
	if (!scene->textures)
		exit_error(ERROR_MEM, NULL, scene);
	scene->textures[0] = mlx_load_png("png/text/checker.png");
	scene->textures[1] = mlx_load_png("png/text/world.png");
	scene->textures[2] = mlx_load_png("png/text/world2.png");
	scene->textures[3] = mlx_load_png("png/text/sterren.png");
	scene->textures[4] = mlx_load_png("png/bump/golf.png");
	scene->textures[5] = mlx_load_png("png/bump/bump1.png");
	scene->textures[6] = mlx_load_png("png/bump/bump2.png");
	scene->textures[7] = mlx_load_png("png/bump/bump3.png");
	scene->textures[8] = mlx_load_png("png/bump/bump4.png");
	scene->textures[9] = mlx_load_png("png/bump/bump5.png");
	scene->textures[10] = mlx_load_png("png/bump/bump6.png");
	scene->textures[11] = mlx_load_png("png/bump/bump7.png");
	scene->textures[12] = mlx_load_png("png/bump/bump8.png");
	scene->textures[13] = mlx_load_png("png/bump/bump9.png");
	while (i < NR_TEXTURES)
	{
		if (!scene->textures[i++])
			exit_error(ERROR_PNG, NULL, scene);
	}
}

/**
 * @brief initiates the scene based on the file contents
 * 
 * @param file (char **) input file with .rt extension
 * @return t_scene* 
 */
t_scene	*init_scene(char *file)
{
	t_scene	*scene;

	scene = ft_calloc(1, sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL, NULL);
	scene->p_width = IM_WIDTH;
	scene->p_height = IM_HEIGHT;
	scene->file_width = IM_WIDTH;
	scene->file_height = IM_HEIGHT;
	scene->aa = 1;
	scene->must_resize = false;
	scene->max_reflect = STD_REFLECT;
	init_textures(scene);
	parse_file(file, scene);
	if (!scene->ambient || !scene->camera)
		exit_error(ERROR_SCENE, "not all required elements provided", scene);
	ft_putendl_fd("\033[32;1m\nScene set up\n\033[0m", 2);
	init_pixels(scene);
	return (scene);
}
