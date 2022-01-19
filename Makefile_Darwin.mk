# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Darwin.mk                                 :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/01/18 21:39:42 by W2Wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	= mlx42.a
HEADERS = -I include
CFLAGS	= -Wextra -Wall -Werror -Wunreachable-code -g
DYLIB_EXISTS = test -e /usr/local/lib/libglfw.3.dylib || echo "false"

ifneq ($(DYLIB_EXISTS), false)
	DYLIB_EXISTS = test -e /Users/$(USER)/.brew/opt/glfw/lib/libglfw.3.dylib || echo "false"
	ifneq ($(DYLIB_EXISTS), false)
		HEADERS += -I /Users/$(USER)/.brew/opt/glfw/include
	endif
endif

# //= Colors =// #
BOLD	= \e[1m
GREEN	= \x1b[32m
RESET	= \033[0m
RED	= \x1b[31m

