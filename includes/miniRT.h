/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:38:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/07 19:01:15 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42.h>
# include <libft.h>
# include <stdbool.h>
# include <defines.h>
# include <errors.h>
# include <types.h>
# include <vector.h>
# include <matrix.h>
# include <parser.h>
# include <stdlib.h>
# include <math.h>

// fuction pointer for intersection test functions of different objects
typedef int		t_hit_test(t_px *ray, t_object, float *hp_info);
typedef int		t_surface_data(t_object obj, t_px *px);
typedef int		t_get_color(t_object obj, t_px px);
typedef	t_xyz	t_uv(t_object obj, t_px px, t_scene *scene);
typedef	t_xyz	t_n_uv(t_object obj, t_xyz uv);

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);
void	replace(char *str, char replace, char with);
int		invert_color(int color);
void	print_vector(t_xyz vector);
float	ft_clamp(float min, float max, float input);
void	clean_scene(t_scene *scene);

// main.c
t_scene	*init_scene(char *file);
void	init_pixels(t_scene *scene);

// render_ascii.c
void	renderAscii(t_scene *scene);
int		get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2);

// render.c
void	get_ray(t_px *px, int x, int y, t_scene *s);
void	trace_ray(t_px *px, t_scene *s);
void	get_surface_data(t_px *px);
float	ft_clamp(float min, float max, float input);
void	render_image(t_scene *scene);

// objects/sphere.c
int		test_sphere(t_px *ray, t_object sphere, float *hp_info);
int		get_sphere_surface_data(t_object sph, t_px *px);
t_xyz	get_uvcoord_sp(t_object sp, t_px px, t_scene *scene);

// objects/plane.c
int		test_plane(t_px *ray, t_object plane, float *hp_info);
int		get_plane_surface_data(t_object plane, t_px *px);
t_xyz	get_uvcoord_pl(t_object pl, t_px px, t_scene *scene);

// objects/cylinder.c
int		test_cylinder(t_px *ray, t_object cylinder, float *hp_info);
int		get_cylinder_surface_data(t_object cy, t_px *px);
t_xyz	get_uvcoord_cy(t_object cy, t_px px, t_scene *scene);

// objects/cone.c
int		test_cone(t_px *ray, t_object cone, float *hp_info);
int		get_cone_surface_data(t_object co, t_px *px);
t_xyz	get_uvcoord_co(t_object co, t_px px, t_scene *scene);

// multithreading.c
pthread_t	*create_threads(t_scene *scene, pthread_t *threads, t_block *blocks);
void		join_threads(pthread_t *threads, t_scene *scene);

// image_mainpulation.c
void	set_resize_flag(int width, int height, void	*param);
void	key_input(mlx_key_data_t k, void *param);
void	zoom(mlx_key_data_t keydata, t_scene *scene);
void	rotate(mlx_key_data_t keydata, t_scene *scene);

// image_utils.c
void	image_to_window(t_scene *scene);
int		get_color(t_px *px, t_scene *scene);
void	select_object(mouse_key_t b, action_t a, modifier_key_t mod, void *param);
void	draw_image(t_scene *scene);
int		get_text_pxcolor(mlx_texture_t *text, t_xyz uv);

// bump_mapping.c
void	map_normal(t_px *px);
void	perturb_normal(t_px *px, t_xyz pertubation);
void	simple_rough(t_px *px, float min, float max);

// procedural_textures.c
int	checkered(t_px *px, int mod);
int	gradient(t_px *px);

// color_maps.c
t_xyz	color_map_5s(float pos);

// text_utils.c
int		map_procedure(t_px *px);
void	map_texture(t_px *px);
float	linear_interpolation(float v1, float v2, float pos, int smooth);
float	bilinear_interpolation(float v1, float v2);
float	get_uv(t_px *px, t_scene *scene);

// shadow_ray.c
float	get_shadow_ray(t_px *shadow_ray, t_light *light, t_px *px);
int		trace_shadow(t_px *px, t_scene *s);
void	loop_lights(t_scene *scene, t_px *px);
float	v_square_of_self(t_xyz a);

#endif
