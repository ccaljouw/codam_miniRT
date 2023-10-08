/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 23:55:32 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/08 23:55:56 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	set_l2w_matrix(t_light *new_light)
{
	new_light->l2w = m44_init();
	m44_translate_by_vector(&new_light->l2w, new_light->light_point);
	m44_multiply_vec3(new_light->l2w, v_create(0, 0, 0), &new_light->origin);
}

void	init_lights(char **param, t_scene *s)
{
	t_list		*new_node;
	t_light		*nw_lite;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (i != 4)
		exit_error(ERROR_LIGHT, "incorrect number of arguments", s);
	new_node = ft_lstnew(NULL);
	nw_lite = malloc(sizeof(t_light));
	if (!nw_lite || !new_node)
		exit_error(ERROR_MEM, NULL, s);
	nw_lite->light_point = set_xyz(param[1], s);
	nw_lite->brightness = to_float(param[2], s);
	if (nw_lite->brightness < 0.0 || nw_lite->brightness > 1.0)
		exit_error(ERROR_LIGHT, "Incorrect brightness values [0.0, 1.0]", s);
	set_rgb(param[3], nw_lite->rgb, s);
	set_l2w_matrix(nw_lite);
	nw_lite->rgb_ratios = v_create(nw_lite->rgb[0] / (float)255, \
		nw_lite->rgb[1] / (float)255, nw_lite->rgb[2] / (float)255);
	nw_lite->rgb_ratios = v_multiply(nw_lite->rgb_ratios, nw_lite->brightness);
	new_node->content = (void *)nw_lite;
	ft_lstadd_back(&s->lights, new_node);
	ft_putstr_fd("\033[34;1mLight config:\t\t  \033[0m", 1);
}
