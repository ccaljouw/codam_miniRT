/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:00:07 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/19 21:24:15 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Print the lights in scene struct [s] to [fd]
 * 
 * @param lights 
 * @param s 
 * @param fd 
 */
void	print_lights(t_list *lights, t_scene *s, int fd)
{
	t_light	*light;

	while (lights)
	{
		light = (t_light *)lights->content;
		if (s->single_light)
			ft_dprintf(fd, "L\t");
		else
			ft_dprintf(fd, "l\t");
		p_v(light->origin, fd);
		ft_dprintf(fd, "%f\t\t\t\t\t", light->brightness);
		p_rgb(light->rgb, fd);
		lights = lights->next;
	}
	ft_dprintf(fd, "\n");
}

/**
 * @brief Print the parameters of a scene to [fd]
 * 
 * @param s 
 * @param fd 
 * @param fname 
 */
void	print_scene(t_scene *s, int fd, char *fname)
{
	int	chars;

	p(fd, "#################################################\n");
	chars = ft_dprintf(fd, "#\t\t\t%s\t\t\t", fname);
	if (chars < 31)
		ft_dprintf(fd, "\t");
	p(fd, "#\n#################################################\n\n\n");
	p(fd, "#resolution\n#\twidth\theight\tanti-alias [0-5]\t# reflections\n");
	ft_dprintf(fd, "R\t%i\t\t%i\t\t%i\t\t\t\t\t%i\n\n", \
		s->file_width, s->file_height, (int)(floor(s->aa / 2)), s->max_reflect);
	p(fd, "#ambient\n#\tbrightness [0-1]\t\t\tcolor\n");
	ft_dprintf(fd, "A\t%.1f\t\t\t\t\t\t\t", s->ambient->ratio);
	p_rgb(s->ambient->rgb, fd);
	p(fd, "\n#lights (L for single, l for multiple)\n");
	p(fd, "#\torigin\t\t\t\t\tbrightness [0-1]\t\t\tcolor\n");
	print_lights(s->lights, s, fd);
	p(fd, "#camera\n#\torigin\t\t\t\t\torientation\t\t\t\t\tfield of view (deg)\n");
	p(fd, "C\t");
	p_v(s->camera->origin, fd);
	p_v(s->camera->orientation_v, fd);
	ft_dprintf(fd, "\t%i\n\n", s->camera->fov);
	p(fd, "#objects\n#ID\torigin | p0\t\t\t\taxis | p1\t\t\t\tdiameter | p2");
	p(fd, "\t\theight\tt\tbt\tp\tb\talbedo (%%)\t");
	p(fd, "specular_size (1-10)\tspec_weight (%%)\trefl\trefr\ttransp\tcolor\n");
	print_objects(s->objects, s, fd);
}

/**
 * @brief Get the index of the latest save_scene, increment it with one
 * 		and create a new file. Print the scene parameters to this file.
 * 
 * @param s 
 */
void	save_scene(t_scene *s)
{
	int			fd;
	static int	i;
	char		fname[100];

	ft_sprintf(fname, "scenes/saved_scene_%i.rt", i);
	while (access(fname, R_OK) != -1)
	{
		i++;
		ft_sprintf(fname, "scenes/saved_scene_%i.rt", i);
	}
	fd = open(fname, O_CREAT | O_RDWR, 0666);
	print_scene(s, fd, fname);
	close(fd);
	ft_printf("scene saved as [%s]\n", fname);
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
	static t_print_object	*print_object[7] = {print_sphere, print_plane, \
										print_cylco, print_cylco, print_cylco, \
										print_cylco, print_triangle};
	t_object				*obj;

	while (objects)
	{
		obj = (t_object *)objects->content;
		print_object[obj->id](obj, s, fd);
		objects = objects->next;
	}
}
