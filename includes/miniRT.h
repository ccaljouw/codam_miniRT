/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:38:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/24 12:36:10 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "errors.h"
# include "types.h"
# include "vector.h"
# include "matrix.h"
# include "parser.h"
# include "test.h"
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include "vector.h"
# include "matrix.h"


# include <stdio.h> //remove

# define EPSILON exp(-21)

// fuction pointer for intersection test functions of different objects
typedef int		t_hit_test(t_px ray, t_object, float *hit_dist);
typedef int		t_surface_data(t_object obj, t_px *px, t_scene scene);

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);
void	replace(char *str, char replace, char with);
int		invert_color(int color);
void	clean_pixels(t_scene *scene);
void	print_vector(t_xyz vector);

// main.c
t_scene	*init_scene(char *file);
void	init_pixels(t_scene *scene);

// render_ascii.c
void	renderAscii(t_scene *scene);
int		get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2);
int		test_sphere(t_px ray, t_object sphere, float *hit_dist);
int		test_plane(t_px ray, t_object plane, float *hit_dist);

// render.c
void	get_ray(t_px *px, int x, int y, t_scene *s);
void	trace_ray(t_px *px, t_scene *s);
int		getColor(t_px	*px, t_scene *scene);
void	render_image(t_scene *scene);

// objects
int		test_sphere(t_px ray, t_object sphere, float *hit_dist);
int		get_sphere_surface_data(t_object sph, t_px *px, t_scene scene);
int		test_plane(t_px ray, t_object plane, float *hit_dist);
int		get_plane_surface_data(t_object plane, t_px *px, t_scene scene);
int		test_cylinder(t_px ray, t_object sphere, float *hit_dist);
int		get_cylinder_surface_data(t_object cy, t_px *px, t_scene scene);

// multithreading.c
pthread_t	*create_threads(t_scene *scene, pthread_t *threads);
void		join_threads(pthread_t *threads, t_scene *scene);

// image_mainpulation.c
void	key_input(mlx_key_data_t k, void *param);
void	zoom(mlx_key_data_t keydata, t_scene *scene);
void	rotate(mlx_key_data_t keydata, t_scene *scene);

// image_utils.c
void	resize(void	*param);
void	select_object(mouse_key_t b, action_t a, modifier_key_t mod, void *param);
void	draw_image(t_scene *scene);
void	image_to_window(t_scene *scene);
void	set_image_size(t_scene *scene, int	width, int height);

// int	check_object(t_scene *scene, int x, int y);

#endif
