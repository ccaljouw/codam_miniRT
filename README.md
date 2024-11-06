# MiniRT | CODAM Amsterdam

## Introduction
Implementation of a limited raytracer to create realistic images from scratch

## Features
- Create an image based on input .rt file
- Change image (see Key Inputs)
- Save image (see Key Inputs)

## Requirements
- Linux or MacOS
- C compiler (tested with clang)
- glfw
- OpenGL (for linux)

## Installation
- Clone the repository: `git clone https://github.com/ccaljouw/codam_miniRT.git <new folder>`
- Change directory: `cd <new folder>`
- Compile: `make` or `make bonus`
- Run the executable: `./miniRT <selected scene from scenes folder>`


## Credits
This MiniRT was created by Albert van Andel and Carien Caljouw as a project for CODAM programming school.

# Key inputs

## Generic inputs
- `L`: select next light
- `ENTER`: save scene
- `P`: adjust anti-alias level
- `R`: adjust reflection depth
- `+/-`: adjust ambient brightness
- SHIFT+movement(wasd, arrows) = fine adjustment

## With no object or light selected
- `W/S`: move camera front/back
- `A/D`: move camera left/right
- `Q/E`: move camera up/down
- `ARROW UP/DOWN`: tilt camera up/down
- `ARROW LEFT/RIGHT`: tilt camera left/right
- `< / >`: rotate camera
- `I/O`: zoom in/out (adjust field of view)

## with light selected
- `W/S`: move light front/back
- `A/D`: move light left/right
- `Q/E`: move light up/down
- `I/O`: brightness up/down

## with object selected
- `W/S`: move object front/back
- `A/D`: move object left/right
- `Q/E`: move object up/down
- `ARROW UP/DOWN`: rotate object around x-axis
- `ARROW LEFT/RIGHT`: rotate object around y-axis
- `< / >`: rotate object around z-axis
- `I/O`: scale/diameter up/down
- `SHIFT+I/O`: height up/down (for cylinder and cone)
- `R/SHIFT+R`: increase/decrease reflectiveness
- `T/SHIFT+T`: increase/decrease transparancy
- `Y`: cycle textures
- `SHIFT+Y`: cycle texture procedures
- `B`: cycle bump maps
- `SHIFT+B`: cycle bump procedures

# Overview of textures and bump maps:

## textures:
	1. checker
	2. world
	3. world2
	4. sterren

## bump textures:
	4. golf
	6-14. bump 1 tm 9

## texture procedures:
	1. checkered
	2. v_checkered
	3. gradient red to blue
	4. gradient black to white
	5. gradient red to blue merged with object/texture color
	6. gradient black to white merged with object/texture color


## bump procedures:
	1. simple_rough
	2. bump based on bump texture
	3. bump based on texture