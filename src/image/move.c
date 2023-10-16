/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:18:29 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 23:07:01 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	adjust_position(t_xyz *pos, mlx_key_data_t keydata)
{
	float	coarse;	

	coarse = 1;
	if (keydata.modifier == MLX_SHIFT)
		coarse = 10;
	if (keydata.key == MOVE_UP)
		pos->y += .5 / coarse;
	if (keydata.key == MOVE_DOWN)
		pos->y -= .5 / coarse;
	if (keydata.key == MOVE_LEFT)
		pos->x -= .5 / coarse;
	if (keydata.key == MOVE_RIGHT)
		pos->x += .5 / coarse;
	if (keydata.key == MOVE_FRONT)
		pos->z += .5 / coarse;
	if (keydata.key == MOVE_BACK)
		pos->z -= .5 / coarse;
}

void	translate_triangle(t_scene *s, mlx_key_data_t k)
{
	t_xyz	pos;
	int		i;

	pos = v_create(0, 0, 0);
	adjust_position(&pos, k);
	i = -1;
	while (++i < 3)
		s->selected->p[i] = v_add(s->selected->p[i], pos);
}

void	move(mlx_key_data_t keydata, t_scene *scene)
{
	t_xyz	*pos;

	if (scene->selected && scene->selected->id == TR)
		translate_triangle(scene, keydata);
	else
	{
		if (scene->selected && scene->selected->id != TR)
			pos = &scene->selected->p_origin;
		else if (scene->selected_light)
			pos = &((t_light *)scene->selected_light->content)->origin;
		else
			pos = &scene->camera->view_point;
		adjust_position(pos, keydata);
		ft_printf("new position: ");
		print_vector(*pos);
	}
	camera_geo(scene);
	render_image(scene);
}
