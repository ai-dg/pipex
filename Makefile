SRC =	pipex.c utils1.c utils2.c utils3.c utils4.c utils5.c execute_cmd.c pipes_and_check.c

CC	=	cc
CFLAGS = -Wall -Wextra -Werror -g

OBJ =	$(SRC:.c=.o)

NAME = pipex

GREEN = \033[32m
BLINK = \033[5m
RESET = \033[0m
ORANGE = \033[33m

%.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Linking $(NAME)..."
	@$(CC) $(CFLAGS) $^ -o $@
	@echo  "$(GREEN)$(BLINK)$(NAME) compiled successfully!$(RESET)"

all: $(NAME)

clean:
	@echo "Cleaning object files..."
	@rm -rf $(OBJ)
	@echo "$(ORANGE)$(BLINK)Objects file cleanned.$(RESET)"

fclean: clean
	@echo "Cleaning $(NAME)..."
	@rm -rf $(NAME)
	@echo "$(ORANGE)$(BLINK)$(NAME) program cleanned.$(RESET)"

re: fclean all

.PHONY: all clean fclean re
