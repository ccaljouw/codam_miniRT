/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:11:39 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/12 14:48:53 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	*routine(void *params)
{
	int		x;
	int		y;
	t_scene	*scene;
	t_block	*block;

	block = (t_block *)params;
	scene = block->scene;
	y = block->y;
	while (y < block->y_max)
	{
		x = 0;
		while (x < scene->p_width)
		{
			scene->pixels[y][x].refl_count = 0;
			get_pixel_data(scene->pixels[y] + x, scene, x, y);
			x++;
		}
		y++;
	}
	return (NULL);
}

/**
 * @brief Get the ray object. 
 * 		* 	adds the cam origin to each pixel struct
 *
 * 		*	recalculates the pixels from raster space (ie 1024 x 768) 
 * 			to normalized device coordinates (NDC)-space (0,1)
 * 			to screen space (-1, 1) in one fell swoop,
 * 			accpounts for the aspect ratio and field of fiev 
 * 			(both set in camera initialization).
 * 
 * 		*	puts these in a vector for convience, NB: the
 * 			z-coordinate is set to 1 and not -1, as the 42 convention is that
 * 			the camera z-axis is swapped vis-a-vis the world z-axis.
 * 
 * 		*	This vector is now multiplied by the cam2world matrix, aligning it
 * 			withe camera orientation and forming the direction vector. 
 * 			This direction vector is normalized.
 * 
 * @param px 
 * @param x 
 * @param y 
 * @param s 
 */
void	get_ray(t_px *px, int x, int y, t_scene *s)
{
	float	cam_x;
	float	cam_y;
	t_xyz	cam_v3;

	ft_bzero(px, sizeof(t_px));
	px->cam_origin = s->camera->origin;
	cam_x = (2 * (((float)x + 0.5) / s->p_width) - 1) \
						* s->camera->aspect_ratio * s->camera->fov_scale;
	cam_y = (1 - 2 * ((float)y + 0.5) / s->p_height) \
						* s->camera->fov_scale;
	cam_v3 = v_create(cam_x, cam_y, 1);
	m44_multiply_vec3_dir(s->camera->cam2world, cam_v3, \
											&px->direction);
	v_normalizep(&px->direction);
}

/**
 * @brief Check intersection of ray with objects
 * 		*	As the origin and direction of the ray are now known, they can be
 * 			tested against objects.
 * 
 * @param px 
 * @param s 
 * @param hp (float *) hp[0] = hit_distance, hp[1] = hit_height
 */
void	trace_ray(t_px *px, t_scene *s)
{
	float				hp[2];
	static t_hit_test	*hit_test[4] = \
						{test_sphere, test_plane, test_cylinder, test_cone};
	t_list				*objects;
	t_object			*object;

	objects = s->objects;
	while (objects)
	{
		ft_bzero(hp, sizeof(float) * 2);
		object = (t_object *)objects->content;
		if (hit_test[object->id](px, object, hp))
		{
			if (!px->hitobject || px->hit_distance > hp[0])
			{
				px->hitobject = object;
				px->hit_distance = hp[0];
				px->hit_height = hp[1];
			}
		}
		objects = objects->next;
	}
}

void	get_pixel_data(t_px	*px, t_scene *scene, int x, int y)
{
	static t_surface_data	*surface_data[4] = \
	{get_sphere_surface_data, get_plane_surface_data, \
	get_cylinder_surface_data, get_cone_surface_data};

	get_ray(px, x, y, scene);
	trace_ray(px, scene);
	if ((px)->hitobject != NULL)
	{
		surface_data[px->hitobject->id](px->hitobject, px);
		get_uv(px, scene);
		map_texture(px);
		map_procedure(px);
		map_normal(px);
		if (px->hitobject->refl)
			px->color = get_pixel_data_reflection(px, scene);
		loop_lights(scene, px);
	}
}

/**
 * @brief Render image with nr of threads defined in parser.h
 * 
 * @param scene 
 */
void	render_image(t_scene *scene)
{
	t_block		block;

	if (BONUS)
		render_threads(scene);
	else
	{
		block.scene = scene;
		block.y = 0;
		block.y_max = scene->p_height;
		routine(&block);
	}
	draw_image(scene);
}
