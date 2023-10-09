BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RED		:= \033[31;1m
RESET	:= \033[0m

NAME 		:= miniRT
CC 			:= cc
CFLAGS 		:= -Wall -Wextra -Werror -O3 #-pthread #-g -fsanitize=address
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42/build
LIBS		:= $(LIBMLX)/libmlx42.a $(LIBFT)/libft.a 
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX) -I includes/ -I ./libs/MLX42/include/MLX42
TEST		?= 0;

UNAME		:= $(shell uname)

ifeq ($(UNAME),Darwin)
	THREADS = $(shell sysctl -n hw.ncpu)
else ifeq ($(UNAME),Linux)
	THREADS = $(shell nproc --all)"
endif

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

# MAIN		:= obj/main/main.o
OBJ 		:= $(addprefix obj/, \
				$(addprefix main/, main.o utils.o render.o multithreading.o init.o ascii.o key_hooks.o) \
				$(addprefix parse/, parse.o unique.o shapes.o setters.o setters2.o light.o) \
				$(addprefix objects/, sphere.o plane.o cylinder.o cone.o) \
				$(addprefix image/, image_manipulation.o image_utils.o resize_select.o) \
				$(addprefix math/, matrix_transformations.o matrix_utils.o matrix_inverse.o matrix_inverse_utils.o vector.o vector2.o vector3.o matrix_vector_utils.o) \
				$(addprefix textures/, text_utils.o color_maps.o procedural_textures.o bump_mapping.o) \
				$(addprefix light/, shadow_ray.o light_types.o) \
				)
TEST_OBJ	:= #$(addprefix testing/obj/, utils.o)

all: bonus_one $(NAME)

bonus_zero:
	$(eval THREADS = 1)
	$(eval CFLAGS += -D BONUS=0 -D THREADS=$(THREADS))
	
bonus_one:
	$(eval CFLAGS += -D BONUS=1 -D THREADS=$(THREADS))

mandatory:  bonus_zero $(NAME)

$(NAME): $(MAIN) $(OBJ) $(TEST_OBJ) $(LIBS) 
	# $(eval CFLAGS += -D THREADS=$(THREADS))
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

fclean: clean
	@rm -f $(NAME)
	@rm -f ./test
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) clean


re: 
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -f $(NAME)
	@rm -f ./test
	@rm -rf obj/
	@$(MAKE) all

.PHONY: all test bonus clean fclean re