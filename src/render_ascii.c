/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_ascii.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 10:11:39 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/20 11:00:22 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"
#include "../includes/test.h"

/**
 * @brief	Back to those old quadratic math lessons!
 * 			solves x for ax^2 + bx + c (where abc are
 * 			given y the test_sphere function and pasted
 * 			into a vector for Norminette's sake, so
 * 			abc.x = a, abc.y = b, abc.z = c).
 * 			Calculates the discriminant (b^2 - 4ac, remember?)
 * 			if this is below zero, the ray doesn't hit the sphere
 * 			
 * 
 * @param abc abc constants in vector form
 * @param hp1 pointer to first hitpoint
 * @param hp2 pointer to second hitpoint
 * @return int 1 on hit, 0 on no hit
 */
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

/**
 * @brief	Tests if the ray provided hits the sphere provided. Returns
 * 			1 of this is the case, and updates hit_dist to 
 * 
 * @param ray 
 * @param sphere 
 * @param hit_dist 
 * @return int 
 */
int	test_sphere(t_px ray, t_object sphere, float *hit_dist)
{
	float	hit_dist1;
	float	hit_dist2;
	t_xyz	orig_to_center;
	t_xyz	abc;

	hit_dist1 = 0;
	hit_dist2 = 0;
	orig_to_center = v_subtract(ray.cam_origin, sphere.pOrigin);
	abc.x = v_dot(ray.direction, ray.direction);
	abc.y = 2 * v_dot(ray.direction, orig_to_center);
	abc.z = v_dot(orig_to_center, orig_to_center) - sphere.diameter;
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

/**
 * @brief Calculate the normal of the sphere at the hitpoint (ie the vector
		perpendicular to the surface at that point).
		do this by subtracting the sphere center coordinate from the hitpoint
		coordinate (which is in turn calulated by origin + direction * distance)
		the 'facing ratio' (or how directly the ray hits the sphere
		normal) is the dot product of the surface normal at the hitpoint and 
		the direction of the ray.
 * 
 * @param hp_distance 
 * @param s 
 * @param px 
 * @return float 
 */
float	get_sphere_surface_data(t_object sph, t_px px)
{
	t_xyz		surface_normal_at_hitpoint;
	t_xyz		hitpoint;
	float		facing_ratio;

	hitpoint = v_add(px.cam_origin, v_mulitply(px.direction, px.hit_distance));
	surface_normal_at_hitpoint = v_subtract(sph.pOrigin, hitpoint);
	v_normalizep(&surface_normal_at_hitpoint);
	facing_ratio = v_dot(surface_normal_at_hitpoint, px.direction);
	return (facing_ratio);
}

float	get_plane_surface_data(t_object plane, t_px px)
{
	(void)px;
	return (v_dot(v_normalize(plane.vNormal), v_normalize(px.direction)));
}

int	test_plane(t_px ray, t_object plane, float *hit_dist)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;

	denominator = v_dot(plane.vNormal, ray.direction);
	if (denominator > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(ray.cam_origin, plane.pOrigin);
		*hit_dist = v_dot(diff_ray0_plane0, plane.vNormal) / denominator;
		if (*hit_dist >= 0)
			return (1);
	}
	return (0);
}

/**
 * @brief The workhorse. 
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
 * 		*	As the origin and direction of the ray are now known, they can be
 * 			tested against objects.
 * 
 * @param px 
 * @param s 
 * @param x 
 * @param y 
 */
void	trace_ray(t_px *px, t_scene *s, int x, int y)
{
	float					hp_distance;
	static t_hit_test		*hit_test[2] = {test_sphere, test_plane};
	static t_surface_data	*surface_data[2] = {get_sphere_surface_data, get_plane_surface_data};
	t_list					*objects;
	t_object				*object;

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
	if (px->hitobject)
	{
		px->facing_ratio = fabsf(surface_data[px->hitobject->id](*px->hitobject, *px));
		ft_printf("\e[48;5;%im \e[0m", (int)(232 + px->facing_ratio * 23));
	}
	else
		ft_printf("\e[48;5;232m \e[0m");
}

/**
 * @brief Loop over all pictures in the image and calculate
 * 			the rays with trace_ray() (right now this assumes
 * 			one sphere and nothing else)
 * 
 * @param scene 
 * @param px 
 */
void	loop_pixels(t_scene *scene, t_px *px)
{
	int		x;
	int		y;

	y = 0;
	while (y < scene->camera->image_height)
	{
		x = 0;
		while (x < scene->camera->image_width)
		{
			trace_ray(&px[x + y], scene, x, y);
			x++;
		}
		ft_printf("\n");
		y++;
	}
}

void set_ascii_image(t_camera *cam)
{

	cam->aspect_ratio = (float)ASCII_WIDTH / ASCII_HEIGHT * 0.6;
	cam->image_width = ASCII_WIDTH;
	cam->image_height = ASCII_HEIGHT;
}

void	renderAscii(t_scene *scene)
{
	t_px		*pixels;

	set_ascii_image(scene->camera);
	pixels = ft_calloc(ASCII_WIDTH * ASCII_HEIGHT, sizeof(t_px));
	if (pixels == NULL)
		exit_error(ERROR_MEM, NULL, scene);
	loop_pixels(scene, pixels);
}
