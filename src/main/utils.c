/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:44:22 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/12 09:31:40 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

/**
 * @brief swap floats x1 and x2
 * 
 * @param x0 
 * @param x1 
 */
void	swap(float *x1, float *x2)
{
	float	temp;

	temp = *x1;
	*x1 = *x2;
	*x2 = temp;
}

/**
 * @brief Exits the program and display [error_msg] and optional nullable
 * 		[optional string]. Exits with 0 when the [error_msg] is "Closing MLX"
 * 
 * @param error_msg 
 * @param optional_str 
 * @param scene 
 */
void	exit_error(char *error_msg, char *optional_str, t_scene *scene)
{
	if (!ft_strcmp("Closing MLX", error_msg))
	{
		clean_scene(scene);
		exit (0);
	}
	ft_dprintf(2, "\033[31;1mError: %s", error_msg);
	if (optional_str)
		ft_dprintf(2, "\n\033[0m\033[33;1m%s\033[0m\n", optional_str);
	else
		ft_dprintf(2, "\n");
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

/**
 * @brief For debug, print the values of a vector and add a newline
 * 
 * @param vector 
 */
void	print_vector(t_xyz vector)
{
	ft_printf("[%.3f, %.3f, %.3f]\n", vector.x, vector.y, vector.z);
}

/**
 * @brief Replace character [replace] with character [with] in the 
 * 		string [str]
 * 
 * @param str 
 * @param replace 
 * @param with 
 */
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
