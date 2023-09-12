NAME 		:= miniRT
CC 			:= gcc
CFLAGS 		:= -Wall -Wextra -Werror
CODAMFLAGS  := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
LIBFT	 	:= ./libs/libft
LIBMLX		:= ./libs/MLX42
LIBS		:= $(LIBFT)/libft.a $(LIBMLX)/libmlx42.a
HEADERS		:= -I $(LIBFT)  -I $(LIBMLX)/include/MLX42

OBJ 		:= $(addprefix obj/, main.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(CODAMFLAGS) $^ -o $@
	@echo miniRT made.

bonus: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) $(CODAMFLAGS) $^ -o $@

carien: $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -lglfw -L /opt/homebrew/Cellar/glfw/3.3.8/lib/ $^ -o $@

$(LIBS): 
	@$(MAKE) -C $(LIBFT)
	@$(MAKE) -C $(LIBMLX)

obj/%.o : src/%.c
	@mkdir -p $(dir $@)
	@echo Creating miniRT object: $@ "\x1b[1A\x1b[M"
	$(CC) $(CFLAGS) -c $^ -o $@ $(HEADERS)

clean:
	rm -rf obj/
	@$(MAKE) -C $(LIBFT) clean
	@$(MAKE) -C $(LIBMLX) clean

fclean: clean
	@echo Cleaning miniRT objects
	@rm -f $(NAME)
	@rm -f home
	@$(MAKE) -C $(LIBFT) fclean
	# @$(MAKE) -C $(LIBMLX) fclean

re: fclean all

.PHONY: all bonus clean fclean re