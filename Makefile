# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:32:49 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/26 22:13:15 by W2Wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= libmlx42.a
CFLAGS	= -Wextra -Wall -Wunreachable-code -Wno-char-subscripts
override HEADERS +=	-I include # Allow override for cygwin github actions
ifndef NOWARNING
CFLAGS	+= -Werror
endif
ifdef DEBUG
CFLAGS	+= -g
endif

ifeq ($(OS), Windows_NT)
	ifdef CYGWIN
		include Makefile_Unix.mk
	else
    	include Makefile_WindowsNT.mk
	endif
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
        include Makefile_Unix.mk
	else ifeq ($(UNAME_S), Darwin)
		DYLIB_EXISTS = test -e /usr/local/lib/libglfw.3.dylib || echo "false"
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