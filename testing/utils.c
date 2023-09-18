/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cariencaljouw <cariencaljouw@student.co      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 14:03:11 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/18 22:48:13 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/test.h"

void	print_camera2(t_camera2 cam)
{
	printf("fov\t\tH:%.3f, V:%.3f\n", cam.fov[0], cam.fov[1]);
	printf("image size\twidth:%.3d, height:%.3d\n", cam.image_size[0], cam.image_size[1]);
	printf("image ratio\t%.3f\n", cam.image_ratio);
	printf("canvas ratio\t%.3f\n", cam.canvas_ratio);
	printf("clipping range\t%.3f to %.3f\n", cam.clipping[0], cam.clipping[1]);
	printf("viewpoint\t");
	print_vector(cam.pOrigin);
	printf("Direction\t");
	print_vector(cam.vDirection);
	printf("Canvas center\t");
	print_vector(cam.pCanvas_centre);
	printf("Canvas U\t");
	print_vector(cam.vCanvasU);
	printf("Canvas V\t");
	print_vector(cam.vCanvasV);
	// printf("camera2 to world matrix\n:");
	// m44_print(cam.camera2_to_world);
}

void	print_vector(t_xyz vector)
{
	printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);
}

char	*vtostr(t_xyz vector)
{
	return (ft_msprintf("%.3f,%.3f,%.3f", vector.x, vector.y, vector.z));
}

void	compare(char *result, char *check, int test)
{
	if (!ft_strcmp(result, check))
		printf("\033[32;1mTest %3d:\tOK!\n\033[0m", test);
	else
		printf("\033[31;1mTest %3d:\tKO!\033[0m\n   expected:\t%s\n   result:\t%s\n", test, check, result);
	free(result);
}