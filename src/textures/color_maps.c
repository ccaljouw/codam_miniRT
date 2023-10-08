/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 15:11:27 by cariencaljo       #+#    #+#             */
/*   Updated: 2023/10/09 00:00:58 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	get_position_range(int *st_range, int nr_pos, float pos, t_stop *stops)
{
	int		i;
	float	diff;
	float	t;

	i = 0;
	diff = 2;
	while (i < nr_pos)
	{
		t = stops[i].pos - pos;
		if (fabs(t) < diff)
		{
			diff = fabs(t);
			st_range[0] = i;
			if (t < 0.0)
				st_range[1] = ft_min((nr_pos - 1), (i + 1));
			else if (t > 0.0)
				st_range[1] = ft_max((i - 1), 0);
			else
				st_range[1] = i;
		}
		i++;
	}
}

t_xyz	get_rgb_fact(float pos, int *stop_range, t_stop *stops)
{
	float	x1;
	float	x2;
	int		t;
	t_xyz	rgb_fact;
	t_xyz	temp;

	if (stop_range[0] == stop_range[1])
		return (stops[stop_range[0]].rgb_fact);
	if (stop_range[0] > stop_range[1])
	{
		t = stop_range[0];
		stop_range[0] = stop_range[1];
		stop_range[1] = t; 
	}
	x1 = stops[stop_range[0]].pos;
	x2 = stops[stop_range[1]].pos;
	temp = v_subtract(stops[stop_range[1]].rgb_fact,
			stops[stop_range[0]].rgb_fact);
	temp = v_divide(temp, x2 - x1);
	temp = v_multiply(temp, pos - x1);
	rgb_fact = v_add(stops[stop_range[0]].rgb_fact, temp);
	return (rgb_fact);
}

t_xyz	color_map_5s(float pos)
{
	int		stop_range[2];
	t_stop	stops[5];
	t_xyz	fact;

	stops[0].pos = 0;
	stops[1].pos = 0.25;
	stops[2].pos = 0.5;
	stops[3].pos = 0.75;
	stops[4].pos = 1;
	stops[0].rgb_fact = v_create(1, 0, 0);
	stops[1].rgb_fact = v_create(1, 0.5, 0);
	stops[2].rgb_fact = v_create(1, 1, 0);
	stops[3].rgb_fact = v_create(0, 1, 0.5);
	stops[4].rgb_fact = v_create(0, 0, 1);
	get_position_range(stop_range, 5, pos, stops);
	fact = get_rgb_fact(pos, stop_range, stops);
	return (fact);
}
