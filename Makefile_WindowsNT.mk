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

# While windows does have support for nmake it offers no near the amount of
# features GnuWin does.

# TODO: Make clean sometimes just NUKES the entire freaking project away ???

CC		= gcc # We need to explictely mention GCC/CC here.
NAME	= libmlx.a
HEADERS	= -I include
CFLAGS	= -Werror -Wextra -Wall -Wunreachable-code -Wno-char-subscripts -Ofast
WINSTFU	= > NUL 2>&1 # In some cases we want windows to just stfu
MAKE	= make --no-print-directory

SRCS	= $(shell dir * /S/B | findstr \.c*$)
OBJS	= $(SRCS:.c=.o)

#//= Colors =//#
# Nope :(

#//= Recipes =//#
all: $(NAME)

%.o: %.c
	@$(CC) -c $< -o $@ $(HEADERS) $(ARCHIVE) && echo Compiling: $(notdir $<) [OK]

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@del /F /Q $(OBJS) $(WINSTFU)

fclean:
	@$(MAKE) clean
	@del /F /Q $(NAME) $(WINSTFU)

re:
	@$(MAKE) clean
	@$(MAKE) all

.PHONY : all clean re fclean