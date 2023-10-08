/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:50:10 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:56:43 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

mlx_texture_t	*set_texture(char *param, t_scene *scene)
{
	int				n;

	n = ft_atoi(param);
	if (n < 0 || n > NR_TEXTURES)
		exit_error(ERROR_PNG, "texture id invallid", scene);
	if (n && n <= NR_TEXTURES)
		return (scene->textures[n - 1]);
	return (NULL);
}

void	set_surface_properties(char **param, t_object *obj, int i, t_scene *s)
{
	obj->text = set_texture(param[i++], s);
	obj->bump = set_texture(param[i++], s);
	obj->text_proc = set_procedure(param[i++], s);
	obj->bump_proc = set_bump_procedure(param[i++], s);
	obj->albedo = set_albedo(param[i++], s);
	obj->specular_size = set_specular_size(param[i++], s);
	obj->specular_weight = set_specular_weight(param[i++], s);
	set_rgb(param[i], obj->rgb, s);
}
