/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:11:39 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/18 09:50:53 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief Free all malloc'ed values if they are not NULL
 * 
 * @param scene 
 */
void	clean_scene(t_scene *scene)
{
	int	y;

	y = 0;
	if (scene->image)
		mlx_delete_image(scene->mlx, scene->image);
	if (scene->mlx)
		mlx_terminate(scene->mlx);
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	ft_lstclear(&scene->lights, free);
	ft_lstclear(&scene->objects, free);
	if (scene->pixels)
	{
		while (y < scene->p_height)
		{
			free(scene->pixels[y]);
			scene->pixels[y] = NULL;
			y++;
		}
	}
	free(scene->pixels);
}

void	leaks_f(void)
{
	system("leaks -q miniRT");
}

int	main(int argc, char **argv)
{
	t_scene			*s;

	check_args(argc, argv);
	s = init_scene(argv[1]);
	if (argv[2] && (!ft_strcmp(argv[2], "-a")))
		render_ascii(s);
	if (argc == 2)
	{
		s->mlx = mlx_init(s->file_width, s->file_height, "RAY'S TRACERS", true);
		if (!s->mlx)
			exit_error((char *)mlx_strerror(mlx_errno), NULL, s);
		s->image = mlx_new_image(s->mlx, s->file_width, s->file_height);
		s->render_image = mlx_new_image(s->mlx, s->file_width, s->file_height);
		image_to_window(s, s->render_image);
		render_image(s);
		image_to_window(s, s->image);
		mlx_key_hook(s->mlx, key_input, s);
		mlx_mouse_hook(s->mlx, select_object, s);
		mlx_resize_hook(s->mlx, set_resize_flag, s);
		mlx_loop_hook(s->mlx, do_resize, s);
		mlx_loop(s->mlx);
	}
	return (0);
}
