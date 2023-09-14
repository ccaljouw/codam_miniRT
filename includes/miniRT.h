/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:38:40 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/09/14 13:00:43 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "MLX42.h"
# include "libft.h"
# include "errors.h"
# include "parser.h"
# include "vector.h"
# include <stdbool.h>
# include <stdlib.h>

# include <stdio.h> //remove

void	exit_error(char *error_msg, char *optional_str, t_scene *data);
t_scene	*init_scene(char *file);

#endif
