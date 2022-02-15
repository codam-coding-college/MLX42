# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/15 15:06:20 by w2wizard      #+#    #+#                  #
#    Updated: 2022/02/14 14:56:53 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifeq ($(OS), Windows_NT)
    CC = gcc # Assuming user has installed GnuWin32, perhaps switch to VC++
    $(error No Build script availble. Compile manually!)
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        CC = gcc
        include Makefile_Linux.mk
	else ifeq ($(UNAME_S), Darwin)
        CC = clang
        include Makefile_Darwin.mk
    else
        $(error OS: $(OS) - Is not supported!)
    endif
endif

CFLAGS	= -Wextra -Wall -Wunreachable-code -g
ifndef NOWARNING
CFLAGS	+= -Werror # Because norme forced us to live with an error
endif

#TODO: Due to Windows, might have to move recipes below to their own respective makefiles

# //= Files =// #

SRCS	=	$(shell find ./src -iname "*.c") lib/glad/glad.c
OBJS	=	${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(NAME)
	
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(ARCHIVE) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS) 
	@printf "$(GREEN)$(BOLD)Done\n$(RESET)"

## //= Commands =// #

clean:
	@echo "$(RED)Cleaning$(RESET)"
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

## //= Misc =// #
.PHONY: all, clean, fclean, re