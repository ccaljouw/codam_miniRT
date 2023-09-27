/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/27 00:32:34 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

void	zoom(mlx_key_data_t keydata, t_scene *scene)
{
	if (scene->selected)
	{
		if (scene->selected->id == PL)
			return;
		if (keydata.key == ZOOM_IN)
			scene->selected->diameter++;
		if (keydata.key == ZOOM_OUT)
			scene->selected->diameter--;
		ft_printf("new diameter:%f\n", scene->selected->diameter); //for debugging
	}
	else
	{
		if (keydata.key == ZOOM_IN)
			scene->camera->fov -= 5;
		if (keydata.key == ZOOM_OUT)
			scene->camera->fov += 5;
		cameraGeometry(scene);
		printf("new fov:%d\n", scene->camera->fov); //for debugging
	}
	render_image(scene);
}

void	rotate(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*orientation;
	
	if (scene->selected)
	{
		orientation = &scene->selected->vNormal;
		printf("object orientation: ");
		print_vector(*orientation);
	}
	else
	{
		orientation = &scene->camera->orientation_v;
		printf("camera orientation: ");
		print_vector(*orientation);
	}
	if (keydata.key == MOVE_X_N)
		orientation->x -= 0.2;
	if (keydata.key == MOVE_X_P)
		orientation->x += 0.2;
	if (keydata.key == MOVE_Y_N)
		orientation->y -= 0.2;
	if (keydata.key == MOVE_Y_P)
		orientation->y += 0.2;
	if (keydata.key == MOVE_Z_N)
		orientation->z -= 0.2;
	if (keydata.key == MOVE_Z_P)
		orientation->z += 0.2;
	if (!scene->selected)	
		cameraGeometry(scene);
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
	if (mlx_is_mouse_down(scene->mlx, MLX_MOUSE_BUTTON_LEFT))
		return;
	if (scene->mlx->width != scene->p_width || scene->mlx->height != scene->p_height)
	{
		ft_printf("reszing\n");
		mlx_resize_image(scene->image, scene->mlx->width, scene->mlx->height);
		if (scene->pixels)
		{
			while (i < scene->p_height)
			{
				free(scene->pixels[i]);
				i++;
			}
			free(scene->pixels);
		}
		ft_printf("here\n");
		ft_printf("old height %i, new height %i\n", scene->p_height, scene->mlx->height);
		scene->p_width = scene->mlx->width;
		scene->p_height = scene->mlx->height;
		init_pixels(scene);
		scene->image = mlx_new_image(scene->mlx, scene->p_width, scene->p_height);
		ft_printf("there\n");
		cameraGeometry(scene);
		ft_printf("everywhere\n");
		render_image(scene);
		ft_printf("something\n");
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
		if (k.key == ZOOM_IN || k.key == ZOOM_OUT)
			zoom(k, scene);
		if (k.key == MOVE_X_N || k.key == MOVE_X_P \
			|| k.key == MOVE_Y_N || k.key == MOVE_Y_P \
			|| k.key == MOVE_Z_N || k.key == MOVE_Z_P)
			rotate(k, scene);
		else
			return ;
	}
}

