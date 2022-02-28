# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:32:49 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/28 17:55:05 by lde-la-h      ########   odam.nl          #
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