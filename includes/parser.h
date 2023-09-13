/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 12:26:43 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# define WIDTH  512
# define HEIGHT 512

typedef struct s_scene
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ambient	*ambient;
	t_camera	*camera;
	t_light		*light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}				t_scene;

typedef void	t_f(char **param, t_scene *data);

void	parse_type(char *line, t_scene *data);
void	set_xyz(char *param, t_xyz *position, t_scene *data);
void	set_rgb(char *param, uint32_t *rgb, t_scene *data);
float	to_float(char *param, t_scene *data);
void	ambient(char **param, t_scene *data);
void	camera(char **param, t_scene *data);
void	light(char **param, t_scene *data);
void	sphere(char **param, t_scene *data);
void	plane(char **param, t_scene *data);
void	cylinder(char **param, t_scene *data);

#endif
