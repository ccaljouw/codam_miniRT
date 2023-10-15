/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:13:35 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/15 23:57:05 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	adjust_reflections(t_scene *s, mlx_key_data_t k)
{
	if (k.key == MLX_KEY_R)
	{
		if (!k.modifier)
		{
			(s->max_reflect)++;
			if (s->max_reflect > MAX_REFLECT)
				s->max_reflect = 0;
			ft_printf("# of reflections: %i\n", s->max_reflect);
			render_image(s);
		}
		else if (k.modifier == MLX_SHIFT && s->selected)
		{
			if ((((t_object *)s->selected)->refl) == 1)
				(((t_object *)s->selected)->refl) = 0;
			else
			{
				(((t_object *)s->selected)->refl) += .1;
				if ((((t_object *)s->selected)->refl) > 1)
					(((t_object *)s->selected)->refl) = 1;
			}
			ft_printf("new refl: %f\n", (((t_object *)s->selected)->refl));
			render_image(s);
		}

	}
}

void	adjust_transparancy(t_scene *s, mlx_key_data_t k)
{

	if (s->selected)
	{
		if (!k.modifier)
			((t_object *)s->selected)->transp += .1;
		if (k.modifier == MLX_SHIFT)
			((t_object *)s->selected)->transp -= .1;
		if (((t_object *)s->selected)->transp > 1)
			((t_object *)s->selected)->transp = 1;
		if (((t_object *)s->selected)->transp < 0)
			((t_object *)s->selected)->transp = 0;
		ft_printf("new trans %f\n", ((t_object *)s->selected)->transp);
	}
	else
		return ;
	render_image(s);
}

void	change_texture(t_scene *s)
{
	t_object	*obj;
	int			current_text;

	if (s->selected)
	{
		obj = s->selected;
		current_text = get_texture_id(s, obj->text);
		if (current_text >= NR_TEXTURES)
			current_text = 0;
		obj->text = s->textures[current_text];
		ft_printf("new texture %i\n", current_text);
		render_image(s);
	}
}

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
	if (k.key == MLX_KEY_P)
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
		change_texture(scene);
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
