/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 13:32:53 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <fcntl.h>

#include <stdio.h> 														// for testing purposes only
uint32_t	get_gradient_value(uint32_t x, uint32_t y, t_scene *data)	// for testing purposes only
{
	uint32_t	r;
	uint32_t	g;

	r = (uint32_t)round(((double)x / (double)data->image->width) * 255);
	g = (uint32_t)round(((double)y / (double)data->image->height) * 255);
	return (r << 24 | g << 16 | 0 << 8 | 255);
}

void	ft_setpixels(void *param)
{
	t_scene		*data;
	uint32_t	x;
	uint32_t	y;

	x = 0;
	y = 0;
	data = (t_scene *)param;
	while (x <= data->image->width - 1)
	{
		while (y <= data->image->height - 1)
		{
			mlx_put_pixel(data->image, x, y, get_gradient_value(x, y, data));
			y++;
		}
		x++;
		y = 0;
	}
}

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
		if (line)
			parse_type(line, scene);
		else // what if error in gnl?
			break ;
	}
	close(fd);
	ft_putendl_fd("\033[32;1mScene set up\n\033[0m", 2);
	return (scene);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	check_args(argc, argv);
	scene = init_scene(argv[1]);
	scene->mlx = mlx_init(WIDTH, HEIGHT, "COLOR GRADIENT", true);
	if (!scene->mlx)
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
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
	mlx_loop_hook(scene->mlx, ft_setpixels, scene);
	mlx_loop(scene->mlx);
	mlx_terminate(scene->mlx);
	// cleanup scene
	return (0);
}
