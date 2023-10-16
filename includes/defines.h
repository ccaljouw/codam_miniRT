/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:37:16 by albertvanan       #+#    #+#             */
/*   Updated: 2023/10/16 22:42:47 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define NR_TEXTURES		14
# define TEXT_PROCEDURES	6
# define BUMP_PROCEDURES 	3
// # define AA					1
// # define AA_SAMPLES			2

# define ALBEDO				.18
# define MAX_REFRACT		5
# define STD_REFLECT		5
# define MAX_REFLECT		10

# define ROT_X_N 			MLX_KEY_RIGHT
# define ROT_X_P 			MLX_KEY_LEFT
# define ROT_Y_N 			MLX_KEY_UP
# define ROT_Y_P 			MLX_KEY_DOWN
# define ROT_Z_N 			MLX_KEY_PERIOD
# define ROT_Z_P 			MLX_KEY_COMMA

# define MOVE_FRONT			MLX_KEY_W
# define MOVE_BACK			MLX_KEY_S
# define MOVE_RIGHT			MLX_KEY_D
# define MOVE_LEFT			MLX_KEY_A
# define MOVE_UP			MLX_KEY_Q
# define MOVE_DOWN			MLX_KEY_E

# define ZOOM_IN 			MLX_KEY_I
# define ZOOM_OUT 			MLX_KEY_O

# define REFLECTION			MLX_KEY_R

# define EPSILON 			0.0000000000000000000001
# define LIGHT_BOOST 		10000
# define SHADOW_BIAS 		0.001

# define IM_WIDTH 			512
# define IM_HEIGHT 			512
# define MAX_WIDTH 			1600
# define MAX_HEIGHT 		1024
# define MAX_AA				5

# define ASCII_WIDTH  		120
# define ASCII_HEIGHT 		40
# define ASCII_RED			0.299
# define ASCII_GREEN		0.587
# define ASCII_BLUE			0.114

# define NEW_LIGHT_DIST		10
# define NEW_OBJECT_DIST	5

# define PROGRESS_BAR_LEN	50

# define BONUS_SPECS		10
# ifndef BONUS
#  define BONUS				0
# endif

#endif