/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   camera2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 15:51:04 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/17 18:03:05 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"
# include "../includes/miniRT.h"

int	camera2test(int testnr)
{
	t_camera2	*cam;
	t_scene		*scene;
	int			test;
	
	test = testnr;
	printf("\033[34;1m--------------------\033[0m\n");
	printf("\033[34;1m    camera2 TESTS\033[0m\n");
	printf("\033[34;1m--------------------\033[0m\n");
	cam = malloc(sizeof(t_camera2));
	if (!cam)
		exit_error(ERROR_MEM, NULL, NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		exit_error(ERROR_MEM, NULL, NULL);
	scene->mlx = mlx_init(WIDTH, HEIGHT, "RAY'S TRACERS", true);
	if (!scene->mlx)
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	scene->image = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	if (!scene->image)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == -1)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	scene->camera2 = cam;
	// 
	cam->pOrigin = v_create(0.0, 0.0, 0.0);
	cam->vDirection = v_create(0.0, 0.0, 1.0);
	cam->fov[0] = 170;
	cam->fov[1] = cam->fov[0]; //change
	update_camera2(scene);
	print_camera2(*cam);
	compare(vtostr(cam->pCanvas_centre), "0.000,1.000,0.000", test++);
	compare(vtostr(cam->vCanvasU), "1.000,0.000,0.000", test++);
	compare(vtostr(cam->vCanvasV), "0.000,0.000,1.000", test++);
	free(cam);
	free(scene);
	return (test - testnr);
}
