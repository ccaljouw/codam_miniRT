/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:42:48 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 14:44:41 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

int	get_triangle_surface_data(t_object *tr, t_px *px)
{
	(void)tr;
	(void)px;

	return (1);
}

t_xyz	get_uvcoord_tr(t_object *tr, t_px *px, t_scene *scene)
{
	(void)tr;
	(void)px;
	(void)scene;
	return(v_create(0, 0 , 0));
}

int	test_triangle(t_px *ray, t_object *tr, float *hp_info)
{
	(void)tr;
	(void)hp_info;
	(void)ray;
	return (1);
}