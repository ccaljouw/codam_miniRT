/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 16:44:22 by ccaljouw      #+#    #+#                 */
/*   Updated: 2023/10/03 09:09:34 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief swap x1 and x2
 * 
 * @param x0 
 * @param x1 
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
	if (!ft_strcmp("Closing MLX", error_msg))
	{
		clean_scene(scene);
		exit (0);
	}
	ft_putendl_fd("\033[31;1mError", 2);
	ft_putstr_fd(error_msg, 2);
	ft_putstr_fd(": \033[0m", 2);
	if (optional_str)
		ft_putendl_fd(optional_str, 2);
	else
		ft_putchar_fd('\n', 2);
	if (scene)
		clean_scene(scene);
	exit (1);
}

/**
 * @brief Clamps the input value between the min and max value,
 * 		returns the result.
 * 
 * @param min 
 * @param max 
 * @param input 
 * @return float 
 */
float	ft_clamp(float min, float max, float input)
{
	if (input > max)
		return (max);
	if (input < min)
		return (min);
	return (input);
}


void	print_vector(t_xyz vector)
{
	ft_printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);
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
