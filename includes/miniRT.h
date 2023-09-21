/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:38:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/21 13:36:45 by ccaljouw      ########   odam.nl         */
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


/**
 * @brief ray struct that contains:
 * @param	p1 (t_xyz) camera2 origin
 * @param	p2 (t_xyz) camera2 direction
 * @param	p1_p2 (t_xyz) distance between p1 and p2
 */
typedef struct s_ray
{
	t_xyz	p1;
	t_xyz	p2;
	t_xyz	p1_p2;
}	t_ray;

/**
 * @brief struct containing two floats
 * @param	t0 (float)
 * @param	t1 (float)
 */
typedef struct s_t
{
	float	t0;
	float	t1;
}			t_t;

/**
 * @brief struct with relevant render information for each pixel
 * @param	type		(enum)
 * @param	tNear		(float)
 * @param	hitobject	(void *)
 */
typedef struct s_renderInfo
{
	// enum		type;
	float		tNear;
	t_xyz		p;
	t_object 	*hitObject;
}				t_rederInfo;

// fuction pointer for intersection test functions of different objects
typedef int		t_hit_test(t_px ray, t_object, float *hit_dist);
typedef int		t_surface_data(t_object obj, t_px px, t_scene scene);

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);
void	clean_pixels(t_scene *scene);

// main.c
t_scene	*init_scene(char *file);

// render_ascii.c
void	renderAscii(t_scene *scene);
int		get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2);
int		test_sphere(t_px ray, t_object sphere, float *hit_dist);
int		test_plane(t_px ray, t_object plane, float *hit_dist);
void	trace_ray(t_px *px, t_scene *s, int x, int y);

// render.c
uint32_t	getColor(t_px	px, t_scene *scene);
void		renderImage(t_scene *scene);

// objects
int		test_sphere(t_px ray, t_object sphere, float *hit_dist);
int		get_sphere_surface_data(t_object sph, t_px px, t_scene scene);
int		test_plane(t_px ray, t_object plane, float *hit_dist);
int		get_plane_surface_data(t_object plane, t_px px, t_scene scene);
int		test_cylinder(t_px ray, t_object sphere, float *hit_dist);
int		get_cylinder_surface_data(t_object cy, t_px px, t_scene scene);

// multithreading.c
pthread_t	*create_threads(t_scene *scene);
void		join_threads(pthread_t *threads, t_scene *scene);


int	check_object(t_scene *scene, int x, int y);

#endif
