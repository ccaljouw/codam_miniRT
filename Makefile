BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RED		:= \033[31;1m
RESET	:= \033[0m

NAME 		:= miniRT
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -O3 #-g -fsanitize=address
CFLAGS_BONUS := -D BONUS=1 -pthread 
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42/build
LIBS		:= $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a 
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX) -I includes/ -I ./libs/MLX42/include/MLX42

UNAME		:= $(shell uname)

ifeq ($(UNAME),Darwin)
	CFLAGS += "-D THREADS=$(shell sysctl -n hw.ncpu)"
	# CFLAGS += "-D THREADS=1"
else ifeq ($(UNAME),Linux)
	CFLAGS += "-D THREADS=$(shell nproc --all)"
endif

ifeq ($(USER), cariencaljouw)
	LIBFLAGS 	= -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(USER), albertvanandel)
	LIBFLAGS 	= -lglfw  -framework Cocoa -framework OpenGL -framework IOKit	
else
	LIBFLAGS	= -ldl -lglfw -lm
endif

OBJ 		:= $(addprefix obj/, \
				$(addprefix main/, main.o utils.o render.o init.o ascii.o key_hooks.o dummy.o dummy2.o) \
				$(addprefix parse/, parse.o unique.o shapes.o setters.o setters2.o light.o) \
				$(addprefix objects/, sphere.o plane.o cylinder.o cone.o) \
				$(addprefix image/, image_manipulation.o image_utils.o select.o resize.o light_manipulation.o) \
				$(addprefix math/, matrix_transformations.o matrix_utils.o matrix_inverse.o matrix_inverse_utils.o vector.o vector2.o vector3.o matrix_vector_utils.o) \
				$(addprefix textures/, text_utils.o color_maps.o procedural_textures.o bump_mapping.o) \
				$(addprefix light/, shadow_ray.o light_types.o) \
				)
OBJ_BONUS	:=  $(addprefix obj_bonus/, \
				$(addprefix main/, main.o utils.o render.o init.o ascii.o key_hooks.o multithreading.o) \
				$(addprefix parse/, parse.o unique.o shapes.o setters.o setters2.o light.o) \
				$(addprefix objects/, sphere.o plane.o cylinder.o cone.o) \
				$(addprefix image/, image_manipulation.o image_utils.o select.o resize.o light_manipulation.o) \
				$(addprefix math/, matrix_transformations.o matrix_utils.o matrix_inverse.o matrix_inverse_utils.o vector.o vector2.o vector3.o matrix_vector_utils.o) \
				$(addprefix textures/, text_utils.o color_maps.o procedural_textures.o bump_mapping.o) \
				$(addprefix light/, shadow_ray.o light_types.o light_transport.o) \
				$(addprefix edit/, save.o print_shapes.o save_util.o add_delete.o) \
				)

all: bonus

mandatory: $(NAME)    #change before submission!!

$(NAME): $(OBJ) $(LIBS)
	@$(CC) $(CFLAGS) $^ -o $@  $(LIBFLAGS)
	@echo "$(GREEN)$(BOLD)miniRT made$(RESET)"

bonus: $(OBJ_BONUS) $(LIBS)
	@$(CC) $(CFLAGS) $(CFLAGS_BONUS) $^ -o $(NAME)  $(LIBFLAGS)
	@echo "$(GREEN)$(BOLD)miniRT bonus made$(RESET)"

$(LIBS): 
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(LIBMLX)
	@echo "$(BLUE)Compiling object files miniRT:$(RESET)"


$(OBJ): obj/%.o : src/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@  $(HEADERS)

$(OBJ_BONUS): obj_bonus/%.o : src/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CFLAGS_BONUS) -c $^ -o $@  $(HEADERS)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -rf obj/
	@rm -rf obj_bonus/
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f ./test
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) clean


re: 
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -f $(NAME)
	@rm -rf obj/
	@rm -rf obj_bonus/
	@$(MAKE) all

.PHONY: all mandatory bonus clean fclean re