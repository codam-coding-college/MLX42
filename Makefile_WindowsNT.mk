# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_WindowsNT.mk                              :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:32:00 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/26 21:32:00 by W2Wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# While windows does have support for nmake it offers nowhere near the amount of
# features GnuWin does.

#//= Colors =//#
# Nope :(

CC		= gcc # We need to explicitly mention GCC/CC here.
WINSTFU	= > NUL 2>&1 # In some cases we want windows to just stfu
SHDR	= src\mlx_vert.c src\mlx_frag.c
SHDRSRC	= shaders\default.frag shaders\default.vert
SRCS	= $(shell dir /S/B "*.c") $(SHDR)
OBJS	= $(SRCS:.c=.o)

#//= Recipes =//#
all: $(SHDR) $(NAME)

# Convert our shaders to .c files
src\mlx_vert.c: shaders\default.vert
	@echo "Converting shader: $< -> $@"
	@python3 tools\compile_shader.py $^ > $@

src\mlx_frag.c: shaders\default.frag 
	@echo "Converting shader: $< -> $@"
	@python3 tools\compile_shader.py $^ > $@

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS) && echo Compiling: $(notdir $<) [OK]

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo Done

clean:
	@del /F /Q $(OBJS) $(SHDR) $(WINSTFU)

fclean: clean
	@del /Q $(NAME) $(WINSTFU)

re: clean all

.PHONY : all clean re fclean