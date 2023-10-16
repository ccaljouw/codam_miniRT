/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:07:30 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 14:25:19 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * @brief Print a vector and add a one tab, or two if the vector printout is
 * 		shorter than 21 characters to [fd].
 * 
 * @param v 
 * @param fd 
 */
void	p_v(t_xyz v, int fd)
{
	int	chars;

	chars = ft_dprintf(fd, "%.3f,%.3f,%.3f\t", v.x, v.y, v.z);
	if (chars < 21)
		ft_dprintf(fd, "\t");
}

/**
 * @brief Print an array of three ints, separated by commas to [fd]
 * 
 * @param rgb 
 * @param fd 
 */
void	p_rgb(int rgb[3], int fd)
{
	ft_dprintf(fd, "%i,%i,%i\n", rgb[0], rgb[1], rgb[2]);
}

/**
 * @brief Loop through the texture array and return the id of
 * 		the [text] pointer in that array.
 * 
 * @param s 
 * @param text 
 * @return int 
 */
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

void	p(int fd, char *s)
{
	ft_dprintf(fd, s);
}
