/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:55:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/12 00:25:08 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	set_light_params(t_light *nw_lite, t_scene *s, char **param)
{
	nw_lite->origin = set_xyz(param[1], s);
	nw_lite->brightness = to_float(param[2], s);
	if (nw_lite->brightness < 0.0 || nw_lite->brightness > 1.0)
		exit_error(ERROR_LIGHT, "Incorrect brightness values [0.0, 1.0]", s);
	nw_lite->rgb_ratios = v_create(nw_lite->rgb[0] / (float)255, \
		nw_lite->rgb[1] / (float)255, nw_lite->rgb[2] / (float)255);
	nw_lite->rgb_ratios = v_multiply(nw_lite->rgb_ratios, nw_lite->brightness);
}

void	init_lights(char **param, t_scene *s)
{
	t_list		*new_node;
	t_light		*nw_lite;
	int			i;

	i = 0;
	if (param[0][0] == 'l' && !BONUS)
		exit_error(ERROR_LIGHT, L_IN_MANDATORY, s);
	if (param[0][0] == 'L')
		s->single_light = true;
	if (ft_lstsize(s->lights) > 0 && s->single_light)
		exit_error(ERROR_LIGHT, L_MULTIPLE, s);
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_LIGHT, "incorrect number of arguments", s);
	new_node = ft_lstnew(NULL);
	nw_lite = malloc(sizeof(t_light));
	if (!nw_lite || !new_node)
		exit_error(ERROR_MEM, NULL, s);
	set_rgb(param[3], nw_lite->rgb, s);
	set_light_params(nw_lite, s, param);
	new_node->content = (void *)nw_lite;
	ft_lstadd_back(&s->lights, new_node);
	ft_putstr_fd("\033[34;1mLight config:\t\t  \033[0m", 1);
}
