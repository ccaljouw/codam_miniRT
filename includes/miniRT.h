/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:38:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/19 07:04:26 by cariencaljo   ########   odam.nl         */
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
typedef bool f_testHit(t_ray camera2Ray, t_object *object, float *t);

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);

// main.c
t_scene	*init_scene(char *file);

// objects/camera2.c
t_ray	ray(t_xyz p1, t_xyz p2);
t_ray	generate_ray(t_scene * scene, int x, int y);
void	update_camera2(t_scene *scene);
void	cameraGeometry(t_camera *cam);

// render_ascii.c
void	renderAscii(t_scene *scene);
int		get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2);
int		test_sphere(t_px ray, t_object sphere, float *hit_dist);
float	get_sphere_surface_data(float hp_distance, t_object *sph, t_px *px);
void	trace_ray(t_px *px, t_scene *s, int x, int y);
void	loop_pixels(t_scene *scene, t_px *px);
void	prepare_camera(t_camera *cam);

// render.c
void	render(t_scene *scene);
void	renderTest(t_scene *scene); 

// objects
bool	testHitSP(t_ray castRay, t_object *sphere, float *intPoint);
// bool	testHitPL(t_ray castRay, t_object *plane, float *intPoint);
// bool	testHitCY(t_ray castRay, t_object *cylinder, float *intPoint);


#endif
