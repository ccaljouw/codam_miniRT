#include "includes/miniRT.h"
#include "includes/vector.h"

void	print_vector(t_xyz vector)
{
	printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);
}

int	test_plane(t_px ray, t_object plane, float *hit_dist)
{
	float	denominator;
	t_xyz	diff_ray0_plane0;
	// static int	flag = 0;
	
	// v_normalizep(&plane.vNormal);
	denominator = v_dot(plane.vNormal, ray.direction);
	printf("denom %.10f", denominator);
	if (fabsf(denominator) > EPSILON)
	{
		diff_ray0_plane0 = v_subtract(plane.pOrigin, ray.cam_origin);
		*hit_dist = v_dot(plane.vNormal, diff_ray0_plane0) / denominator;
		// if (!flag){
			ft_printf("\n\nPRINTOUT: %i, %i\n\n", ray.screen_x, ray.screen_y);
			ft_printf("plane normal: ");
			print_vector(plane.vNormal);
			ft_printf("plane pt: ");
			print_vector(plane.pOrigin);
			ft_printf("ray dir: ");
			print_vector(ray.direction);
			ft_printf("ray origin: ");
			print_vector(ray.cam_origin);
			ft_printf("hd %f \n\n", *hit_dist);
			// flag = 1;
		// }
		// if(*hit_dist > 0)
		// 	ft_printf("hd %f \n\n", *hit_dist);
		if (*hit_dist > 0)
		{
			return (1);
		}
	}
	return (0);
}

int main(void)
{
	t_px ray;
	t_object plane;
	float	hit_dist;

	plane.vNormal = v_create(0, 1, 0);
	plane.pOrigin = v_create(0, 0, 0);
	ray.direction = v_create(6.9, -4.7, -6.79);
	ray.cam_origin = v_create(5.09, 11.71, -3.2);
	test_plane(ray, plane, &hit_dist);
}
