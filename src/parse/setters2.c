/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   setters2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/08 23:50:10 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/13 10:17:48 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

mlx_texture_t	*set_texture(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > NR_TEXTURES)
		exit_error(ERROR_PNG, "texture id invalid", scene);
	if (n && n <= NR_TEXTURES)
		return (scene->textures[n - 1]);
	return (NULL);
}

void	set_surface_properties(char **param, t_object *obj, int i, t_scene *s)
{
	if (BONUS && i > 0)
	{
		obj->text = set_texture(*param, s);
		if (obj->text && obj->id == PL)
		{
			obj->plane_z = (obj->text->height * sqrtf(s->file_height)) / s->file_height;
			obj->plane_x = (obj->text->width * sqrtf(s->file_height)) / s->file_width;
		}
		obj->bump = set_texture(*(param + 1), s);
		obj->text_proc = set_procedure(*(param + 2), s);
		obj->bump_proc = set_bump_procedure(*(param + 3), s);
		obj->albedo = set_albedo(*(param + 4), s);
		obj->specular_size = set_specular_size(*(param + 5), s);
		obj->specular_weight = set_specular_weight(*(param + 6), s);
		obj->refl = to_float(*(param + 7), s);
		obj->refr = to_float(*(param + 8), s);
		obj->transp = to_float(*(param + 9), s);
		set_rgb(*(param + 10), obj->rgb, s);
	}
	else
	{
		obj->albedo = .18;
		set_rgb(*(param), obj->rgb, s);
	}
}
