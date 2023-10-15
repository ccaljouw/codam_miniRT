/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albertvanandel <albertvanandel@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 16:09:09 by ccaljouw          #+#    #+#             */
/*   Updated: 2023/10/15 23:12:24 by albertvanan      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define SUCCESS "Closing MLX"
# define ERROR_MEM "Memory allocation error"
# define ERROR_MLX "Error in MLX42 function"
# define ERROR_PATH "Unable to open input file. \
Please check path, extention and file permissions"
# define ERROR_FLAG "Wrong flag provided"
# define ERROR_ARGS "Incorrect number of arguments"
# define ERROR_TYPE "Unsupported type provided"
# define ERROR_AMB "Incorrect parameters provided for Ambient lighting"
# define ERROR_CAM "Incorrect parameters provided for Camera"
# define ERROR_LIGHT "Incorrect parameters provided for Light"
# define ERROR_SPHERE  "Incorrect parameters provided for Sphere"
# define ERROR_PLANE "Incorrect parameters provided for Plane"
# define ERROR_CYLINDER "Incorrect parameters provided for Cylinder"
# define ERROR_CONE "Incorrect parameters provided for Cone"
# define ERROR_TR "Incorrect parameters provided for Triangle"
# define ERROR_RES "Incorrect parameters provided for Resolution"
# define ERROR_SCENE "Incorrect scene provided"
# define ERROR_XYZ "Incorrect coordinates provided"
# define ERROR_RGB "Incorrect RGB values provided"
# define ERROR_F "Incorrect float provided"
# define ERROR_THREAD "Multi threading"
# define ERROR_PNG "Error loading texture"
# define USAGE_MSG "Usage: ./miniRT [path_to_file].rt [optional: -a]"
# define ERROR_REFL "Incorrect reflection paramater provided"
# define ERROR_TRANSP "Incorrect transparancy paramater provided"

# define L_IN_MANDATORY	"only the L object is allowed in mandatory, \
as multiple lights are forbidden"
# define L_MULTIPLE "when 'L' is used, only a single light is allowed. \
Use 'l' instead for multple lights"

#endif
