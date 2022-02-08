# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/15 15:06:20 by w2wizard      #+#    #+#                  #
#    Updated: 2022/02/08 17:45:43 by lde-la-h      ########   odam.nl          #
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
        $(error OS: $(OS_NAME) - Is not supported!)
    endif
endif

# //= Files =// #

# TODO: Add files, remove shell command.
# TODO: Exclude glad.c from norme.
SRCS	=	$(shell find ./src -iname "*.c")
OBJS	=	${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(NAME)
	
%.o: %.c
	@printf	"$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\x1b[35C[OK]\n$(RESET)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(ARCHIVE)

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