/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:38:40 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/16 15:06:08 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
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

typedef struct s_ray
{
	t_xyz	p1;
	t_xyz	p2;
	t_xyz	p1_p2;
}	t_ray;

void	exit_error(char *error_msg, char *optional_str, t_scene *data);
t_scene	*init_scene(char *file);
void	render_sphere(t_scene *scene, t_sphere *sphere);
bool	generate_ray(t_camera *cam, float screen_x, float screen_y, t_ray *cameraRay);
t_ray	ray(t_xyz p1, t_xyz p2);
void	cameraGeometry(t_camera *cam);
bool	close_points(float f1, float f2);
bool	test_intersection(t_ray castRay, t_xyz localNormal, int *localColor, t_sphere *sphere);

#endif
