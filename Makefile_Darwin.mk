# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Darwin.mk                                 :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/01/15 16:09:46 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= mlx42
ARCHIVE	= -lglfw
CFLAGS	= -Wextra -Wall -Wunreachable-code -O3 -g
HEADERS = -I include

# //= Colors =// #
BOLD	= \e[1m
GREEN	= \x1b[32m
RESET	= \033[0m
RED		= \x1b[31m

# //= Files =// #

# TODO: Add files, remove shell command.
# TODO: Exclude glad.c from norme.
SRCS	=	$(shell find ./src -iname "*.c")
OBJS	=	${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(NAME)
	
%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<) 🔨 \n$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(ARCHIVE)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS) 
	@printf "$(GREEN)$(BOLD)Done ✅\n$(RESET)"

## //= Commands =// #

clean:
	@echo "$(RED)Cleaning 🧹$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

## //= Misc =// #
.PHONY: all, clean, fclean, re
