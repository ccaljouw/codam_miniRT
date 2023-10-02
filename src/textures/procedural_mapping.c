/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   procedural_mapping.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/02 16:20:01 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/*
Procedural textures are calcultaed basd on x, y coordinates of the object space.

available procedures:
	1	checkered
	2	v_checkered
*/

int	checkered(t_px px, float x, float y, float z)
{

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 2;
	y = (int)y % 2;
	z = (int)z % 2;
	if (((int)x ^ (int)y) ^ (int)z)
		px.color = invert_color(px.color);
	return (px.color);
}

int	map_procedure(t_px px, float x, float y, float z)
{
	if (px.hitobject->text_proc == 1)
		return (checkered(px, x, y, z));
	return (px.color);	
}

void	map_texture(t_px *px)
{
	static t_get_color	*get_color[4] = {get_color_sphere, get_color_plane, \
		get_color_cylinder , get_color_cone};
	t_object	*object;

	object = (t_object *)px->hitobject;
	if (!object)
		return;
	px->color = ((object->rgb[0] << 24) | (object->rgb[1] << 16) | (object->rgb[2] << 8) | 255);
	if (object->text || object->text_proc)
		px->color = get_color[object->id](*object, *px);
}