/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ccaljouw <ccaljouw@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:44:22 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/09/23 20:27:12 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/miniRT.h"


/**
 * @brief swap t1 and t2
 * 
 * @param t0 
 * @param t1 
 */
void	swap(float *x1, float *x2)
{
	float temp;

	temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

void	exit_error(char *error_msg, char *optional_str, t_scene *scene)
{
	ft_putendl_fd("\033[31;1mError", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": \033[0m", 2);
	if (optional_str)
		ft_putendl_fd(optional_str, 2);
	else
		ft_putchar_fd('\n', 2);
	(void)scene; //remove
	// if (scene)
	// 		cleanup scene
	exit (1);
}

void	clean_pixels(t_scene *scene)
{
	int	x;
	int	y;
	
	
	x = 0;
	y = 0;
	if (scene->p_width)
	{
		while (y < scene->p_height)
		{
			while (x < scene->p_width)
			{
				free(scene->pixels[y] + x);
				x++;
			}
			y++;
		}
		free(scene->pixels);
		scene->pixels = NULL;
	}
}

void	print_vector(t_xyz vector)
{
	printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);  //weghalen
}

void	replace(char *str, char replace, char with)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == replace)
			str[i] = with;
		i++;
	}
}