/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:03:04 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/24 13:02:54 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Print the texture and surface settings of [obj] 
 * 			to file descriptor [fd]
 * 
 * @param s 
 * @param obj 
 * @param fd 
 */
void	print_texture_settings(t_scene *s, t_object *obj, int fd)
{
	ft_dprintf(fd, "%i\t", get_texture_id(s, obj->text));
	ft_dprintf(fd, "%i\t", get_texture_id(s, obj->bump));
	ft_dprintf(fd, "%i\t%i\t\t", obj->text_proc, obj->bump_proc);
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->albedo * 100));
	if (obj->specular_size != 0)
		ft_dprintf(fd, "%i\t\t\t\t\t\t", (int)(300 / obj->specular_size));
	else
		ft_dprintf(fd, "0\t\t\t\t\t\t");
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->specular_weight * 100));
	ft_dprintf(fd, "%.3f\t", obj->refl);
	ft_dprintf(fd, "%.3f\t", obj->refr);
	ft_dprintf(fd, "%.3f\t", obj->transp);
	p_rgb(obj->rgb, fd);
}

/**
 * @brief Print a plane object to file descriptor [fd]
 * 
 * @param pl 
 * @param s 
 * @param fd 
 */
void	print_plane(t_object *pl, t_scene *s, int fd)
{
	ft_dprintf(fd, "pl\t");
	p_v(pl->p_origin, fd);
	p_v(pl->v_normal, fd);
	ft_dprintf(fd, "\t\t\t\t\t\t\t");
	print_texture_settings(s, pl, fd);
}

/**
 * @brief Print a cylinder or cone objet to file descriptor [fd]
 * 
 * @param cy 
 * @param s 
 * @param fd 
 */
void	print_cylco(t_object *cy, t_scene *s, int fd)
{
	static char	*names[4] = {"cy", "ccy", "co", "cco"};

	ft_dprintf(fd, "%s\t", names[cy->id - 2]);
	p_v(cy->p_origin, fd);
	p_v(cy->v_normal, fd);
	ft_dprintf(fd, "%.1f\t\t\t\t\t", round(cy->diameter * 10) / 10);
	ft_dprintf(fd, "%.1f\t\t", round(cy->height * 10) / 10);
	print_texture_settings(s, cy, fd);
}

/**
 * @brief Print a sphere object to file descriptor [fd]
 * 
 * @param sp 
 * @param s 
 * @param fd 
 */
void	print_sphere(t_object *sp, t_scene *s, int fd)
{
	ft_dprintf(fd, "sp\t");
	p_v(sp->p_origin, fd);
	ft_dprintf(fd, "\t\t\t\t\t\t%.1f\t\t\t\t\t\t\t", \
							round(sp->diameter * 10) / 10);
	print_texture_settings(s, sp, fd);
}

void	print_triangle(t_object *tr, t_scene *s, int fd)
{
	ft_dprintf(fd, "tr\t");
	p_v(tr->p[0], fd);
	p_v(tr->p[1], fd);
	p_v(tr->p[2], fd);
	ft_dprintf(fd, "\t");
	print_texture_settings(s, tr, fd);
}
