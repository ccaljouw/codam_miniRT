/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/13 09:11:08 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 80
# endif

#define WIDTH  512
#define HEIGHT 512

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
void	set_xyz(char *param, t_xyz *position);
void	set_rgb(char *param, uint32_t *rgb);
float	to_float(char *param);
void	ambient(char **param, t_scene *data);
void	camera(char **param, t_scene *data);
void	light(char **param, t_scene *data);
void	sphere(char **param, t_scene *data);
void	plane(char **param, t_scene *data);
void	cylinder(char **param, t_scene *data);

#endif
