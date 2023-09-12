/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/12 18:43:51 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "types.h"

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 80
# endif

typedef struct s_scene
{
	t_ambient	*ambient;
	t_camera	*camera;
	t_light 	*light;
	t_sphere	*speres;
	t_plane		*planes;
	t_cylinder	*cylinders;
}			t_scene;

void	parse_type(char *line, t_scene *data);
void	parse_ambient(char *line, t_scene *data);
void	parse_camera(char *line, t_scene *data);
void	parse_light(char *line, t_scene *data);
void	parse_sphere(char *line, t_scene *data);
void	parse_plane(char *line, t_scene *data);
void	parse_cylinder(char *line, t_scene *data);


#endif
