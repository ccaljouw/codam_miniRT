/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_adjustments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:56:54 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 22:59:54 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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

void	change_texture(t_scene *s, mlx_key_data_t k)
{
	int	current_text;

	if (!s->selected || (k.modifier && k.modifier != MLX_SHIFT))
		return ;
	if (!k.modifier)
	{
		current_text = get_texture_id(s, s->selected->text);
		if (current_text == NR_TEXTURES)
		{
			s->selected->text = NULL;
			current_text = -1;
		}
		else
			s->selected->text = s->textures[current_text];
		ft_printf("new texture %i\n", current_text + 1);
	}
	else
	{
		(s->selected->text_proc)++;
		if (s->selected->text_proc > TEXT_PROCEDURES)
			s->selected->text_proc = 0;
		ft_printf("text proc: %i\n", s->selected->text_proc);
	}
	render_image(s);
}

void	change_aa(t_scene *s)
{
	if (s->aa == 1)
		s->aa = 2;
	else
		s->aa += 2;
	if (s->aa > MAX_AA * 2)
		s->aa = 1;
	ft_printf("anti alias level: %i\n", (int)(floor(s->aa / 2)));
	s->n_height = s->file_height;
	s->n_width = s->file_width;
	s->must_resize = true;
	do_resize(s);
}

void	change_bump(t_scene *scene, mlx_key_data_t k)
{
	int			current_bump;

	if (!scene->selected || (k.modifier && k.modifier != MLX_SHIFT))
		return ;
	if (!k.modifier)
	{
		current_bump = get_texture_id(scene, scene->selected->bump);
		if (current_bump == NR_TEXTURES)
		{
			scene->selected->bump = NULL;
			current_bump = -1;
		}
		else
			scene->selected->bump = scene->textures[current_bump];
		ft_printf("new bumpmap %i\n", current_bump + 1);
	}
	else if (k.modifier == MLX_SHIFT)
	{
		(scene->selected->bump_proc)++;
		if (scene->selected->bump_proc > BUMP_PROCEDURES)
			scene->selected->bump_proc = 0;
		ft_printf("new bump proc %i\n", scene->selected->bump_proc);
	}
	render_image(scene);
}
