/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:10:24 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/18 22:44:51 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "types.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 81
# endif

# define WIDTH  256
# define HEIGHT 256

typedef struct s_scene
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_ambient	*ambient;
	t_camera2	*camera2;
	t_light		*light;
	t_list		*objects;
}				t_scene;

typedef void	t_f(char **param, t_scene *scene);

void	parse_type(char *line, t_scene *scene);
t_xyz	set_xyz(char *param, t_scene *scene);
void	set_rgb(char *param, uint32_t *rgb, t_scene *scene);
float	to_float(char *param, t_scene *scene);
void	init_ambient(char **param, t_scene *scene);
void	init_camera2(char **param, t_scene *scene);
void	init_light(char **param, t_scene *scene);
void	init_sphere(char **param, t_scene *scene);
void	init_plane(char **param, t_scene *scene);
void	init_cylinder(char **param, t_scene *scene);

#endif
