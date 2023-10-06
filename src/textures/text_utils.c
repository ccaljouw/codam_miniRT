/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 10:41:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/06 17:00:30 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

float	get_text_val(mlx_texture_t *text, t_xyz n_uv)
{
	(void)n_uv;
	(void)text;
	return (0);
}

t_xyz	partial_diff(t_xyz disp, t_xyz uv, float h)
{
	t_xyz	diff;
	t_xyz	part1;
	t_xyz	part2;
	
	part1 = v_add(uv, disp);
	part2 = v_subtract(uv, disp);
	diff = v_divide(v_subtract(part1, part2), 2 * h);
	return (diff);
}

/**
 * @brief use the symmetric difference quotient to estimate the partial derivatives 
 * of the texture at the point uv
 * 
 * @param px 
 * @param uv 
 */
t_xyz	texture_diff(t_px *px, t_xyz uv)
{
	t_xyz	u_disp;
	t_xyz	v_disp;
	float	u_grad;
	float	v_grad;
	
	u_disp = v_create(SHADOW_BIAS, 0, 0);
	v_disp = v_create(0, SHADOW_BIAS, 0); //on y or z?
	u_grad = get_text_val(px->hitobject->text, partial_diff(u_disp, uv, SHADOW_BIAS));
	v_grad = get_text_val(px->hitobject->text, partial_diff(v_disp, uv, SHADOW_BIAS));
	return(v_create(u_grad, v_grad, 0));
}

int	map_procedure(t_px *px, t_scene *scene)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	
	if(!px->hitobject)
		return (px->color);
	if (!px->hitobject->text_proc)
		return (px->color);
	uv = get_uv[px->hitobject->id](*px->hitobject, *px, scene);
	if (px->hitobject->text_proc == 1)
		return (checkered(px, uv, scene));
	if (px->hitobject->text_proc == 2)
		return (v_checkered(px, uv));
	if (px->hitobject->text_proc == 3)
		return (gradient(px, uv));
	return (px->color);	
}

int	map_texture(t_px *px, t_scene *scene)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};

	if (!px->hitobject)
	{
		px->color = (0 << 24 | 0 << 16 | 0 << 8 | 255);
		return (px->color);
	}
	if (!px->hitobject->text)
	{
		px->color = (px->hitobject->rgb[0] << 24 | px->hitobject->rgb[1] << 16 | px->hitobject->rgb[2] << 8 | 255);
		return (px->color);
	}
	uv = get_uv[px->hitobject->id](*px->hitobject, *px, scene);
	scene->min_x = (uv.x < scene->min_x ? uv.x : scene->min_x); // for testing
	scene->max_x = (uv.x > scene->max_x ? uv.x : scene->max_x);  // for testing
	scene->min_y = (uv.y < scene->min_y ? uv.y : scene->min_y); // for testing
	scene->max_y = (uv.y > scene->max_y ? uv.y : scene->max_y); // for testing
	px->color = get_text_pxcolor(px, px->hitobject->text, uv); // for testing
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
	float fade;

	fade = pos;
	if (smooth)
		fade = pos * pos * (3 - 2 * pos);
	return (v1 + fade * (v2 - v1));
}


