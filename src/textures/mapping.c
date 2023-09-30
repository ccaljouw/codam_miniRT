/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapping.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/30 16:24:01 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	checkered(t_px px, float x, float y, float z)
{
	int			color;

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 2;
	y = (int)y % 2;
	z	= (int)z % 2;
	color = (px.hitobject->rgb[0] << 24 | px.hitobject->rgb[1] << 16 | px.hitobject->rgb[2] << 8 | 255);
	if (((int)x ^ (int)y) ^ (int)z)
		color = invert_color(color);
	return (color);
}

int	get_texture(t_px px, t_object object, t_scene *scene)
{
	static t_get_color	*get_color[3] = {get_color_sphere, get_color_plane, \
		get_color_cylinder};
	
	if (object.text == 0)
		px.color = ((object.rgb[0] << 24) | (object.rgb[1] << 16) | (object.rgb[2] << 8) | 255);
	// else if (object.text == NR_TEXTURES + 1)
	// 	px.color = checkerd(px, object);
	else
		px.color = get_color[object.id](object, px, scene->textures[object.text - 1]);
	return (px.color);
}
