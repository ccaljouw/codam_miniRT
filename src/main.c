/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/17 07:20:29 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <fcntl.h>

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
	if (argc != 2)
		exit_error(ERROR_ARGS, NULL, NULL);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH, NULL, NULL);
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
	char	*line;
	int		fd;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL, NULL);
	ft_memset(scene, 0, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line) // close fd if error in line
		{
			if (line[ft_strlen(line) - 1] == '\n')
				line[ft_strlen(line) - 1] = '\0';
			parse_type(line, scene);
		}
		else // what if error in gnl?
			break ;
	}
	close(fd);
	if (!scene->ambient || !scene->camera)
		exit_error(ERROR_SCENE, "not all required elements provided", scene);
	ft_putendl_fd("\033[32;1m\nScene set up\n\033[0m", 2);
	return (scene);
}
 
void	resize(void	*param)
{
	t_scene *scene;

	scene = (t_scene *)param;
	if (scene->mlx->width != (int32_t)scene->image->width || scene->mlx->height != (int32_t)scene->image->height)
	{
		mlx_resize_image(scene->image, scene->mlx->width, scene->mlx->height);
		render(scene);
	}
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	check_args(argc, argv);
	scene = init_scene(argv[1]);
	scene->mlx = mlx_init(WIDTH, HEIGHT, "RAY'S TRACERS", true);
	if (!scene->mlx)
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	render(scene);
	if (!scene->image)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == -1)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	mlx_loop_hook(scene->mlx, resize, scene);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);

	// cleanup scene
	return (0);
}
