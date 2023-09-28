/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_manipulation.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/28 22:03:23 by cariencaljo   ########   odam.nl         */
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
		orientation = &scene->selected->vNormal;
	else
		orientation = &scene->camera->orientation_v;
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
	printf("orientation: ");
	print_vector(*orientation);
	cameraGeometry(scene);
	render_image(scene);
}

void	set_resize_flag(int width, int height, void	*param)
{
	t_scene	*scene;

	scene = (t_scene *)param;
	scene->must_resize = 1;
	mlx_resize_image(scene->image, width, height);
	scene->n_width = width;
	scene->n_height = height;
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

