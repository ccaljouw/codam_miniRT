/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:07:30 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/11 16:08:07 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	p_v(t_xyz v, int fd)
{
	int	chars;

	chars = ft_dprintf(fd, "%.3f,%.3f,%.3f\t", v.x, v.y, v.z);
	if (chars < 21)
		ft_dprintf(fd, "\t");
}

void	p_rgb(int rgb[3], int fd)
{
	ft_dprintf(fd, "%i,%i,%i\n", rgb[0], rgb[1], rgb[2]);
}

int	get_texture_id(t_scene *s, mlx_texture_t *text)
{
	int	i;

	i = NR_TEXTURES - 1;
	while (i > -1)
	{
		if (text == s->textures[i])
			break ;
		i--;
	}
	if (i == -1)
		return (0);
	return (i + 1);
}
