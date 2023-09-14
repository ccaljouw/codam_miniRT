/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 11:23:58 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/14 20:13:09 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"

void	set_camera(t_camera *cam)
{
	// cam->viewpoint read from file;
	cam->look_at = v_create(0.0, 0.0, 0.0);
	// cam->orientation_v read from file
	cam->plane_dist = 1;
	cam->c_width = 0.25; //change
	cam->c_height = (16.0/9.0); //change
	
}

/**
 * @brief 
 * 1. compute vector form camera to lookAt position (principal axis)
 * 2. compute U and V vectors (vectors on the screen paralel to 
 * x and y of camera position)
 * 3. comput the centre of the screen
 * 4. modify the U and V vectors to match the size of the screen
 * 
 * @param cam (t_camera)
 */
void	cameraGeometry(t_camera *cam)
{
	cam->principal_axis = v_subtract(cam->look_at, cam->view_point);
	v_normalize(&cam->principal_axis);
	
	cam->screenU = v_cross(cam->principal_axis, cam->orientation_v);
	v_normalize(&cam->screenU);
	cam->screenV = v_cross(cam->screenU, cam->principal_axis);
	v_normalize(&cam->screenV);
	
	cam->screenCentre = v_add(cam->view_point, v_mulitply(cam->principal_axis, cam->plane_dist));

	cam->screenU = v_mulitply(cam->screenU, cam->c_width);
	cam->screenV = v_mulitply(cam->screenV, cam->c_height);
}

/**
 * @brief Initialises the camera in the scene.
 * Only one object of this type can be present in the scene.
 * @param param (char **) tab separated string input.
 * @param scene (t_scene) passed to clean up when input is invallid.
 */
void	init_camera(char **param, t_scene *scene)
{
	int	i;

	if (scene->camera)
		exit_error(ERROR_SCENE, "redefinition of camera", scene);
	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_SPHERE, "incorrect number of arguments", scene);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		exit_error(ERROR_MEM, NULL, scene);
	scene->camera->view_point = set_xyz(param[1], scene);
	scene->camera->orientation_v = set_xyz(param[2], scene);
	scene->camera->fov = ft_atoi(param[3]);
	if (!scene->camera->fov && !ft_strcmp(param[3], "0"))
		exit_error("incorrect fov", NULL, scene);
	scene->camera->look_at = v_create(0.0, 0.0, 0.0);
	scene->camera->plane_dist = 1; //change?
	scene->camera->c_width = 0.25; //change?
	scene->camera->c_height = 0.25; //change?
	cameraGeometry(scene->camera);
	print_camera(*(scene->camera)); //testing
	ft_putstr_fd("\033[34;1mCamera config:\t\t  \033[0m", 1);
}
