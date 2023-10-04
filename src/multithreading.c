/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multithreading.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 14:21:20 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/04 14:12:16 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>
#include <pthread.h>  //check with Nicolas it is ok to use this

void	*routine(void *params)
{
	int		x;
	int		y;
	t_scene	*scene;
	t_block	*block;

	block = (t_block *)params;
	scene = block->scene;
	y = block->y;
	while (y < block->y_max)
	{
		x = 0;
		while (x < scene->p_width)
		{
			get_ray(scene->pixels[y] + x, x, y, scene);
			trace_ray(scene->pixels[y] + x, scene);
			if ((scene->pixels[y] + x)->hitobject != NULL)
			{
				get_surface_data(scene->pixels[y] + x);
				map_normal(scene->pixels[y] + x);
				loop_lights(scene, scene->pixels[y] + x);
			}
			x++;
		}
		y++;
	}
	return (NULL);
}

t_block	set_block(t_scene *scene, int y, int blocksize)
{
	t_block	block;

	block.scene = scene;
	block.y = y;
	block.y_max = y + blocksize;
	return (block);
}

pthread_t	*create_threads(t_scene *scene, pthread_t *threads, t_block *blocks)
{
	int			blocksize;
	int			y;
	int			i;

	i = 0;
	y = 0;
	blocksize = scene->p_height / THREADS;
	while (i < THREADS)
	{
		blocks[i] = set_block(scene, y, blocksize);
		y = y + blocksize;
		if (pthread_create(threads + i, NULL, &routine, &blocks[i]))
				exit_error(ERROR_THREAD, "failed to create thread\n", scene);
		i++;
	}
	return (threads);
}

void	join_threads(pthread_t *threads, t_scene *scene)
{
	int		i;

	i = 0;
	while (i < THREADS)
	{
		if (pthread_join(threads[i], NULL))
			exit_error(ERROR_THREAD, "failed to join thread\n", scene);
		i++;
	}
	draw_image(scene);
	// ft_printf("minx:%f, maxx:%f, miny:%f, maxy:%f\n", scene->min_x, scene->max_x, scene->min_y, scene->max_y);
}
