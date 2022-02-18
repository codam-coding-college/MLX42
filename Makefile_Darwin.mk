# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Darwin.mk                                 :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/16 12:49:18 by lde-la-h      ########   odam.nl          #
#    Updated: 2022/02/17 23:36:01 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# //= Variables =// #

NAME 			= libmlx42.a
HEADERS			= -I include
DYLIB_EXISTS	= test -e /usr/local/lib/libglfw.3.dylib || echo "false"

# Check for dylib amongst .brew directories.
ifneq ($(DYLIB_EXISTS), false)
	DYLIB_EXISTS = test -e /Users/$(USER)/.brew/opt/glfw/lib/libglfw.3.dylib || echo "false"
	ifneq ($(DYLIB_EXISTS), false)
		HEADERS += -I /Users/$(USER)/.brew/opt/glfw/include
	endif
endif

# //= Colors =// #
BOLD	= \033[1m
BLACK	= \033[30;1m
RED		= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m
