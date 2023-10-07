/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/07 13:33:29 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

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
	float	cam_x;
	float	cam_y;
	t_xyz	cam_v3;
	
	ft_bzero(px, sizeof(t_px));
	px->cam_origin = s->camera->origin;
	cam_x = (2 * (((float)x + 0.5) / s->camera->image_width) - 1) \
						* s->camera->aspect_ratio * s->camera->fov_scale;
	cam_y = (1 - 2 * ((float)y + 0.5) / s->camera->image_height) \
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
		if (hit_test[object->id](px, *object, hp))
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

void	get_surface_data(t_px *px)
{
	t_object				*object;
	static t_surface_data	*surface_data[4] = \
	{get_sphere_surface_data, get_plane_surface_data, \
	get_cylinder_surface_data, get_cone_surface_data};

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
	t_block		*blocks;

	threads = malloc(THREADS * sizeof(pthread_t));
	blocks = malloc(THREADS * sizeof(t_block));
	if (!threads || !blocks)
		exit_error(ERROR_MEM, NULL, scene);
	calculate_angles(scene);
	create_threads(scene, threads, blocks);
	join_threads(threads, scene);
	free(blocks);
	free(threads);
}

void	print_ascii(t_px *px, t_scene *scene)
{
	float	color_ratio;

	color_ratio = 0;
	if (px->hitobject)
	{
		px->color = get_color(px, scene);
		color_ratio = ((px->color >> 24) & 0xFF) / (float)255 * 0.299;
		color_ratio += ((px->color >> 16) & 0xFF) / (float)255 * 0.587;
		color_ratio += ((px->color >> 8) & 0xFF) / (float)255 * 0.114;
		ft_printf("\e[48;5;%im \e[0m", (int)(232 + color_ratio * 23));
	}
	else
		ft_printf("\e[48;5;232m \e[0m");
}

void	set_ascii_params(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->p_height)
		free(scene->pixels[i++]);
	free(scene->pixels);
	i = 0;
	scene->camera->aspect_ratio = (float)ASCII_WIDTH / ASCII_HEIGHT * 0.6;
	scene->camera->image_width = ASCII_WIDTH;
	scene->camera->image_height = ASCII_HEIGHT;
	scene->pixels = ft_calloc(ASCII_HEIGHT, sizeof(t_px *));
	scene->p_height = ASCII_HEIGHT;
	scene->p_width = ASCII_WIDTH;
	if (!scene->pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < ASCII_HEIGHT)
	{
		scene->pixels[i] = ft_calloc(ASCII_WIDTH, sizeof(t_px));
		if (!scene->pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
}

void	renderAscii(t_scene *scene)
{
	int	x;
	int	y;

	set_ascii_params(scene);
	y = 0;
	while (y < scene->camera->image_height)
	{
		x = 0;
		while (x < scene->camera->image_width)
		{
			get_ray(scene->pixels[y] + x, x, y, scene);
			trace_ray(scene->pixels[y] + x, scene);
			if ((scene->pixels[y] + x)->hitobject != NULL)
			{
				get_surface_data(scene->pixels[y] + x);
				map_normal(scene->pixels[y] + x);
				loop_lights(scene, scene->pixels[y] + x);
			}
			print_ascii(scene->pixels[y] + x, scene);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	exit_error(SUCCESS, NULL, scene);
}
