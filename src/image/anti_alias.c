/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:55:07 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/13 16:02:58 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	get_aa_color(int x, int y, t_scene *s)
{
	int	i;
	int	j;
	int	sum_rgb[3];
	int	cur_rgb;

	i = 0;
	ft_bzero(&sum_rgb, sizeof(int) * 3);
	while (i < s->aa)
	{
		j = 0;
		while (j < s->aa)
		{
			cur_rgb = get_color(s->pixels[y + i] + x + j, s);
			sum_rgb[0] += (cur_rgb >> 24) & 0xFF;
			sum_rgb[1] += (cur_rgb >> 16) & 0xFF;
			sum_rgb[2] += (cur_rgb >> 8) & 0xFF;
			j++;
		}
		i++;
	}
	sum_rgb[0] /= s->aa * s->aa;
	sum_rgb[1] /= s->aa * s->aa;
	sum_rgb[2] /= s->aa * s->aa;
	return (sum_rgb[0] << 24 | sum_rgb[1] << 16 | sum_rgb[2] << 8 | 255);
}

void	draw_aa(t_scene *scene)
{
	int		x;
	int		y;

	y = 0;
	while (y < scene->p_height - scene->aa)
	{
		x = 0;
		while (x < scene->p_width - scene->aa)
		{
			get_aa_color(x, y, scene);
			mlx_put_pixel(scene->image, x / scene->aa, y / scene->aa, \
						get_aa_color(x, y, scene));
			x += scene->aa;
		}
		y += scene->aa;
	}
}
