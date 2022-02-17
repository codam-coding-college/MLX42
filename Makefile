# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/15 15:06:20 by w2wizard      #+#    #+#                  #
#    Updated: 2022/02/17 23:07:01 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifeq ($(OS), Windows_NT)
    CC = gcc # Assuming user has installed GnuWin32, perhaps switch to VC++
    include Makefile_Windows.mk
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

# /usr/bin/find is explicitly mentioned here for Windows compilation under Cygwin
# //= Files =// #
SHDR	=	src/mlx_vert.c src/mlx_frag.c
SHDRSRC	=	shaders/default.frag shaders/default.vert
SRCS	=	$(shell /usr/bin/find ./src -iname "*.c") $(SHDR) lib/glad/glad.c
OBJS	=	${SRCS:.c=.o}

# //= Rules =// #
## //= Compile =// #
all: $(SHDR) $(NAME)

# Convert our shaders to .c files
src/mlx_vert.c: shaders/default.vert
	@echo "$(GREEN)$(BOLD)Converting shader: $< -> $@ $(RESET)"
	@python3 tools/compile_shader.py $^ > $@

src/mlx_frag.c: shaders/default.frag 
	@echo "$(GREEN)$(BOLD)Converting shader: $< -> $@ $(RESET)"
	@python3 tools/compile_shader.py $^ > $@

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) $(ARCHIVE) && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@printf "$(GREEN)$(BOLD)Done\n$(RESET)"

## //= Commands =// #

clean:
	@echo "$(RED)Cleaning$(RESET)"
	@rm -f $(OBJS) $(SHDR)

fclean: clean
	@rm -f $(NAME)

re:	fclean all

## //= Misc =// #
.PHONY: all, clean, fclean, re