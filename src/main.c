/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 10:11:39 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/18 00:17:37 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include <fcntl.h>
#include "../includes/test.h"

/**
 * @brief checks that there are 2 arguments provided 
 * and that argv[1] has an .rt extension
 * @param argc 
 * @param argv 
 */
void	check_args(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 2)
		exit_error(ERROR_ARGS, NULL, NULL);
	while (argv[1][i] != '\0')
		i++;
	if (ft_strncmp(argv[1] + (i - 3), ".rt", 4) != 0)
		exit_error(ERROR_PATH, NULL, NULL);
}

/**
 * @brief initiates the scene based on the file contents
 * 
 * @param file (char **) input file with .rt extension
 * @return t_scene* 
 */
t_scene	*init_scene(char *file)
{
	t_scene	*scene;
	char	*line;
	int		fd;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL, NULL);
	ft_memset(scene, 0, sizeof(t_scene));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error(ERROR_PATH, NULL, NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line) // close fd if error in line
			parse_type(line, scene);
		else // what if error in gnl?
			break ;
	}
	close(fd);
	// if (!scene->ambient || !scene->camera)
	// 	exit_error(ERROR_SCENE, "not all required elements provided", scene);
	ft_putendl_fd("\033[32;1m\nScene set up\n\033[0m", 2);
	return (scene);
}


typedef struct s_pixel
{
	int		screen_x;
	int		screen_y;
	float	cam_x;
	float	cam_y;
	t_xyz	cam_v3;
	t_xyz	cam_origin;
	t_xyz	direction;
}	t_px;

int	get_parabolic_hitpoints(t_xyz abc, float *hp1, float *hp2)
{
	float	discriminant;
	float	quotient;

	discriminant = abc.y * abc.y - 4 * abc.x * abc.z;
	if (discriminant < 0)
		return (0);
	if (discriminant == 0)
		return (*hp1 = -0.5 * abc.y / abc.x, *hp2 = *hp1, 1);
	if (abc.y > 0)
		quotient = -0.5 * (abc.y + sqrt(discriminant));
	else
		quotient = -0.5 * (abc.y - sqrt(discriminant));
	*hp1 = quotient / abc.x;
	*hp2 = abc.z / quotient;
	if (*hp1 > *hp2)
		swap_floats(hp1, hp2);
	return (1);
}

int	test_sphere(t_px ray, t_sphere sphere, float *hit_dist)
{
	float	hit_dist1;
	float	hit_dist2;
	t_xyz	orig_to_center;
	t_xyz	abc;

	// 	sph = (t_sphere *)scene->spheres->content;
		// ft_printf("Sphere: ");
		// print_vector(sphere.pC);
		// ft_printf("radius: %f", sphere.radius);
		// ft_printf("diameter: %f", sphere.diameter);
		// ft_printf("color: %i:%i:%i", sphere.rgb[0], sphere.rgb[1], sphere.rgb[2]);

	hit_dist1 = 0;
	hit_dist2 = 0;
	orig_to_center = v_subtract(ray.cam_origin, sphere.pC);
	abc.x = v_dot(ray.direction, ray.direction);
	// ft_printf("a: %f\n", abc.x);
	abc.y = 2 * v_dot(ray.direction, orig_to_center);
	abc.z = v_dot(orig_to_center, orig_to_center) - sphere.diameter;
	// ft_printf("c: %f\n", abc.z);
	if (!get_parabolic_hitpoints(abc, &hit_dist1, &hit_dist2))
		return (0);
	if (hit_dist1 < 0)
	{
		hit_dist1 = hit_dist2;
		if (hit_dist1 < 0)
			return (0);
	}
	return (*hit_dist = hit_dist1, 1);
}

void	loop_pixels(t_scene *scene, t_camera *cam, t_px *px)
{
	int		x;
	int		y;
	float	hd;

	y = 0;
	while (y < cam->image_height)
	{
		x = 0;
		while (x < cam->image_width)
		{
			px[x + y].screen_x = x;
			px[x + y].screen_y = y;
			px[x + y].cam_x = (2 * (((float)x + 0.5) / cam->image_width) - 1) \
										* cam->aspect_ratio * cam->fov_scale;
			px[x + y].cam_y = (1 - 2 * ((float)y + 0.5) / cam->image_height) \
										* cam->fov_scale;
			px[x + y].cam_v3 = v_create(px[x + y].cam_x, px[x + y].cam_y, 1);
			m44_multiply_vec3_dir(cam->cam2world, px[x + y].cam_v3, \
													&px[x + y].direction);
			px[x + y].cam_origin = cam->origin;
			v_normalizep(&px[x + y].direction);
			if (test_sphere(px[x + y], *((t_sphere *)scene->spheres->content), &hd))
				ft_printf("o");
			else
				ft_printf(".");
			// ft_printf("%3i %3i: \n", x, y);
			// print_vector(px[x + y].cam_v3);
			// print_vector(px[x + y].direction);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

t_m44	m44_from_direction_vector(t_xyz direction)
{
	t_xyz	x_axis;
	t_xyz	y_axis;
	t_m44	matrix;

	matrix = m44_init();
	x_axis = v_normalize(v_cross(v_create(0, 1, 0), direction));
	y_axis = v_normalize(v_cross(direction, x_axis));
	matrix.arr[0][0] = x_axis.x;
	matrix.arr[0][1] = y_axis.x;
	matrix.arr[0][2] = direction.x;
	matrix.arr[1][0] = x_axis.y;
	matrix.arr[1][1] = y_axis.y;
	matrix.arr[1][2] = direction.y;
	matrix.arr[2][0] = x_axis.z;
	matrix.arr[2][1] = y_axis.z;
	matrix.arr[2][2] = direction.z;
	return (matrix);
}

int	main(int argc, char **argv)
{
	t_scene		*scene;
	t_sphere	*sph;
	t_px		*pixels;
	t_m44		direction;

	check_args(argc, argv);
	scene = init_scene(argv[1]);
	scene->mlx = mlx_init(WIDTH, HEIGHT, "RAY'S TRACERS", true);
	if (!scene->mlx)
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->camera->aspect_ratio = (float)WIDTH / HEIGHT;
	scene->camera->image_width = WIDTH;
	scene->camera->image_height = HEIGHT;
	scene->camera->cam2world = m44_init();
	m44_translate(&scene->camera->cam2world, scene->camera->view_point.x, scene->camera->view_point.y, scene->camera->view_point.z);
	direction = m44_from_direction_vector(scene->camera->orientation_v);
	m44_invert(direction, &direction);
	scene->camera->cam2world = m44_dot_product(direction, scene->camera->cam2world);
	// m44_print(scene->camera->cam2world);
	// m44_invert(scene->camera->cam2world, &scene->camera->cam2world);
	m44_multiply_vec3(scene->camera->cam2world, v_create(0, 0, 0), &scene->camera->origin);
	scene->camera->fov_scale = tan(ft_rad(scene->camera->fov * 0.5));
	print_camera(*scene->camera);
	pixels = ft_calloc(WIDTH * HEIGHT, sizeof(t_px));
	if (pixels == NULL)
		exit_error(ERROR_MEM, NULL, scene);
	if (scene->spheres)
	{
		sph = (t_sphere *)scene->spheres->content;
		ft_printf("Sphere: ");
		print_vector(sph->pC);
		ft_printf("radius: %f", sph->radius);
		ft_printf("diameter: %f", sph->diameter);
		ft_printf("color: %i:%i:%i\n", sph->rgb[0], sph->rgb[1], sph->rgb[2]);
	}
	loop_pixels(scene, scene->camera, pixels);
	
	// render_sphere(scene, scene->spheres->content);
	// if (!scene->image)
	// {
	// 	mlx_close_window(scene->mlx);
	// 	exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	// }
	// if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == -1)
	// {
	// 	mlx_close_window(scene->mlx);
	// 	exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	// }
	// // mlx_loop_hook(scene->mlx, render_sphere, scene);
	// mlx_loop(scene->mlx);
	// mlx_terminate(scene->mlx);
	// cleanup scene
	return (0);
}
