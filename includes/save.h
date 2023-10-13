/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:01:02 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/13 16:17:17 by albertvanan      ###   ########.fr       */
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

#endif
