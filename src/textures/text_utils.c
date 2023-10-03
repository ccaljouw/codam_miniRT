/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:41:09 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/03 12:59:41 by ccaljouw         ###   ########.fr       */
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

void	get_text_color(t_px *px)
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
