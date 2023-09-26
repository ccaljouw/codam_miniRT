/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/09/26 19:41:22 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"


void	image_to_window(t_scene *scene)
{
	if (!scene->image)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
	if (mlx_image_to_window(scene->mlx, scene->image, 0, 0) == - 1)
	{
		mlx_close_window(scene->mlx);
		exit_error((char *)mlx_strerror(mlx_errno), NULL, scene);
	}
}

int	get_text_pxcolor(mlx_texture_t *text, float x, float y)
{
	int	px;
	int	text_x;
	int text_y;

	text_x = (int)roundf(x * text->width);
	text_y = (int)roundf(y * text->height);
	px = (((text_y * text->width) + (text_x)) * 4) - 1;
	return ((text->pixels[px + 1] << 24) + (text->pixels[px + 2] << 16) \
				+ (text->pixels[px + 3] << 8) + text->pixels[px]);
}

void	draw_text(t_scene *scene, mlx_texture_t *text)
{
	int	x;
	int	y;
	
	(void)text;
	scene->rendering = mlx_load_png("image.png");
	if (!scene->rendering)
		printf("error loading texture\n");
	y = 0;
	while (y < scene->p_height)
	{
		x = 0;
		while (x < scene->p_width)
		{
			mlx_put_pixel(scene->image, x, y, get_text_pxcolor(scene->rendering, ((float)x / (float)scene->p_width), ((float)y / (float)scene->p_height)));
			x++;
		}
		y++;
	}
}

void	draw_image(t_scene *scene)
{
	int	x;
	int	y;

	y = 0;
	while (y < scene->p_height)
	{
		x = 0;
		while (x < scene->p_width)
		{
			mlx_put_pixel(scene->image, x, y, getColor(&scene->pixels[y][x], scene));
			x++;
		}
		y++;
	}
}

void	select_object(mouse_key_t b, action_t a, modifier_key_t mod, void *param)
{
	t_scene 	*scene;
	int			x;
	int			y;

	(void)mod;
	scene = (t_scene *)param;
	if (b == MLX_MOUSE_BUTTON_LEFT && a == MLX_PRESS)
	{
		mlx_get_mouse_pos(scene->mlx, &x, &y);
		if (scene->selected == scene->pixels[y][x].hitobject)
			scene->selected = NULL;
		else
			scene->selected = scene->pixels[y][x].hitobject;
		draw_image(scene);
	}
}

int	getColor(t_px *px, t_scene *scene)
{
	t_object	*object;
	int			color;

	object = (t_object *)px->hitobject;
	color = ((px->hitobject->rgb[0] << 24) | (px->hitobject->rgb[1] << 16) | (px->hitobject->rgb[2] << 8) | 255);
	// printf("x_screen:%d, y_screen:%d, x_cam:%f, y_cam:%f\n", px->screen_x, px->screen_y, px->cam_x, px->cam_y);
	if (!object)
		return (0 << 24 | 0 << 16 | 0 << 8 | 255);
	if (scene->selected == px->hitobject)
		px->color = invert_color(px->color);
	else
		px->color = ((int)(((color >> 24) & 0xFF) * ft_clamp(0, 1, ((scene->ambient->rgb_ratio[0] * px->facing_ratio) + px->ratios.x * (0.18 / M_PI)))) << 24 \
		| (int)(((color >> 16) & 0xFF) * ft_clamp(0, 1, ((scene->ambient->rgb_ratio[1] * px->facing_ratio) + px->ratios.y * (0.18 / M_PI)))) << 16 \
		| (int)(((color >> 8) & 0xFF) * ft_clamp(0, 1, ((scene->ambient->rgb_ratio[2] * px->facing_ratio) + px->ratios.z * (0.18 / M_PI)))) << 8 \
		| 255);
	return (px->color);
}

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
