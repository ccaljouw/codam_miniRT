/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 14:21:20 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/26 16:22:39 by ccaljouw         ###   ########.fr       */
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
	t_px	*px;

	block = (t_block *)params;
	scene = block->scene;
	y = block->y;
	while (y < block->y_max)
	{
		x = 0;
		while (x < scene->p_width)
		{
			px = scene->pixels[y] + x;
			get_ray(scene->pixels[y] + x, x, y, scene);
			trace_ray(scene->pixels[y] + x, scene);
			get_surface_data(scene->pixels[y] + x);
			loop_lights(*scene, px);
			x++;
		}
		y++;
	}
	draw_image(scene);
	return (NULL);
}

t_block	set_block(t_scene *scene, int y, int blocksize)
{
	t_block	block;
	
	block.scene = scene;
	block.y =  y;
	block.y_max = y + blocksize;
	return (block);
}

pthread_t	*create_threads(t_scene *scene, pthread_t *threads)
{
	t_block		*blocks;
	int			blocksize;
	int			y;
	int 		i;

	blocks = malloc(THREADS * sizeof(t_block));
	if (!blocks)
		exit_error(ERROR_MEM, NULL, scene);
	i = 0;
	y = 0;
	blocksize = scene->p_height / THREADS;
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
