/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anti_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 15:55:07 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 15:55:37 by albertvanan      ###   ########.fr       */
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
	while (i < AA_SAMPLES)
	{
		j = 0;
		while (j < AA_SAMPLES)
		{
			cur_rgb = get_color(s->pixels[y + i] + x + j, s);
			sum_rgb[0] += (cur_rgb >> 24) & 0xFF;
			sum_rgb[1] += (cur_rgb >> 16) & 0xFF;
			sum_rgb[2] += (cur_rgb >> 8) & 0xFF;
			j++;
		}
		i++;
	}
	sum_rgb[0] /= AA_SAMPLES * AA_SAMPLES;
	sum_rgb[1] /= AA_SAMPLES * AA_SAMPLES;
	sum_rgb[2] /= AA_SAMPLES * AA_SAMPLES;
	return (sum_rgb[0] << 24 | sum_rgb[1] << 16 | sum_rgb[2] << 8 | 255);
}

void	draw_aa(t_scene *scene)
{
	int		x;
	int		y;

	y = 0;
	while (y < scene->p_height - AA_SAMPLES)
	{
		x = 0;
		while (x < scene->p_width - AA_SAMPLES)
		{
			get_aa_color(x, y, scene);
			mlx_put_pixel(scene->image, x / AA_SAMPLES, y / AA_SAMPLES, \
						get_aa_color(x, y, scene));
			x += AA_SAMPLES;
		}
		y += AA_SAMPLES;
	}
}
