/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unique.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:39:58 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/25 01:50:44 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	cameraGeometry(t_scene *scene)
{
	t_camera	*cam;
	t_m44		direction;

	cam = scene->camera;
	if (cam->orientation_v.x == 0 && cam->orientation_v.y == 0 \
		&& cam->orientation_v.z == 0)
		exit_error(ERROR_CAM, "orientation (0,0,0)", scene);
	cam->image_width = scene->p_width;
	cam->image_height = scene->p_height;
	cam->aspect_ratio = (float)scene->p_width / scene->p_height;
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
	|| s->camera->orientation_v.z < -1 || s->camera->orientation_v.z > 1 )
		exit_error(ERROR_CAM, "incorrect orientation [-1, 1]", s);
	s->camera->fov = ft_atoi(param[3]);
	if (s->camera->fov < 0 || s->camera->fov > 180)
		exit_error(ERROR_CAM, "incorrect fov [0, 180]", s);
	if (!s->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, s);
	cameraGeometry(s);
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
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
	t_ambient	*ambient; // added this to keep the lines under 80 chars.

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
	ambient->rgb_ratio[0] = ((float)ambient->rgb[0] / 255) * ambient->ratio;	// calculate ratios here to assure its only done once
	ambient->rgb_ratio[1] = ((float)ambient->rgb[1] / 255) * ambient->ratio;
	ambient->rgb_ratio[2] = ((float)ambient->rgb[2] / 255) * ambient->ratio;
	scene->ambient = ambient;
	ft_putstr_fd("\033[34;1mAmbient lighting config: \033[0m", 1);
}

/**
 * @brief Initialises the light in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_light(char **param, t_scene *s)
{
	int	i;

	if (s->light)
		exit_error(ERROR_SCENE, "redefinition of light", s);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_LIGHT, "incorrect number of arguments", s);
	s->light = malloc(sizeof(t_light));
	if (!s->light)
		exit_error(ERROR_MEM, NULL, s);
	s->light->light_point = set_xyz(param[1], s);
	s->light->brightness = to_float(param[2], s);
	if (s->light->brightness < 0.0 || s->light->brightness > 1.0)
		exit_error(ERROR_LIGHT, "Incorrect brightness values [0.0, 1.0]", s);
	set_rgb(param[3], s->light->rgb, s);
	s->light->l2w = m44_init();
	m44_translate_by_vector(&s->light->l2w, s->light->light_point);
	m44_multiply_vec3(s->light->l2w, v_create(0, 0, 0), &s->light->origin);
	s->light->rgb_ratios = v_create(s->light->rgb[0] / (float)255, \
									s->light->rgb[1] / (float)255, \
									s->light->rgb[2] / (float)255);
	print_vector(s->light->light_point);
	print_vector(s->light->origin);
	ft_putstr_fd("\033[34;1mLight config:\t\t  \033[0m", 1);
}

void	init_resolution(char **param, t_scene *s)
{
	int	i;

	i = 0;
	while (param[i])
		i++;
	if (i != 3)
		exit_error(ERROR_RES, "incorrect number of arguments", s);
	s->p_width = to_float(param[1], s);
	s->p_height = to_float(param[2], s);
	if (s->p_width < 0 || s->p_width > MAX_WIDTH \
						|| s->p_height < 0 || s->p_height > MAX_HEIGHT)
		exit_error(ERROR_RES, "incorrect values \
				[0, MAX_WIDTH / MAX_HEIGHT]", s);
	ft_putstr_fd("\033[34;1mResolution config:\t\t  \033[0m", 1);
}
