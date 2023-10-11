/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:13:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 00:24:51 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	key_input2(mlx_key_data_t k, t_scene *scene)
{
	if (k.key == MLX_KEY_L)
		select_light(scene);
	if (k.key == MLX_KEY_MINUS || k.key == MLX_KEY_EQUAL)
		adjust_ambient(scene, k);
	if (k.key == MLX_KEY_P)
		save_scene(scene);
	if (k.key == MLX_KEY_BACKSPACE)
		delete_object(scene);
	if (k.key >= MLX_KEY_1 && k.key <= MLX_KEY_4)
		add_object(scene, k.key - 49);
	if (k.key == MLX_KEY_5)
		add_light(scene);
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
		if (k.key == ROT_X_N || k.key == ROT_X_P \
			|| k.key == ROT_Y_N || k.key == ROT_Y_P \
			|| k.key == ROT_Z_N || k.key == ROT_Z_P)
			rotate(k, scene);
		if (k.key == MOVE_UP || k.key == MOVE_DOWN \
			|| k.key == MOVE_LEFT || k.key == MOVE_RIGHT \
			|| k.key == MOVE_FRONT || k.key == MOVE_BACK)
			move(k, scene);
		key_input2(k, scene);
	}
}
