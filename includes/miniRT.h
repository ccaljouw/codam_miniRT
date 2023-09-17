/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   miniRT.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:38:40 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/17 08:13:58 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libs/MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include "errors.h"
# include "parser.h"
# include "vector.h"
# include "test.h"
# include <stdbool.h>
# include <stdlib.h>
# include "matrix.h"

# include <stdio.h> //remove

# define EPSILON exp(-21)

/**
 * @brief ray struct that contains:
 * @param	p1 (t_xyz) camera origin
 * @param	p2 (t_xyz) camera direction
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
	t_sphere 	*hitObject;
}				t_rederInfo;

//utils.c
void	exit_error(char *error_msg, char *optional_str, t_scene *data);
void	swap(float *x1, float *x2);

// main.c
t_scene	*init_scene(char *file);

// objects/general.c
bool	generate_ray(t_camera *cam, float screen_x, float screen_y, t_ray *cameraRay);
t_ray	ray(t_xyz p1, t_xyz p2);

// objects/camera.c
void	cameraGeometry(t_camera *cam);
bool	close_points(float f1, float f2);


// render.c
void	render(t_scene *scene);

// objects/sphere.c
void	render_sphere(t_scene *scene, t_sphere *sphere);
bool	test_spIntersection(t_ray castRay, int *localColor, t_sphere *sphere, float *intPoint);

#endif
