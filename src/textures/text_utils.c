/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 10:41:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/11 22:58:57 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

float	get_uv(t_px *px, t_scene *scene)
{
	static t_uv	*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy, get_uvcoord_co};

	px->uv = get_uv[px->hitobject->id](px->hitobject, px, scene);
	return (0);
}

void	map_texture(t_px *px)
{
	if (!!px->hitobject)
		px->color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
	if (!px->hitobject->text)
		px->color = (px->hitobject->rgb[0] << 24 | px->hitobject->rgb[1] << 16 \
			| px->hitobject->rgb[2] << 8 | 255);
	else
		px->color = get_text_pxcolor(px->hitobject->text, px->uv);
}

int	map_procedure(t_px *px)
{
	if (!px->hitobject)
		return (px->color);
	if (!px->hitobject->text_proc)
		return (px->color);
	if (px->hitobject->text_proc == 1)
		return (checkered(px, 2));
	if (px->hitobject->text_proc == 2)
		return (checkered(px, 3));
	if (px->hitobject->text_proc == 3)
		return (gradient(px, color_map_rb));
	if (px->hitobject->text_proc == 4)
		return (gradient(px, color_map_bw));
	if (px->hitobject->text_proc == 5)
		return (gradient_interpolated(px, color_map_rb));
	if (px->hitobject->text_proc == 6)
		return (gradient_interpolated(px, color_map_bw));
	return (px->color);
}

/**
 * @brief return interpolated value based on v1 and v2 (linear interpolation)
 * 
 * @param v1 (float) fisrt value;
 * @param v2 (float) second value;
 * @param pos (float) position to get the value for
 * @param smooth (int) if set to 1, smooth step algorithm applied to pos
 * @return float 
 */
float	linear_interpolation(float v1, float v2, float pos, int smooth)
{
	float	fade;

	fade = pos;
	if (smooth)
		fade = pos * pos * (3 - 2 * pos);
	return (v1 + fade * (v2 - v1));
}

/**
 * @brief interpolates x and y positions on scale [0,1] for x and [0,1] for y;
 * 
 * @param v1 
 * @param v2 
 * @param pos1 
 * @param pos2 
 * @return float 
 */
float	bilinear_interpolation(float v1, float v2)
{
	float	val1;
	float	val2;

	val1 = linear_interpolation(0, 1, v2, 1);
	val2 = linear_interpolation(0, 1, v2, 1);
	return (linear_interpolation(val1, val2, v1, 1));
}
