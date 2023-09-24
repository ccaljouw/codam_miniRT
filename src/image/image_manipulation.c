/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_manipulation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/24 12:36:44 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	zoom(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->selected)
	{
		if (scene->selected->id == PL)
			return;
		if (keydata.key == MLX_KEY_I)
			scene->selected->diameter++;
		if (keydata.key == MLX_KEY_O)
			scene->selected->diameter--;
	}
	else
	{
		if (keydata.key == MLX_KEY_I)
			scene->camera->fov -= 5;
		if (keydata.key == MLX_KEY_O)
			scene->camera->fov += 5;
		cameraGeometry(scene);
	}
	render_image(scene);
}

void	rotate(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->selected)
	{
		if (keydata.key == MLX_KEY_LEFT)
			scene->selected->vNormal.x -= 0.2;
		if (keydata.key == MLX_KEY_RIGHT)
			scene->selected->vNormal.x += 0.2;
		if (keydata.key == MLX_KEY_UP)
			scene->selected->vNormal.y += 0.2;
		if (keydata.key == MLX_KEY_DOWN)
			scene->selected->vNormal.y -= 0.2;
	}
	else
	{
		if (keydata.key == MLX_KEY_UP)
			scene->camera->orientation_v.y -= 0.1;
		if (keydata.key == MLX_KEY_DOWN)
			scene->camera->orientation_v.y += 0.1;
		if (keydata.key == MLX_KEY_LEFT)
			scene->camera->orientation_v.x += 0.1;
		if (keydata.key == MLX_KEY_RIGHT)
			scene->camera->orientation_v.x -= 0.1;
		cameraGeometry(scene);
	}
	render_image(scene);
}

/**
 * @brief checks window size against image size and resizes image when window size has changed
 * 
 * @param param (t_scene *) scene
 */
void	resize(void	*param)
{
	t_scene 	*scene;
	int			i;

	i = 0;
	scene = (t_scene *)param;
	if (scene->mlx->width != scene->p_width || scene->mlx->height != scene->p_height)
	{
		if (scene->pixels)
		{
			while (i < scene->p_height)
			{
				free(scene->pixels[i]);
				i++;
			}
			free(scene->pixels);
		}
		scene->p_width = scene->mlx->width;
		scene->p_height = scene->mlx->height;
		init_pixels(scene);
		mlx_resize_image(scene->image, scene->mlx->width, scene->mlx->height);
		cameraGeometry(scene);
		render_image(scene);
	}
}

void	key_input(mlx_key_data_t k, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (k.action == MLX_RELEASE)
	{
		if (k.key == MLX_KEY_ESCAPE)
			exit_error(SUCCESS, NULL, scene);	
		if (k.key == MLX_KEY_I || k.key == MLX_KEY_O)
			zoom(k, scene);
		if (k.key == MLX_KEY_LEFT || k.key == MLX_KEY_RIGHT \
			|| k.key == MLX_KEY_UP || k.key == MLX_KEY_DOWN)
			rotate(k, scene);
		else
			return;
	}
}

void	set_image_size(t_scene *scene, int	width, int height)
{
	scene->p_width = width;
	scene->p_height = height;
}
