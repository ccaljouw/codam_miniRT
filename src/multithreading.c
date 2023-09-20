/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   multithreading.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/20 14:21:20 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/20 21:02:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <pthread.h>  //check with Nicolas it is ok to use this

void	*routine(void *params)
{
	int		x;
	int		y;
	t_scene	*scene;
	t_block	*block;
	t_px	*pixels;

	block = (t_block *)params;
	scene = &block->scene;
	y = block->y;
	pixels = ft_calloc(scene->image->width * (block->y_max - y), sizeof(t_px));
	if (!pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (y < block->y_max)
	{
		// x = scene->camera->image_height/2;
		// while (x == scene->camera->image_height/2)
		x = 0;
		while (x < scene->camera->image_height)
		{
			trace_ray(&pixels[x + y], scene, x, y);
			mlx_put_pixel(scene->image, x, y, getColor(pixels[x + y], scene));
			x++;
		}
		y++;
	}
	return (NULL);
}

t_block	set_block(t_scene *scene, int y, int blocksize)
{
	t_block	block;
	
	block.scene = *scene;
	block.y =  y;
	block.y_max = y + blocksize;
	return (block);
}

pthread_t	*create_threads(t_scene *scene)
{
	pthread_t	*threads;
	t_block		*blocks;
	int			blocksize;
	int			y;
	int 		i;

	threads = ft_calloc(THREADS, sizeof(pthread_t));
	blocks = ft_calloc(THREADS, sizeof(t_block));
	if (!threads || !blocks)
		exit_error(ERROR_MEM, NULL, scene);
	i = 0;
	y = 0;
	blocksize = scene->image->height / THREADS;
	while (i < THREADS)
	{
		blocks[i] = set_block(scene, y, blocksize);
		y = y + blocksize;
		if (pthread_create(threads + i, NULL, &routine, &blocks[i]))
		{
			while (i >= 0)
				if (pthread_join(threads[i], NULL))
			exit_error(ERROR_THREAD, "failed to create thread\n", scene);
		}
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
}
