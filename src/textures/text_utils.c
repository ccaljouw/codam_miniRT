/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   text_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/03 10:41:09 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/04 10:26:27 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

float	get_text_val(t_xyz coord)
{
	(void)coord;
	return (0);
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
	v_disp = v_create(0, 0, SHADOW_BIAS);
	(void)px;
	u_grad = get_text_val(v_divide(v_subtract(v_add(uv, u_disp),v_subtract(uv, u_disp)), 2 * SHADOW_BIAS));
	v_grad = get_text_val(v_divide(v_subtract(v_add(uv, v_disp),v_subtract(uv, v_disp)), 2 * SHADOW_BIAS));
	return(v_create(u_grad, v_grad, 0));
}

int	map_procedure(t_px *px)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	
	if(!px->hitobject)
		return (px->color);
	if (!px->hitobject->text_proc)
		return (px->color);
	uv = get_uv[px->hitobject->id](*px->hitobject, *px);
	if (px->hitobject->text_proc == 1)
		return (checkered(px, uv));
	if (px->hitobject->text_proc == 2)
		return (v_checkered(px, uv));
	return (px->color);	
}

int	map_texture(t_px *px, t_scene *scene)
{
	t_xyz			uv;
	static t_uv		*get_uv[4] = {get_uvcoord_sp, get_uvcoord_pl, \
		get_uvcoord_cy , get_uvcoord_co};
	static t_n_uv	*norm_uv[4] = {norm_uvcoord_sp, norm_uvcoord_pl, \
		norm_uvcoord_cy , norm_uvcoord_co};

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
	uv = get_uv[px->hitobject->id](*px->hitobject, *px);
	uv = norm_uv[px->hitobject->id](*px->hitobject, uv);
	scene->min_x = (uv.x < scene->min_x ? uv.x : scene->min_x);
	scene->max_x = (uv.x > scene->max_x ? uv.x : scene->max_x);
	scene->min_y = (uv.y < scene->min_y ? uv.y : scene->min_y);
	scene->max_y = (uv.y > scene->max_y ? uv.y : scene->max_y);
	px->color = get_text_pxcolor(px, px->hitobject->text, uv);
	return (px->color);	
}

