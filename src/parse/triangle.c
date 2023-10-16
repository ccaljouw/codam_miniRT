/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:08:13 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 16:21:11 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	min_max_values(float *min_max, t_object *tr)
{
	int		i;

	i = 0;
	min_max[0] = 1000000;
	min_max[1] = -1000000;
	min_max[2] = 1000000;
	min_max[3] = -1000000;
	while (i < 3)
	{
		if (tr->p[i].x < min_max[0])
			min_max[0] = tr->p[i].x;
		if (tr->p[i].x > min_max[1])
			min_max[1] = tr->p[i].x;
		if (tr->p[i].y < min_max[2])
			min_max[2] = tr->p[i].y;
		if (tr->p[i].y > min_max[3])
			min_max[3] = tr->p[i].y;
		i++;
	}
}

void	triangle_vectors(t_object *tr)
{
	t_xyz	p0p1;
	t_xyz	p0p2;
	float	min_max[4];

	p0p1 = v_subtract(tr->p[1], tr->p[0]);
	p0p2 = v_subtract(tr->p[2], tr->p[0]);
	tr->v_normal = v_normalize(v_cross(p0p1, p0p2));
	tr->edge[0] = v_subtract(tr->p[1], tr->p[0]);
	tr->edge[1] = v_subtract(tr->p[2], tr->p[1]);
	tr->edge[2] = v_subtract(tr->p[0], tr->p[2]);
	min_max_values(min_max, tr);
	tr->plane_y = min_max[3] - min_max[2];
	tr->plane_x = min_max[1] - min_max[0];
}

void	init_triangle(char **param, t_scene *scene)
{
	t_list		*new_node;
	t_object	*new_tr;
	int			i;

	i = 0;
	while (param[i])
		i++;
	if (!BONUS)
		exit_error(ERROR_TR, "triangle not implemented in mandatory", scene);
	if (i != 5 && i != 5 + BONUS_SPECS)
		exit_error(ERROR_TR, "incorrect number of arguments", scene);
	new_tr = ft_calloc(1, sizeof(t_object));
	new_node = ft_lstnew(new_tr);
	if (!new_tr || !new_node)
		exit_error(ERROR_MEM, NULL, scene);
	new_tr->id = TR;
	new_tr->p[0] = set_xyz(param[1], scene);
	new_tr->p[1] = set_xyz(param[2], scene);
	new_tr->p[2] = set_xyz(param[3], scene);
	new_tr->rotate_matrix = m44_init();
	triangle_vectors(new_tr);
	set_surface_properties(&param[4], new_tr, i - BONUS_SPECS, scene);
	ft_lstadd_back(&scene->objects, new_node);
	ft_putstr_fd("\033[34;1mTriangle config:\t\033[0m", 1);
}
