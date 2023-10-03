/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 23:38:39 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/03 21:25:08 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Return the biggest of two ints
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

/**
 * @brief Return the smallest of two ints
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

/**
 * @brief Return the largest of two floats
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float	ft_fmax(float a, float b)
{
	if (b > a)
		return (b);
	return (a);
}

/**
 * @brief Return the smalles of two floats
 * 
 * @param a 
 * @param b 
 * @return float 
 */
float	ft_fmin(float a, float b)
{
	if (b < a)
		return (b);
	return (a);
}
