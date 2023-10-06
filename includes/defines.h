/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   defines.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: albertvanandel <albertvanandel@student.      +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 20:37:16 by albertvanan   #+#    #+#                 */
/*   Updated: 2023/10/06 08:38:33 by cariencaljo   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define NR_TEXTURES		3
# define TEXT_PROCEDURES	3
# define BUMP_MAPS 			2

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

# define EPSILON 			exp(-21)
# define LIGHT_BOOST 		10000
// # define ALBEDO				0.057295779513082
# define SHADOW_BIAS 		0.001

# define IM_WIDTH 			512
# define IM_HEIGHT 			512
# define MAX_WIDTH 			1024
# define MAX_HEIGHT 		1024

# define ASCII_WIDTH  		120
# define ASCII_HEIGHT 		40

#endif