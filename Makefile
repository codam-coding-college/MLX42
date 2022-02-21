# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/15 15:06:20 by w2wizard      #+#    #+#                  #
#    Updated: 2022/02/21 10:43:07 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

ifeq ($(OS), Windows_NT)
    include Makefile_Windows.mk
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        include Makefile_Linux.mk
	else ifeq ($(UNAME_S), Darwin)
        include Makefile_Darwin.mk
    else
        $(error OS: $(OS) - Is not supported!)
    endif
endif

CFLAGS	= -Wextra -Wall -Wunreachable-code -Wno-char-subscripts
ifndef NOWARNING
CFLAGS	+= -Werror # Windows
endif
ifdef DEBUG
CFLAGS	+= -g
endif

# //= Files =// #
# /usr/bin/find is explicitly mentioned here for Windows compilation under Cygwin
SHDR	=	src/mlx_vert.c src/mlx_frag.c
SHDRSRC	=	shaders/default.frag shaders/default.vert
LIBS	=	$(shell /usr/bin/find ./lib -iname "*.c")
SRCS	=	$(shell /usr/bin/find ./src -iname "*.c") $(SHDR) $(LIBS)
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