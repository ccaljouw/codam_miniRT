/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:13:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 23:10:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief More key hooks:
 * 	L:			select light (in loop)
 * 	-/+:		adjust ambient brightness
 * 	P:			print scene info to file
 * 	BACKSPACE:	delete selected object/light
 * 	1-4:		add new SP/PL/CY/CO
 * 	5:			add new light
 * 
 * @param k 
 * @param scene 
 */
void	key_input2(mlx_key_data_t k, t_scene *scene)
{
	if (k.key == MLX_KEY_L)
		select_light(scene);
	if (k.key == MLX_KEY_MINUS || k.key == MLX_KEY_EQUAL)
		adjust_ambient(scene, k);
	if (k.key == MLX_KEY_S && k.modifier == MLX_SUPERKEY)
		save_scene(scene);
	if (k.key == MLX_KEY_BACKSPACE)
		delete_object(scene);
	if (k.key >= MLX_KEY_1 && k.key <= MLX_KEY_5)
		add_object(scene, k.key - 49);
	if (k.key == MLX_KEY_6)
		add_light(scene);
	if (k.key == MLX_KEY_R)
		adjust_reflections(scene, k);
	if (k.key == MLX_KEY_T)
		adjust_transparancy(scene, k);
	if (k.key == MLX_KEY_Y)
		change_texture(scene, k);
	if (k.key == MLX_KEY_P)
		change_aa(scene);
	if (k.key == MLX_KEY_B)
		change_bump(scene, k);
}

/**
 * @brief Key hooks:
 * 	ESCAPE:		close the program
 * 	I/O:		zoom camera / adjust diameter
 *	SHIFT+I/O:	adjust height
 *	ARROW L/R:	rotate over Y axis
 *	ARROR U/D:	rotate over X axis
 *	< / >:		rotate over Z axis
 *	W / S:		move over x axis
 * 	A / D:		move over y axis
 *  Q / E:		move over z axis
 * 
 * @param k 
 * @param param 
 */
void	key_input(mlx_key_data_t k, void *param)
{
	t_scene		*scene;

	scene = (t_scene *)param;
	if (k.action == MLX_RELEASE)
	{
		if (k.key == MLX_KEY_ESCAPE)
			exit_error(SUCCESS, NULL, scene);
		if (!BONUS)
			return ;
		if (k.key == ZOOM_IN || k.key == ZOOM_OUT)
			scale(k, scene);
		if (k.key == ROT_X_N || k.key == ROT_X_P \
			|| k.key == ROT_Y_N || k.key == ROT_Y_P \
			|| k.key == ROT_Z_N || k.key == ROT_Z_P)
			rotate(k, scene);
		if ((k.key == MOVE_UP || k.key == MOVE_DOWN \
			|| k.key == MOVE_LEFT || k.key == MOVE_RIGHT \
			|| k.key == MOVE_FRONT || k.key == MOVE_BACK)
			&& k.modifier != MLX_SUPERKEY)
			move(k, scene);
		key_input2(k, scene);
	}
}
