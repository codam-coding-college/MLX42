# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/01/02 12:10:02 by W2Wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= mlx42
CFLAGS	= -Wextra -Werror -Wall -Wunreachable-code -O3 -g

# //= Colors =// #
BOLD	= \e[1m
GREEN	= \x1b[32m
RESET	= \033[0m
RED		= \x1b[31m

# Define the header location
HEADERS = -I include -I src/Internal
LIBS	= /usr/local/lib/libglfw.dylib

# //= Files =// #

# TODO: Add files, remove shell command.
# TODO: Exclude glad.c from norme.
SRCS	=	$(shell find ./src -iname "*.c") main.c
OBJS	= ${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(NAME)
	
%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<) 🔨 \n$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) 

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(HEADERS) $(LIBS) -o $(NAME)
	@printf "$(GREEN)$(BOLD)Done ✅\n$(RESET)"

## //= Commands =// #

# Clean
clean:
	@echo "$(RED)Cleaning 🧹$(RESET)"
	@rm -f $(OBJS)

# Full clean
fclean: clean
	@rm -f $(NAME)

# Re-compile
re:	fclean all

## //= Misc =// #

# Phonies as not to confuse make, these are actual commands, not files.
.PHONY: all, clean, fclean, re

#all:
#	clang main.c glad.c /usr/local/Cellar/glfw/3.3.6/lib/libglfw.3.3.dylib