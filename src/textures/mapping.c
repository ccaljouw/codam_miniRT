/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapping.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:18:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/29 16:59:03 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	checkerd(t_px px, t_object object)
{
	t_xyz		p;
	int			color;

	p = v_add(px.hitpoint, v_multiply(px.surface_normal, SHADOW_BIAS));
	p.x = fabs(floor(p.x));
	p.y = fabs(floor(p.y));
	p.z = fabs(floor(p.z));
	p.x = (int)p.x % 2;
	p.y = (int)p.y % 2;
	p.z	= (int)p.z % 2;
	color = (object.rgb[0] << 24 | object.rgb[1] << 16 | object.rgb[2] << 8 | 255);
	if (((int)p.x ^ (int)p.y) ^ (int)p.z)
		color = invert_color(color);
	return (color);
}

int	get_texture(t_px px, t_object object, t_scene *scene)
{
	static t_get_color	*get_color[3] = {get_color_sphere, get_color_plane, \
		get_color_cylinder};
	
	if (object.text == 0)
		px.color = ((object.rgb[0] << 24) | (object.rgb[1] << 16) | (object.rgb[2] << 8) | 255);
	else if (object.text == NR_TEXTURES + 1)
		px.color = checkerd(px, object);
	else
		px.color = get_color[object.id](object, px, scene->textures[object.text - 1]);
	return (px.color);
}
