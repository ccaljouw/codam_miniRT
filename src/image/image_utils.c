/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccaljouw <ccaljouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:54:35 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/09/26 15:24:25 by ccaljouw         ###   ########.fr       */
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

int	get_text_pxcolor(t_scene *scene, mlx_image_t *text, int x, int y)
{
	int	px;
	int	r;
	int	g;
	int b;
	int a;
	
	px = (((y * scene->p_width) + x) * 4) - 1;
	a = text->pixels[px];
	r = text->pixels[px + 1];
	g = text->pixels[px + 2];
	b = text->pixels[px + 3];
	return ((r << 24) + (g << 16) + (b << 8) + a);
}

void	draw_text(t_scene *scene, mlx_image_t *text)
{
	int	x;
	int	y;
	// int px;
	mlx_texture_t	*temp;
	
	(void)text;
	temp = mlx_load_png("image.png");
	if (!temp)
		printf("error loading texture\n");
	scene->rendering = mlx_texture_to_image(scene->mlx, temp);
	mlx_resize_image(scene->rendering, scene->p_width, scene->p_height);
	// px = 0;
	y = 0;
	while (y < scene->p_height)
	{
		x = 0;
		while (x < scene->p_width)
		{
			// px = (((y * scene->p_width) + x) * 4) - 1;
			// scene->image->pixels[px] = scene->rendering->pixels[px];
			// scene->image->pixels[px + 1] = scene->rendering->pixels[px + 1];
			// scene->image->pixels[px + 2] = scene->rendering->pixels[px + 2];
			// scene->image->pixels[px + 3] = scene->rendering->pixels[px + 3];
			mlx_put_pixel(scene->image, x, y, get_text_pxcolor(scene, scene->rendering, x, y));
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
	t_object				*object;
	static t_surface_data	*surface_data[3] = \
				{get_sphere_surface_data, get_plane_surface_data, get_cylinder_surface_data};

	object = (t_object *)px->hitobject;
	
	if (!object)
		return (0 << 24 | 0 << 16 | 0 << 8 | 255);
	if (scene->selected == px->hitobject)
		px->color = invert_color(px->color);
	else
		px->color = surface_data[object->id](*px->hitobject, px, *scene);
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
