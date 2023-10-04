BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RED		:= \033[31;1m
RESET	:= \033[0m

NAME 		:= miniRT
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -O3 -pthread #-g -fsanitize=address
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42/build
LIBS		:= $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a 
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX) -I includes/ -I ./libs/MLX42/include/MLX42
TEST		?= 0;

UNAME		:= $(shell uname)

ifeq ($(USER), cariencaljouw)
	LIBFLAGS 	= -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ -framework Cocoa -framework OpenGL -framework IOKit
else ifeq ($(USER), albertvanandel)
	LIBFLAGS 	= -lglfw  -framework Cocoa -framework OpenGL -framework IOKit	
else
	LIBFLAGS	= -ldl -lglfw -lm
endif

ifeq ($(TEST), 1)
	MAIN_SRC	:= testing/main.c
else
	MAIN_SRC	:= src/main.c
endif

ifeq ($(UNAME),Darwin)
	CFLAGS += "-D THREADS=$(shell sysctl -n hw.ncpu)"
	# CFLAGS += "-D THREADS=1"
else ifeq ($(UNAME),Linux)
	CFLAGS += "-D THREADS=$(shell nproc --all)"
endif

MAIN		:= obj/main.o
OBJ 		:= $(addprefix obj/, utils.o render.o multithreading.o \
				$(addprefix parse/, parse.o unique.o shapes.o) \
				$(addprefix objects/, sphere.o plane.o cylinder.o cone.o) \
				$(addprefix image/, image_manipulation.o image_utils.o) \
				$(addprefix math/, matrix_transformations.o matrix_utils.o matrix_inverse.o matrix_inverse_utils.o vector.o matrix_vector_utils.o) \
				$(addprefix textures/, text_utils.o procedural_textures.o bump_mapping.o) \
				$(addprefix light/, shadow_ray.o) \
				)
TEST_OBJ	:= #$(addprefix testing/obj/, utils.o)

all: $(NAME)

$(NAME): $(MAIN) $(OBJ) $(TEST_OBJ) $(LIBS) 
	@$(CC) $(CFLAGS) $^ -o $@  $(LIBFLAGS)
	@echo "$(GREEN)$(BOLD)miniRT made$(RESET)"

bonus: $(MAIN) $(OBJ) $(LIBS)
	@$(CC) $(CFLAGS) $(CODAMFLAGS) $^ -o $@

test:
	@$(MAKE) re TEST=1

$(LIBS): 
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(LIBMLX)
	@echo "$(BLUE)Compiling object files miniRT:$(RESET)"

$(MAIN): 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $(MAIN_SRC) -o obj/main.o $(HEADERS)

$(OBJ): obj/%.o : src/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@  $(HEADERS)

$(TEST_OBJ): testing/obj/%.o : testing/%.c 
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c  $^ -o $@ $(HEADERS)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -rf obj/
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f ./test
	@$(MAKE) -C $(LIBFT) fclean


re: 
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -f $(NAME)
	@rm -f ./test
	@rm -rf obj/
	@$(MAKE) all

.PHONY: all test bonus clean fclean re