/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_shapes.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/11 16:03:04 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/11 17:02:47 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	print_texture_settings(t_scene *s, t_object *obj, int fd)
{
	ft_dprintf(fd, "\t%i\t", get_texture_id(s, obj->text));
	ft_dprintf(fd, "%i\t", get_texture_id(s, obj->bump));
	ft_dprintf(fd, "%i\t%i\t\t", obj->text_proc, obj->bump_proc);
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->albedo * 100));
	ft_dprintf(fd, "%i\t\t\t\t\t\t", (int)(300 / obj->specular_size));
	ft_dprintf(fd, "%i\t\t\t", (int)(obj->specular_weight * 100));
	ft_dprintf(fd, "%.3f\t", obj->refl);
	p_rgb(obj->rgb, fd);
}

typedef void	t_print_object(t_object *object, t_scene *s, int fd);

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

void	print_sphere(t_object *sp, t_scene *s, int fd)
{
	(void)sp;
	(void)s;
	ft_dprintf(fd, "sp\t");
	p_v(sp->p_origin, fd);
	ft_dprintf(fd, "\t\t\t\t\t\t%.1f\t\t\t", round(sp->diameter * 10) / 10);
	print_texture_settings(s, sp, fd);
}

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
