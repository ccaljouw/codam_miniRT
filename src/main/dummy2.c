/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dummy2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 09:21:21 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 14:25:35 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_pixel_data_reflection(t_px *px, t_scene *scene)
{
	(void)px;
	(void)scene;
	return (1);
}

int	blend_color(int c1, int c2, float fact_c1)
{
	(void)c1;
	(void)c2;
	(void)fact_c1;
	return (255);
}

void	light_transport(t_px *px, t_scene *scene)
{
	(void)px;
	(void)scene;
}

int	get_texture_id(t_scene *s, mlx_texture_t *text)
{
	(void)s;
	(void)text;
	return (0);
}
