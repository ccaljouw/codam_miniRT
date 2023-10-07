/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   image_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/23 08:54:35 by cariencaljo   #+#    #+#                 */
/*   Updated: 2023/10/07 13:53:46 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>


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

void	get_text_pxcolor(t_px *pix)
{
	int				px;
	int				text_x;
	int 			text_y;
	mlx_texture_t 	*text;

	if (!pix->hitobject)
		return ;
	if (!pix->hitobject->text)
	{
		pix->color = (pix->hitobject->rgb[0] << 24 | pix->hitobject->rgb[1] << 16 | pix->hitobject->rgb[2] << 8 | 255);
		return ;
	}
	text = pix->hitobject->text;
	text_x = floor(pix->uv.x * (float)text->width);
	text_y = floor(pix->uv.y * (float)text->height);
	if (text_y == 0 && text_x == 0)
		px = 0;
	else
		px = (((text_y * text->width) + (text_x)) * 4) - 1;
	pix->color = (text->pixels[px + 1] << 24) + (text->pixels[px + 2] << 16) \
				+ (text->pixels[px + 3] << 8) + text->pixels[px];
	return ;
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
			// get_color(scene->pixels[y] + x, scene);	
			mlx_put_pixel(scene->image, x, y, get_color(scene->pixels[y] + x, scene));
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
		// draw_image(scene);
		render_image(scene);
	}
}

int	get_color(t_px *px, t_scene *scene)
{
	int	rgb[3];
	
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
	px->color = rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 255;
	if (px->hitobject && scene->selected == px->hitobject)
		px->color = invert_color(px->color);
	scene->min_x = (px->uv.x < scene->min_x ? px->uv.x : scene->min_x); // for testing
	scene->max_x = (px->uv.x > scene->max_x ? px->uv.x : scene->max_x);  // for testing
	scene->min_y = (px->uv.y < scene->min_y ? px->uv.y : scene->min_y); // for testing
	scene->max_y = (px->uv.y > scene->max_y ? px->uv.y : scene->max_y); // for testing
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
