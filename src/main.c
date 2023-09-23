/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/23 08:43:21 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <fcntl.h>
#include "../includes/test.h"

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
	if (argc < 2)
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
			if (line[0] == '\n')
			{
				free(line);
				continue ;
			}
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

void	image_to_window(t_scene *scene)
{
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
}

/**
 * @brief checks window size against image size and resizes image when window size has changed
 * 
 * @param param (t_scene *) scene
 */
void	resize(void	*param)
{
	t_scene 	*scene;
	mlx_image_t *temp;

	scene = (t_scene *)param;
	if ((uint32_t)scene->mlx->width != scene->image->width || (uint32_t)scene->mlx->height != scene->image->height)
	{
		mlx_resize_image(scene->image, scene->mlx->width, scene->mlx->height);
		temp =  scene->image;
		scene->image = mlx_new_image(scene->mlx, scene->mlx->width, scene->mlx->height);
		renderImage(scene);
		image_to_window(scene);
		mlx_delete_image(scene->mlx, temp);
	}
}

void	select_object(mouse_key_t b, action_t a, modifier_key_t mod, void *param)
{
	t_scene 	*scene;
	int			x;
	int			y;

	x = 0;
	y = 0;
	scene = (t_scene *)param;
	(void)mod;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		if (scene->search == scene->pixels[y][x].hitobject)
		{
			scene->search = NULL;
			renderImage(scene);
			return;
		}
		else
			scene->search = scene->pixels[y][x].hitobject;
		y = 0;
		while (y < scene->p_height)
		{
			x = 0;
			while (x < scene->p_width)
			{
				if (scene->pixels[y][x].hitobject == scene->search)
					mlx_put_pixel(scene->image, x, y, (100 << 24 | 100 << 16 | 100 << 8 | 100));
				x++;
			}
			y++;
		}
	}
}

void	key_input(mlx_key_data_t keydata, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	// zoom
	if (keydata.key == MLX_KEY_I && keydata.action == MLX_RELEASE && scene->search)
		scene->search->diameter++;
	else if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE && scene->search)
		scene->search->diameter--;
	else if (keydata.key == MLX_KEY_I && keydata.action == MLX_RELEASE)
		scene->camera->fov -= 5;
	else if (keydata.key == MLX_KEY_O && keydata.action == MLX_RELEASE)
		scene->camera->fov += 5;
	// turn
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_RELEASE)
		scene->camera->orientation_v.y -= 0.1;
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_RELEASE)
		scene->camera->orientation_v.y += 0.1;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		scene->camera->orientation_v.x += 0.1;
	else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		scene->camera->orientation_v.x -= 0.1;
	else if (keydata.action == MLX_RELEASE)
		return;
	renderImage(scene);
}

int	main(int argc, char **argv)
{
	t_scene	*scene;

	check_args(argc, argv);
	scene = init_scene(argv[1]);
	if (argv[2] && (!ft_strcmp(argv[2], "-a") || !ft_strcmp(argv[2], "-ai")))
		renderAscii(scene);
	if (argc == 2 || !ft_strcmp(argv[2], "-ai"))
	{
		scene->mlx = mlx_init(IM_WIDTH, IM_HEIGHT, "RAY'S TRACERS", true);
		if (!scene->mlx)
			exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
		scene->image = mlx_new_image(scene->mlx, IM_WIDTH, IM_HEIGHT);
		image_to_window(scene);
		renderImage(scene);
		// mlx_loop_hook(scene->mlx, resize, scene);
		mlx_key_hook(scene->mlx, key_input, scene);
		mlx_mouse_hook(scene->mlx, select_object, scene);
		mlx_loop(scene->mlx);
		mlx_delete_image(scene->mlx, scene->image);
		mlx_terminate(scene->mlx);
	}
	// cleanup scene
	return (0);
}
