/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/19 23:25:10 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	image_to_window(t_scene *scene, mlx_image_t *image)
{
	if (!image)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	if (mlx_image_to_window(scene->mlx, image, 0, 0) == -1)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
}

int	get_text_pxcolor(mlx_texture_t *text, t_xyz uv)
{
	int				px;
	int				text_x;
	int				text_y;
	int				color;

	text_x = floor(uv.x * (float)text->width);
	text_y = floor(uv.y * (float)text->height);
	if (text_y == 0 && text_x == 0)
		px = 0;
	else
		px = (((text_y * text->width) + (text_x)) * 4) - 1;
	color = (text->pixels[px + 1] << 24) + (text->pixels[px + 2] << 16) \
				+ (text->pixels[px + 3] << 8) + text->pixels[px];
	return (color);
}

void	draw_image(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	if (scene->aa > 1)
	{
		draw_aa(scene);
	}
	else
	{
		while (y < scene->p_height)
		{
			x = 0;
			while (x < scene->p_width)
			{
				mlx_put_pixel(scene->image, x, y, \
						get_color(scene->pixels[y] + x, scene));
				x++;
			}
			y++;
		}
	}
}

// void	draw_black(t_scene *scene)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	if (scene->aa > 1)
// 	{
// 		draw_aa(scene);
// 	}
// 	else
// 	{
// 		while (y < scene->p_height)
// 		{
// 			x = 0;
// 			while (x < scene->p_width)
// 			{
// 				mlx_put_pixel(scene->render_image, x, y, 255);
// 				x++;
// 			}
// 			y++;
// 		}
// 	}
// }

/**
 * @brief Calculate the color of a pixel:
 * 	-	get the ambient color by multiplying the rgb color of the object
 * 		with the facing ratio of the ray
 * 	-	add the specular reflection which is the specular ratio multiplied
 * 		rgb white
 * 
 * @param px 
 * @param scene 
 * @return int 
 */
int	get_color(t_px *px, t_scene *scene)
{
	int	rgb[3];
	int	color;

	if (!px->hitobject)
		return (px->color = 0 << 24 | 0 << 16 | 0 << 8 | 255);
	rgb[0] = (int)(((px->color >> 24) & 0xFF) * \
		ft_clamp(0, 1, ((scene->ambient->rgb_ratio[0] * px->facing_ratio) \
		+ px->diffuse.x)));
	rgb[1] = (int)(((px->color >> 16) & 0xFF) * \
		ft_clamp(0, 1, ((scene->ambient->rgb_ratio[1] * px->facing_ratio) \
		+ px->diffuse.y)));
	rgb[2] = (int)(((px->color >> 8) & 0xFF) * \
		ft_clamp(0, 1, ((scene->ambient->rgb_ratio[2] * px->facing_ratio) \
		+ px->diffuse.z)));
	rgb[0] = ft_clamp(0, 255, rgb[0] + 255 * px->specular.x);
	rgb[1] = ft_clamp(0, 255, rgb[1] + 255 * px->specular.y);
	rgb[2] = ft_clamp(0, 255, rgb[2] + 255 * px->specular.z);
	color = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	if (px->hitobject && scene->selected == px->hitobject)
		color = invert_color(color);
	if (px->rfr_color)
		color = blend_color(px->rfr_color, color, px->hitobject->transp);
	if (px->refl_color)
		color = blend_color(px->refl_color, color, px->hitobject->refl);
	return (color);
}

/**
 * @brief Turn a color into its inverse.
 * 
 * @param color 
 * @return int 
 */
int	invert_color(int color)
{
	int	r;
	int	g;
	int	b;

	r = 255 - ((color >> 24) & 0xFF);
	g = 255 - ((color >> 16) & 0xFF);
	b = 255 - ((color >> 8) & 0xFF);
	return (r << 24 | g << 16 | b << 8 | 255 >> 1);
}
