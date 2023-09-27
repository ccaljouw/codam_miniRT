/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:11:39 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/27 00:46:06 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/test.h"


/**
 * @brief The workhorse: Get the ray object. 
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
	ft_bzero(px, sizeof(t_px));
	px->cam_origin = s->camera->origin;
	px->screen_x = x;
	px->screen_y = y;
	px->cam_x = (2 * (((float)x + 0.5) / s->camera->image_width) - 1) \
						* s->camera->aspect_ratio * s->camera->fov_scale;
	px->cam_y = (1 - 2 * ((float)y + 0.5) / s->camera->image_height) \
						* s->camera->fov_scale;
	px->cam_v3 = v_create(px->cam_x, px->cam_y, 1);
	m44_multiply_vec3_dir(s->camera->cam2world, px->cam_v3, \
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
 * @param x 
 * @param y 
 */
void	trace_ray(t_px *px, t_scene *s)
{
	float				hp_distance;
	static t_hit_test	*hit_test[3] = {test_sphere, test_plane, test_cylinder};
	t_list				*objects;
	t_object			*object;

	objects = s->objects;
	while (objects)
	{
		object = (t_object *)objects->content;
		if (hit_test[object->id](*px, *object, &hp_distance))
		{
			if (!px->hitobject || px->hit_distance > hp_distance)
			{
				px->hitobject = object;
				px->hit_distance = hp_distance;
			}
		}
		objects = objects->next;
	}
}

void	get_surface_data(t_px *px)
{
	t_object				*object;
	static t_surface_data	*surface_data[3] = \
	{get_sphere_surface_data, get_plane_surface_data, \
	get_cylinder_surface_data};

	object = (t_object *)px->hitobject;
	px->color = surface_data[object->id](*px->hitobject, px);
}

/**
 * @brief Render image with nr of threads defined in parser.h
 * 
 * @param scene 
 */
void	render_image(t_scene *scene)
{
	pthread_t	*threads;

	threads = malloc(THREADS * sizeof(pthread_t));
	if (!threads)
		exit_error(ERROR_MEM, NULL, scene);
	create_threads(scene, threads);
	join_threads(threads, scene);
}

void	print_ascii(t_px px, t_scene scene)
{
	(void)scene;
	(void)px;
	int						surface_color;
	float					color_ratio;
	static t_surface_data	*surface_data[3] = {get_sphere_surface_data, get_plane_surface_data, get_cylinder_surface_data};

	color_ratio = 0;
	if (px.hitobject)
	{
		surface_color = surface_data[px.hitobject->id](*px.hitobject, &px);
		color_ratio = ((surface_color >> 24) & 0xFF) / (float)255 * 0.299;
		color_ratio += ((surface_color >> 16) & 0xFF) / (float)255 * 0.587;
		color_ratio += ((surface_color >> 8) & 0xFF) / (float)255 * 0.114;
		ft_printf("\e[48;5;%im \e[0m", (int)(232 + color_ratio * 23));
	}
	else
		ft_printf("\e[48;5;232m \e[0m");
}

void	renderAscii(t_scene *scene)
{
	t_px		**pixels;
	t_camera	*cam;
	int		x;
	int		y;
	int		i;

	i = 0;
	cam = scene->camera;
	cam->aspect_ratio = (float)ASCII_WIDTH / ASCII_HEIGHT * 0.6;
	cam->image_width = ASCII_WIDTH;
	cam->image_height = ASCII_HEIGHT;
	pixels = malloc(ASCII_HEIGHT * sizeof(t_px *));
	if (!pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < ASCII_HEIGHT)
	{
		pixels[i] = ft_calloc(ASCII_WIDTH, sizeof(t_px));
		if (!pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
	y = 0;
	while (y < cam->image_height)
	{
		x = 0;
		while (x < cam->image_width)
		{
			get_ray(pixels[y] + x, x, y, scene);
			trace_ray(pixels[y] + x, scene);
			print_ascii(pixels[y][x], *scene);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

