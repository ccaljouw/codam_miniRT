BOLD	:= \033[1m
GREEN	:= \033[32;1m
BLUE	:= \033[34;1m
RED		:= \033[31;1m
RESET	:= \033[0m

NAME 		:= miniRT
CC 			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror
CODAMFLAGS  := -lglfw -framework Cocoa -framework OpenGL -framework IOKit
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/libmlx42.a
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX)/include/MLX42

OBJ 		:= $(addprefix obj/, main.o utils.o parse/parse.o parse/unique.o parse/shapes.o vector.o)

all: $(NAME)

$(NAME): $(LIBS) $(OBJ)
	@$(CC) $(CFLAGS) $(CODAMFLAGS) $^ -o $@
	@echo "$(GREEN)$(BOLD)miniRT made$(RESET)"

bonus: $(OBJ) $(LIBS)
	@$(CC) $(CFLAGS) $(CODAMFLAGS) $^ -o $@

carien: $(LIBS) $(OBJ)
	$(CC) $(CFLAGS) -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ $^ -o $(NAME)
	@echo "$(GREEN)$(BOLD)miniRT made$(RESET)"

$(LIBS): 
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(LIBMLX)
	@echo "$(BLUE)Compiling object files miniRT:$(RESET)"

$(OBJ): obj/%.o : src/%.c
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