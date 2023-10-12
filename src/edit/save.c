/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:00:07 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 09:52:00 by albertvanan      ###   ########.fr       */
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

	ft_dprintf(fd, "#################################################\n");
	chars = ft_dprintf(fd, "#\t\t\t%s\t\t\t", fname);
	if (chars < 31)
		ft_dprintf(fd, "\t");
	ft_dprintf(fd, "#\n#################################################\n\n\n");
	ft_dprintf(fd, "#resolution\n#\twidth\theight\n");
	ft_dprintf(fd, "R\t%i\t\t%i\n\n", s->p_width, s->p_height);
	ft_dprintf(fd, "#ambient\n#\tbrightness [0-1]\t\t\tcolor\n");
	ft_dprintf(fd, "A\t%.1f\t\t\t\t\t\t\t", s->ambient->ratio);
	p_rgb(s->ambient->rgb, fd);
	ft_dprintf(fd, "\n#lights (L for single, l for multiple)\n");
	ft_dprintf(fd, "#\torigin\t\t\t\t\tbrightness [0-1]\t\t\tcolor\n");
	print_lights(s->lights, s, fd);
	ft_dprintf(fd, "#camera\n#\torigin\t\t\t\t\torientation\t\t\t\t\tfield of view (deg)\n");
	ft_dprintf(fd, "C\t");
	p_v(s->camera->origin, fd);
	p_v(s->camera->orientation_v, fd);
	ft_dprintf(fd, "\t%i\n\n", s->camera->fov);
	ft_dprintf(fd, "#objects\n#ID\torigin\t\t\t\t\taxis\t\t\t\tdiameter\theight\t");
	ft_dprintf(fd, "t\tbt\tp\tb\talbedo (%%)\t");
	ft_dprintf(fd, "specular_size (1-10)\tspec_weight (%%)\trefl\tcolor\n");
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
