/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:51:04 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/18 23:29:20 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"

int	cameratest(int testnr)
{
	t_camera	*cam;
	int			test;
	
	test = testnr;
	printf("\033[34;1m--------------------\033[0m\n");
	printf("\033[34;1m    CAMERA TESTS\033[0m\n");
	printf("\033[34;1m--------------------\033[0m\n");
	cam = malloc(sizeof(t_camera));
	if (!cam)
		exit_error(ERROR_MEM, NULL, NULL);
	cam->view_point = v_create(0.0, 0.0, 0.0);;
	cam->look_at = v_create(0.0, 2.0, 0.0);
	cam->orientation_v = v_create(0.0, 0.0, 1.0);
	cam->plane_dist = 1.0;
	cam->c_width = 1.0;
	cam->c_height = 1.0;
	// cameraGeometry(cam);
	// print_camera(*cam);
	compare(vtostr(cam->screenCentre), "0.000,1.000,0.000", test++);
	compare(vtostr(cam->screenU), "1.000,0.000,0.000", test++);
	compare(vtostr(cam->screenV), "0.000,0.000,1.000", test++);
	free(cam);
	return (test - testnr);
}
