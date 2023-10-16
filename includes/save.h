/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:01:02 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 16:16:13 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVE_H
# define SAVE_H

void	print_objects(t_list *objects, t_scene *s, int fd);
int		get_texture_id(t_scene *s, mlx_texture_t *text);
void	p_v(t_xyz v, int fd);
void	p_rgb(int rgb[3], int fd);
void	p(int fd, char *s);
int		get_texture_id(t_scene *s, mlx_texture_t *text);

void	print_texture_settings(t_scene *s, t_object *obj, int fd);
void	print_plane(t_object *pl, t_scene *s, int fd);
void	print_cylco(t_object *cy, t_scene *s, int fd);
void	print_sphere(t_object *sp, t_scene *s, int fd);
void	print_triangle(t_object *tr, t_scene *s, int fd);
#endif
