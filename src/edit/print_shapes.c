/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_shapes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:03:04 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/12 10:25:31 by cariencaljo   ########   odam.nl         */
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
	ft_dprintf(fd, "\t%i\t", get_texture_id(s, obj->text));
	ft_dprintf(fd, "%i\t", get_texture_id(s, obj->bump));
	ft_dprintf(fd, "%i\t%i\t\t", obj->text_proc, obj->bump_proc);
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->albedo * 100));
	if (obj->specular_size != 0)
		ft_dprintf(fd, "%i\t\t\t\t\t\t", (int)(300 / obj->specular_size));
	else
		ft_dprintf(fd, "0\t\t\t\t\t\t");
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->specular_weight * 100));
	ft_dprintf(fd, "%.3f\t", obj->refl);
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
	(void)pl;
	(void)s;
	ft_dprintf(fd, "pl\t");
	p_v(pl->p_origin, fd);
	p_v(pl->v_normal, fd);
	ft_dprintf(fd, "\t\t\t");
	print_texture_settings(s, pl, fd);
}

/**
 * @brief Print a cylinder or cone objet to file descriptor [fd]
 * 
 * @param cy 
 * @param s 
 * @param fd 
 */
void	print_cylinder(t_object *cy, t_scene *s, int fd)
{
	(void)cy;
	(void)s;
	if (cy->id == CO)
		ft_dprintf(fd, "co\t");
	else
		ft_dprintf(fd, "cy\t");
	p_v(cy->p_origin, fd);
	p_v(cy->v_normal, fd);
	ft_dprintf(fd, "%.1f\t\t", round(cy->diameter * 10) / 10);
	ft_dprintf(fd, "%.1f\t", round(cy->height * 10) / 10);
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
	(void)sp;
	(void)s;
	ft_dprintf(fd, "sp\t");
	p_v(sp->p_origin, fd);
	ft_dprintf(fd, "\t\t\t\t\t\t%.1f\t\t\t", round(sp->diameter * 10) / 10);
	print_texture_settings(s, sp, fd);
}

/**
 * @brief Loop through the [objects] list and print it to [fd]
 * 
 * @param objects 
 * @param s 
 * @param fd 
 */
void	print_objects(t_list *objects, t_scene *s, int fd)
{
	static t_print_object	*print_object[4] = {print_sphere, print_plane, \
										print_cylinder, print_cylinder};
	t_object				*obj;

	while (objects)
	{
		obj = (t_object *)objects->content;
		print_object[obj->id](obj, s, fd);
		objects = objects->next;
	}
}
