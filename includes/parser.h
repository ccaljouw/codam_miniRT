/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:10:24 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/11 11:58:58 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"
# include <pthread.h> 

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# ifndef THREADS
#  define THREADS 1
# endif

void			parse_file(char *file, t_scene *scene);
void			parse_type(char *line, t_scene *scene);
t_xyz			set_xyz(char *param, t_scene *scene);
void			set_rgb(char *param, int *rgb, t_scene *scene);
mlx_texture_t	*set_texture(char *param, t_scene *scene);
int				set_procedure(char *param, t_scene *scene);
int				set_bump_procedure(char *param, t_scene *scene);
float			set_specular_size(char *param, t_scene *scene);
float			set_specular_weight(char *param, t_scene *scene);
float			set_albedo(char *param, t_scene *scene);
void			set_surface_properties(char **param, t_object *obj, \
												int i, t_scene *s);
float			to_float(char *param, t_scene *scene);
void			init_ambient(char **param, t_scene *scene);
void			init_camera(char **param, t_scene *scene);
void			camera_geo(t_scene *scene);
void			init_lights(char **param, t_scene *s);
void			init_sphere(char **param, t_scene *scene);
void			init_plane(char **param, t_scene *scene);
void			init_cylinder(char **param, t_scene *scene);
void			init_cone(char **param, t_scene *scene);
void			init_resolution(char **param, t_scene *scene);
// void			calculate_angles(t_scene *scene);

#endif
