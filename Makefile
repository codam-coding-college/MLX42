# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvissche <vvissche@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:32:49 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/03/13 16:58:14 by vvissche      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= libmlx42.a
CFLAGS	= -Wextra -Wall -Wunreachable-code -Wno-char-subscripts
ifndef NOWARNING
CFLAGS	+= -Werror
endif
ifdef DEBUG
CFLAGS	+= -g
else
CFLAGS	+= -Ofast
endif

ifeq ($(OS), Windows_NT)
	ifdef CYGWIN
		override HEADERS +=	-I include
		include Makefile_Unix.mk
	else
		HEADERS +=	-I include
    	include Makefile_WindowsNT.mk
	endif
else
	HEADERS +=	-I include
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        include Makefile_Unix.mk
	else ifeq ($(UNAME_S), Darwin)

		# Default
		DYLIB_EXISTS = test -e /usr/local/lib/libglfw.3.dylib || echo "false"

		# Generic Homebrew path
		ifneq ($(DYLIB_EXISTS), false)
			BREW_GLFW_PREFIX := $(shell brew --prefix glfw)
			DYLIB_EXISTS = test -e $(BREW_GLFW_PREFIX)"/lib/libglfw.3.dylib" || echo "false"
			ifneq ($($DYLIB_EXISTS), false)
				HEADERS += -I $(BREW_GLFW_PREFIX)"/include"
			endif
		endif

		# Homebrew path
		ifneq ($(DYLIB_EXISTS), false)
			DYLIB_EXISTS = test -e /opt/homebrew/Cellar/glfw/3.3.6/lib/libglfw.3.dylib || echo "false"
			ifneq ($(DYLIB_EXISTS), false)
				HEADERS += -I /opt/homebrew/Cellar/glfw/3.3.6/include
			endif
		endif
		
		# Homebrew42 path
		ifneq ($(DYLIB_EXISTS), false)
			DYLIB_EXISTS = test -e /Users/$(USER)/.brew/opt/glfw/lib/libglfw.3.dylib || echo "false"
			ifneq ($(DYLIB_EXISTS), false)
				HEADERS += -I /Users/$(USER)/.brew/opt/glfw/include
			endif
		endif
        include Makefile_Unix.mk
    else
        $(error OS: $(OS) - Is not supported!)
    endif
endif

#//= Misc =//#
.PHONY: all, clean, fclean, re