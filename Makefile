BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RED		:= \033[31;1m
RESET	:= \033[0m

NAME 		:= miniRT
CC 			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/libmlx42.a
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX)/include/MLX42
TEST		?= 0;

ifeq ($(USER), cariencaljouw)
	LIBFLAGS 	= -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ -framework Cocoa -framework OpenGL -framework IOKit
else
	LIBFLAGS	= -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

ifeq ($(TEST), 1)
	MAIN_SRC	:= testing/main.c
else
	MAIN_SRC	:= src/main.c
endif

MAIN		:= obj/main.o
OBJ 		:= $(addprefix obj/, utils.o parse/parse.o parse/unique.o parse/shapes.o vector.o objects/object.o objects/camera.o)
TEST_OBJ	:= $(addprefix testing/obj/, util.o)

all: $(NAME)

$(NAME): $(LIBS) $(MAIN) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFLAGS) $^ -o $@
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
	$(CC) $(CFLAGS) -c $^ -o $@ $(HEADERS)

$(TEST_OBJ): testing/obj/%.o : testing/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $^ -o $@ $(HEADERS)

clean:
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -rf obj/
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@rm -f $(NAME)
	@rm -f home
	@$(MAKE) -C $(LIBFT) fclean
	@$(MAKE) -C $(LIBMLX) fclean

re: 
	@echo "$(BLUE)$(BOLD)Cleaning miniRT$(RESET)"
	@rm -f $(NAME)
	@rm -rf obj/
	@$(MAKE) all;

.PHONY: all bonus clean fclean re