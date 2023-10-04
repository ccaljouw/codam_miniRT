/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 20:37:16 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/04 15:55:41 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define NR_TEXTURES		3
# define TEXT_PROCEDURES	3
# define BUMP_MAPS 			1

# define MOVE_X_P 			MLX_KEY_RIGHT
# define MOVE_X_N 			MLX_KEY_LEFT
# define MOVE_Y_P 			MLX_KEY_UP
# define MOVE_Y_N 			MLX_KEY_DOWN
# define MOVE_Z_P 			MLX_KEY_PERIOD
# define MOVE_Z_N 			MLX_KEY_COMMA

# define ZOOM_IN 			MLX_KEY_I
# define ZOOM_OUT 			MLX_KEY_O

# define EPSILON 			exp(-21)
# define LIGHT_BOOST 		10000
# define ALBEDO				0.057295779513082
# define SHADOW_BIAS 		0.001

# define IM_WIDTH 			512
# define IM_HEIGHT 			512
# define MAX_WIDTH 			1024
# define MAX_HEIGHT 		1024

# define ASCII_WIDTH  		120
# define ASCII_HEIGHT 		40

#endif