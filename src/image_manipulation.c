/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_manipulation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/23 09:33:04 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	zoom(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->search)
	{
		if (keydata.key == MLX_KEY_I)
			scene->search->diameter++;
		if (keydata.key == MLX_KEY_O)
			scene->search->diameter--;
	}
	else
	{
		if (keydata.key == MLX_KEY_I)
			scene->camera->fov -= 5;
		if (keydata.key == MLX_KEY_O)
			scene->camera->fov += 5;
		cameraGeometry(scene->camera);
	}
	renderImage(scene);
}

void	turn(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->search && scene->search->id == CY)
	{
		if (keydata.key == MLX_KEY_LEFT)
			scene->search->vAxis.x += 0.1;
		if (keydata.key == MLX_KEY_RIGHT)
			scene->search->vAxis.x -= 0.1;
		if (keydata.key == MLX_KEY_UP)
			scene->search->vAxis.y -= 0.1;
		if (keydata.key == MLX_KEY_DOWN)
			scene->search->vAxis.y += 0.1;
	}
	if (scene->search && scene->search->id == PL)
	{
		if (keydata.key == MLX_KEY_LEFT)
			scene->search->vNormal.x += 0.1;
		if (keydata.key == MLX_KEY_RIGHT)
			scene->search->vNormal.x -= 0.1;
		if (keydata.key == MLX_KEY_UP)
		{
			scene->search->vNormal.z -= 0.1;
			scene->search->vNormal.y -= 0.1;
		}
		if (keydata.key == MLX_KEY_DOWN)
		{
			scene->search->vNormal.z += 0.1;
			scene->search->vNormal.y += 0.1;
		}
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
	}
	cameraGeometry(scene->camera);
	renderImage(scene);
}
