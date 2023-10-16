/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/16 22:04:51 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	adjust_diameter_height(mlx_key_data_t keydata, t_object *obj)
{
	if (keydata.key == ZOOM_IN)
	{
		if (keydata.modifier == MLX_SHIFT)
			obj->height += .2;
		else
			obj->diameter += .2;
	}
	if (keydata.key == ZOOM_OUT)
	{
		if (keydata.modifier == MLX_SHIFT)
			obj->height -= .2;
		else
			obj->diameter -= .2;
	}
}

void	scale_triangle(t_object *tr, mlx_key_data_t k)
{
	t_m44	scale;
	t_m44	trm;
	t_m44	tr_i;
	int		i;

	trm = m44_init();
	m44_translate_by_vector(&trm, v_subtract(v_create(0, 0, 0), tr->p[0]));
	m44_invert(trm, &tr_i);
	scale = m44_init();
	if (k.key == ZOOM_IN)
		m44_scale(&scale, 1.1, 1.1, 1.1);
	if (k.key == ZOOM_OUT)
		m44_scale(&scale, 0.9, 0.9, 1.1);
	i = -1;
	while (++i < 3)
	{
		m44_multiply_vec3(trm, tr->p[i], &tr->p[i]);
		m44_multiply_vec3(scale, tr->p[i], &tr->p[i]);
		m44_multiply_vec3(tr_i, tr->p[i], &tr->p[i]);
	}
}

void	scale(mlx_key_data_t keydata, t_scene *s)
{
	if (s->selected && s->selected->id != TR)
		adjust_diameter_height(keydata, s->selected);
	else if (s->selected && s->selected->id == TR)
		scale_triangle(s->selected, keydata);
	else if (s->selected_light)
		adjust_light_brightness(keydata, (t_light *)s->selected_light->content);
	else
	{
		if (keydata.key == ZOOM_IN)
			s->camera->fov -= 5;
		if (keydata.key == ZOOM_OUT)
			s->camera->fov += 5;
		if (s->camera->fov < 0)
			s->camera->fov = 0;
		if (s->camera->fov > 180)
			s->camera->fov = 180;
		ft_printf("new fov: %i\n", s->camera->fov);
		camera_geo(s);
	}
	render_image(s);
}
