/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_split_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:21:28 by albertvanan       #+#    #+#             */
/*   Updated: 2023/09/29 15:33:17 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Frees a 2d arr as made by ft_split() and sets all pointers to NULL
 * 
 * @param arr 
 */
void	ft_clean_split_arr(char ***arr)
{
	int	i;

	i = 0;
	if (*arr == NULL)
		return ;
	while ((*arr)[i] != NULL)
	{
		free ((*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
