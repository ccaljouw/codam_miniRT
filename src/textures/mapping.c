/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapping.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/27 23:14:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	checkerd(t_px px, t_object object)
{
	t_xyz		unit;
	t_xyz		p;

	unit = v_subtract(px.hitpoint, object.pOrigin);
	p.x = abs((int)floorf(unit.x)) % 2;
	p.y = abs((int)floorf(unit.y)) % 2;
	p.z = abs((int)floorf(unit.z)) % 2;
	if (p.x == p.y == p.z)
		px.color = (255 << 24 | 255 << 16 | 255 << 8 | 255);
	else
		px.color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	return (px.color);
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
