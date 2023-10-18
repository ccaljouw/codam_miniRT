/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:38:40 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/18 09:48:23 by ccaljouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <stdbool.h>
# include <defines.h>
# include <errors.h>
# include <vector.h>
# include <matrix.h>
# include <types.h>
# include <parser.h>
# include <stdlib.h>
# include <math.h>
# include <save.h>

//utils.c
void		exit_error(char *error_msg, char *optional_str, t_scene *data);
void		swap(float *x1, float *x2);
void		replace(char *str, char replace, char with);
int			invert_color(int color);
void		print_vector(t_xyz vector);
float		ft_clamp(float min, float max, float input);
void		clean_scene(t_scene *scene);

// main.c

// init.c
t_scene		*init_scene(char *file);
void		init_pixels(t_scene *scene);
void		check_args(int argc, char **argv);
void		init_textures(t_scene *scene);

// render_ascii.c
void		render_ascii(t_scene *scene);
int			get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2);

// render.c
void		get_ray(t_px *px, int x, int y, t_scene *s);
void		trace_ray(t_px *px, t_scene *s);
int			get_pixel_data(t_px	*px, t_scene *scene);
void		render_image(t_scene *scene);
void		*render_routine(void *params);

// objects/sphere.c
int			test_sphere(t_px *ray, t_object *sphere, float *hp_info);
int			get_sphere_surface_data(t_object *sph, t_px *px);
t_xyz		get_uvcoord_sp(t_object *sp, t_px *px, t_scene *scene);

// objects/plane.c
int			test_plane(t_px *ray, t_object *plane, float *hp_info);
int			get_plane_surface_data(t_object *plane, t_px *px);
t_xyz		get_uvcoord_pl(t_object *pl, t_px *px, t_scene *scene);

// objects/cylinder.c
int			test_cylinder(t_px *ray, t_object *cylinder, float *hp_info);
int			get_cylinder_surface_data(t_object *cy, t_px *px);
t_xyz		get_uvcoord_cy(t_object *cy, t_px *px, t_scene *scene);

// objects/cone.c
int			test_cone(t_px *ray, t_object *cone, float *hp_info);
int			get_cone_surface_data(t_object *co, t_px *px);
t_xyz		get_uvcoord_co(t_object *co, t_px *px, t_scene *scene);

// objects/triangle.c
int			test_triangle(t_px *ray, t_object *sphere, float *hp_info);
int			get_triangle_surface_data(t_object *tr, t_px *px);
t_xyz		get_uvcoord_tr(t_object *sp, t_px *px, t_scene *scene);

// multithreading.c
pthread_t	*create_threads( \
			t_scene *scene, pthread_t *threads, t_block *blocks);
void		join_threads(pthread_t *threads, t_scene *scene);
t_block		set_block(t_scene *scene, int y, int blocksize);
void		render_threads(t_scene *scene);

// key_hooks.c
void		key_input(mlx_key_data_t k, void *param);

// resize_select.c
void		select_light(t_scene *scene);
void		set_resize_flag(int width, int height, void	*param);
void		do_resize(void *param);
void		select_object( \
			mouse_key_t b, action_t a, modifier_key_t mod, void *param);

// image_manipulation.c
void		scale(mlx_key_data_t keydata, t_scene *scene);
void		rotate(mlx_key_data_t keydata, t_scene *scene);
void		adjust_ambient(t_scene *scene, mlx_key_data_t key_data);
void		move(mlx_key_data_t keydata, t_scene *scene);

// param_adjustments.c
void		adjust_reflections(t_scene *s, mlx_key_data_t k);
void		adjust_transparancy(t_scene *s, mlx_key_data_t k);
void		change_texture(t_scene *s, mlx_key_data_t k);
void		change_aa(t_scene *s);
void		change_bump(t_scene *scene, mlx_key_data_t k);

// image_utils.c
void		image_to_window(t_scene *scene, mlx_image_t *image);
int			get_color(t_px *px, t_scene *scene);
void		draw_image(t_scene *scene);
void		draw_black(t_scene *scene);
int			get_text_pxcolor(mlx_texture_t *text, t_xyz uv);

// antialias.c
void		draw_aa(t_scene *scene);
int			get_aa_color(int x, int y, t_scene *s);

// bump_mapping.c
void		map_normal(t_px *px);
void		perturb_normal(t_px *px, t_xyz pertubation);
void		simple_rough(t_px *px, float min, float max);

// procedural_textures.c
int			checkered(t_px *px, int mod);
int			gradient(t_px *px, t_colormap map);
int			gradient_interpolated(t_px *px, t_colormap map);

// color_maps.c
t_xyz		color_map_rb(float pos);
t_xyz		color_map_bw(float pos);

// text_utils.c
int			map_procedure(t_px *px);
void		map_texture(t_px *px);
float		linear_interpolation(float v1, float v2, float pos, int smooth);
float		bilinear_interpolation(float v1, float v2);
float		get_uv(t_px *px, t_scene *scene);

// save.c
void		save_scene(t_scene *s);

// add_delete.c
void		delete_object(t_scene *scene);
void		add_object(t_scene *scene, int id);
void		add_light(t_scene *scene);

// light_manipulations.c
void		adjust_light_brightness(mlx_key_data_t keydata, t_light *light);
void		adjust_ambient(t_scene *scene, mlx_key_data_t key_data);

// shadow_ray.c
float		get_shadow_ray(t_px *shadow_ray, t_light *light, t_px *px);
int			trace_shadow(t_px *px, t_scene *s);
void		loop_lights(t_scene *scene, t_px *px);

void		specular(t_light *light, t_px *shadow_ray, t_px *px);
void		diffuse(t_light *light, \
					t_px *px, t_px *shadow_ray, float light_radius);

// refl_refr.c
void		light_transport(t_px *px, t_scene *scene);
t_xyz		reflect_ray(t_xyz normal, t_xyz angle);
t_xyz		refract_ray(t_px *px, t_xyz normal);
int			blend_color(int c1, int c2, float fact_c1);

#endif
