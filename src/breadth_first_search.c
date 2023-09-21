/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   breadth_first_search.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/01/26 10:40:37 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/21 14:28:14 by ccaljouw      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/miniRT.h"

int	check_coord(t_scene *scene, t_pos *pos)
{
	if (scene->pixels[pos->y][pos->x].hitobject == scene->search)
	{
		mlx_put_pixel(scene->image, pos->x, pos->y, (100 << 24 | 100 << 16 | 100 << 8 | 100));
		return (1);
	}
	return (0);
}

int	check_set(t_scene *scene, t_list *set, int x, int y)
{
	t_pos	*pos;
	t_list	*list;

	list = set;
	if (x >= scene->p_width - 1 || y >= scene->p_height - 1 \
		|| x < 0 || y < 0)
		return (0);
	while (list)
	{
		pos = list->content;
		if (x == pos->x && y == pos->y)
			return (1);
		list = list->next;
	}
	return (0);
}

int	check_neighbor(t_scene *scene, t_list **reached, int x, int y)
{
	t_pos	*pos;

	if (!check_set(scene, *reached, x, y))
	{
		pos = malloc(sizeof(t_pos));
		if (!pos)
			exit_error(ERROR_MEM, NULL, scene);
		pos->x = x;
		pos->y = y;
		ft_lstadd_back(reached, ft_lstnew(pos));
		if (check_coord(scene, pos))
			return (1);
	}
	return (0);
}

void	bfs(t_scene *scene, t_list *frontier, t_list *reached)
{
	t_pos	*pos;
	t_list	*temp;

	if (!frontier)
		return ;
	pos = frontier->content;
	if (check_neighbor(scene, &reached, pos->x + 1, pos->y))
		ft_lstadd_back(&frontier, ft_lstnew(ft_lstlast(reached)->content));
	if (check_neighbor(scene, &reached, pos->x - 1, pos->y))
		ft_lstadd_back(&frontier, ft_lstnew(ft_lstlast(reached)->content));
	if (check_neighbor(scene, &reached, pos->x, pos->y + 1))
		ft_lstadd_back(&frontier, ft_lstnew(ft_lstlast(reached)->content));
	if (check_neighbor(scene, &reached, pos->x, pos->y - 1))
		ft_lstadd_back(&frontier, ft_lstnew(ft_lstlast(reached)->content));
	temp = frontier;
	frontier = frontier->next;
	free(temp);
	bfs(scene, frontier, reached);
}

int	check_object(t_scene *scene, int x, int y)
{
	t_list	*frontier;
	t_list	*reached;
	t_pos	*pos;

	pos = malloc(sizeof(pos));
	if (!pos)
		exit_error(ERROR_MEM, NULL, scene);
	if (!scene->pixels[y][x].hitobject)
		return (0);
	pos->x = x;
	pos->y = y;
	frontier = NULL;
	reached = NULL;
	ft_lstadd_back(&reached, ft_lstnew(pos));
	ft_lstadd_back(&frontier, ft_lstnew(pos));
	bfs(scene, frontier, reached);
	ft_lstclear(&reached, NULL); //check if should be cleaned
	return (1);
}
