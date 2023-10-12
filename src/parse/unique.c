/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:39:58 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/12 15:48:50 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	camera_geo(t_scene *scene)
{
	t_camera	*cam;
	t_m44		direction;

	cam = scene->camera;
	if (cam->orientation_v.x == 0 && cam->orientation_v.y == 0 \
		&& cam->orientation_v.z == 0)
		exit_error(ERROR_CAM, "orientation (0,0,0)", scene);
	cam->aspect_ratio = (float)scene->file_width / scene->file_height;
	cam->fov_scale = tan(ft_rad(cam->fov * 0.5));
	cam->cam2world = m44_init();
	m44_translate_by_vector(&cam->cam2world, cam->view_point);
	direction = m44_from_direction_vector(cam->orientation_v);
	cam->cam2world = m44_dot_product(direction, cam->cam2world);
	m44_multiply_vec3(cam->cam2world, v_create(0, 0, 0), &cam->origin);
	cam->fov_scale = tan(ft_rad(cam->fov * 0.5));
}

void	init_camera(char **param, t_scene *s)
{
	int	i;

	if (s->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", s);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", s);
	s->camera = malloc(sizeof(t_camera));
	if (!s->camera)
		exit_error(ERROR_MEM, NULL, s);
	s->camera->view_point = set_xyz(param[1], s);
	s->camera->orientation_v = set_xyz(param[2], s);
	if (s->camera->orientation_v.x < -1 || s->camera->orientation_v.x > 1 \
	|| s->camera->orientation_v.y < -1 || s->camera->orientation_v.y > 1 \
	|| s->camera->orientation_v.z < -1 || s->camera->orientation_v.z > 1)
		exit_error(ERROR_CAM, "incorrect orientation [-1, 1]", s);
	s->camera->fov = ft_atoi(param[3]);
	if (s->camera->fov < 0 || s->camera->fov > 180)
		exit_error(ERROR_CAM, "incorrect fov [0, 180]", s);
	if (!s->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, s);
	camera_geo(s);
	ft_putstr_fd("\033[34;1mCamera config:\t\t\033[0m", 1);
}

/**
 * @brief Initialises ambient lighting in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_ambient(char **param, t_scene *scene)
{
	int			i;
	t_ambient	*ambient;

	if (scene->ambient)
		exit_error(ERROR_SCENE, "redefinition of ambient lighting", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	ambient = malloc(sizeof(t_ambient));
	if (!ambient)
		exit_error(ERROR_MEM, NULL, scene);
	ambient->ratio = to_float(param[1], scene);
	if (ambient->ratio < 0.0 || ambient->ratio > 1)
		exit_error(ERROR_AMB, "incorrect lighting ratio [0.0, 1.0]", scene);
	set_rgb(param[2], ambient->rgb, scene);
	ambient->rgb_ratio[0] = ((float)ambient->rgb[0] / 255) * ambient->ratio;
	ambient->rgb_ratio[1] = ((float)ambient->rgb[1] / 255) * ambient->ratio;
	ambient->rgb_ratio[2] = ((float)ambient->rgb[2] / 255) * ambient->ratio;
	scene->ambient = ambient;
	ft_putstr_fd("\033[34;1mAmbient light config:\t\033[0m", 1);
}

void	init_resolution(char **param, t_scene *s)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RES, "incorrect number of arguments", s);
	s->file_width = to_float(param[1], s);
	s->file_height = to_float(param[2], s);
	if (s->file_width < 0 || s->file_width > MAX_WIDTH \
						|| s->file_height < 0 || s->file_height > MAX_HEIGHT)
		exit_error(ERROR_RES, "incorrect values \
				[0, MAX_WIDTH / MAX_HEIGHT]", s);
	s->p_height = s->file_height + AA * (AA_SAMPLES - 1) * s->file_height;
	s->p_width = s->file_width + AA * (AA_SAMPLES - 1) * s->file_width;
	ft_putstr_fd("\033[34;1mResolution config:\t\t\033[0m", 1);
}
