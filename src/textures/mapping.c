/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mapping.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 21:18:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/27 21:49:30 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

int	get_texture(t_px px, t_object object)
{
	static t_get_color	*get_color[3] = {get_color_sphere, get_color_plane, \
		get_color_cylinder};
	
	px.color = get_color[object.id](object, px);
	return (px.color);
}
	// t_xyz		unit;
	// // t_xyz		p;
	// float		u;
	// float		v;
	/* unit is the unit vector form the hitpoint the sphere origen */  
	// if (object->id == SP)
		
	// {
		// unit = v_subtract(px->hitpoint, object->pOrigin);
		// v_normalizep(&unit);
		// u = atan2((pow(unit.y, 2) + pow(unit.z, 2)), unit.x);
		// v = atan2(unit.z, unit.y);
		// u = 1 - ((u + M_PI) / (2 * M_PI));
		// v = 1 - ((v + M_PI) / (2 * M_PI));
		// color = get_text_pxcolor(scene->rendering, u, v);
	// }
	// else if (object->id == CY)
	// {
	// 	unit = v_subtract(px->hitpoint, object->pOrigin);
	// 	v_normalizep(&unit);
	// 	u = atan2(unit.y, unit.x);
	// 	v = unit.z;
	// 	u = 1 - ((u + M_PI) / (2 * M_PI));
	// 	v = 1 - ((v + 1) * 0.5);
	// 	color = get_text_pxcolor(scene->rendering, u, v);
	// }
	// else if (object->id == PL)
	// {
	// 	unit = v_add(object->pOrigin, v_multiply(px->direction, px->hit_distance));
	// 	// unit = v_subtract(px->hitpoint, object->pOrigin);
	// 	v_normalizep(&unit);
	// 	u = unit.x;
	// 	v = unit.y;
	// 	u = ((u + 1.0) * 0.5);
	// 	v = ((v + 1.0) * 0.5);
	// 	// printf("u:%f, v:%f\n", u, v);
	// 	color = get_text_pxcolor(scene->rendering, u, v);
	// }
	// else
	// {
	// 	unit = v_subtract(px->hitpoint, object->pOrigin);
	// 	p.x = abs((int)floorf(unit.x)) % 2;
	// 	p.y = abs((int)floorf(unit.y)) % 2;
	// 	p.z = abs((int)floorf(unit.z)) % 2;
	// 	if (p.x == p.y == p.z)
	// 		color = (255 << 24 | 255 << 16 | 255 << 8 | 255);
	// 	else
	// 		color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	// }