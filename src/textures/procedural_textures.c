/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   procedural_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 21:18:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 13:29:29 by ccaljouw         ###   ########.fr       */
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

int	v_checkered(t_px px, float x, float y, float z)
{

	x = fabs(floor(x));
	y = fabs(floor(y));
	z = fabs(floor(z));
	x = (int)x % 3;
	y = (int)y % 3;
	z = (int)z % 3;
	if (!(((int)x ^ (int)y) ^ (int)z))
		px.color = invert_color(px.color);
	return (px.color);
}

int	map_procedure(t_px px)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	
	if (!px.hitobject->text_proc)
		return (px.color);
	uv = get_uv[px.hitobject->id](*px.hitobject, px);
	if (px.hitobject->text_proc == 1)
		return (checkered(px, uv.x, uv.y, uv.z));
	if (px.hitobject->text_proc == 2)
		return (v_checkered(px, uv.x, uv.y, uv.z));
	return (px.color);	
}

int	map_texture(t_px px)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	static t_n_uv	*norm_uv[4] = {norm_uvcoord_sp, norm_uvcoord_pl, \
		norm_uvcoord_cy , norm_uvcoord_co};
	
	if (!px.hitobject->text)
	{
		px.color = (px.hitobject->rgb[0] << 24 | px.hitobject->rgb[1] << 16 | px.hitobject->rgb[2] << 8 | 255);
		return (px.color);
	}
	uv = get_uv[px.hitobject->id](*px.hitobject, px);
	uv = norm_uv[px.hitobject->id](*px.hitobject, uv);
	px.color = get_text_pxcolor(&px, px.hitobject->text, uv);
	return (px.color);	
}