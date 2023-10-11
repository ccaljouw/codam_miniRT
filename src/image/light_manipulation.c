/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_manipulation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:14:20 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/11 16:23:19 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	adjust_light_brightness(mlx_key_data_t keydata, t_light *light)
{
	if (keydata.key == ZOOM_IN)
		light->brightness += 0.1;
	if (keydata.key == ZOOM_OUT)
		light->brightness -= 0.1;
	light->rgb_ratios = v_create(light->rgb[0] / (float)255, \
	light->rgb[1] / (float)255, light->rgb[2] / (float)255);
	light->rgb_ratios = v_multiply(light->rgb_ratios, light->brightness);
	ft_printf("new brightness: %f\n", light->brightness);
}

void	adjust_ambient(t_scene *scene, mlx_key_data_t key_data)
{
	t_ambient	*a;

	a = scene->ambient;
	if (key_data.key == MLX_KEY_MINUS)
		a->ratio -= .05;
	if (key_data.key == MLX_KEY_EQUAL)
		a->ratio += .05;
	a->rgb_ratio[0] = ((float)a->rgb[0] / 255) * a->ratio;
	a->rgb_ratio[1] = ((float)a->rgb[1] / 255) * a->ratio;
	a->rgb_ratio[2] = ((float)a->rgb[2] / 255) * a->ratio;
	ft_printf("ambient brightness: %f\n", a->ratio);
	render_image(scene);
}
