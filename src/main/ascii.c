/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:08:47 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 14:48:31 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Print a pixel as an ascii space with background color. Color
 * 		is converted to grayscale using standard perceived values
 * 		(roughly 15% blue, 30% red and 55% green)
 * 
 * @param px 
 * @param scene 
 */
void	print_ascii(t_px *px, t_scene *scene)
{
	float	color_ratio;

	color_ratio = 0;
	if (px->hitobject)
	{
		px->color = get_color(px, scene);
		color_ratio = ((px->color >> 24) & 0xFF) / (float)255 * ASCII_RED;
		color_ratio += ((px->color >> 16) & 0xFF) / (float)255 * ASCII_GREEN;
		color_ratio += ((px->color >> 8) & 0xFF) / (float)255 * ASCII_BLUE;
		ft_printf("\e[48;5;%im \e[0m", (int)(232 + color_ratio * 23));
	}
	else
		ft_printf("\e[48;5;232m \e[0m");
}

/**
 * @brief Set the scene paramaters right for ascii. Frees the allocated pixel
 * 		data for MLX display, then recreates a new pixel array with ascii
 * 		width and height.
 * 
 * @param scene 
 */
void	set_ascii_params(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->p_height)
		free(scene->pixels[i++]);
	free(scene->pixels);
	i = 0;
	scene->camera->aspect_ratio = (float)ASCII_WIDTH / ASCII_HEIGHT * 0.6;
	// scene->camera->image_width = ASCII_WIDTH;
	// scene->camera->image_height = ASCII_HEIGHT;
	scene->pixels = ft_calloc(ASCII_HEIGHT, sizeof(t_px *));
	scene->p_height = ASCII_HEIGHT;
	scene->p_width = ASCII_WIDTH;
	if (!scene->pixels)
		exit_error(ERROR_MEM, NULL, scene);
	while (i < ASCII_HEIGHT)
	{
		scene->pixels[i] = ft_calloc(ASCII_WIDTH, sizeof(t_px));
		if (!scene->pixels[i])
			exit_error(ERROR_MEM, NULL, scene);
		i++;
	}
}

/**
 * @brief Render the image in ascii
 * 
 * @param scene 
 */
void	render_ascii(t_scene *scene)
{
	int	x;
	int	y;

	set_ascii_params(scene);
	y = 0;
	while (y < scene->p_height)
	{
		x = 0;
		while (x < scene->p_width)
		{
			get_pixel_data(scene->pixels[y] + x, scene, x, y);
			print_ascii(scene->pixels[y] + x, scene);
			x++;
		}
		ft_printf("\n");
		y++;
	}
	exit_error(SUCCESS, NULL, scene);
}
