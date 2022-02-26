# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:32:49 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/26 21:32:49 by W2Wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= libmlx.a
CFLAGS	= -Wextra -Wall -Wunreachable-code -Wno-char-subscripts
override HEADERS +=	-I include # Allow override for cygwin github actions
ifndef NOWARNING
CFLAGS	+= -Werror
endif
ifdef DEBUG
CFLAGS	+= -g
endif

#TODO: Add extra define for cygwin for github actions and potential other people
ifeq ($(OS), Windows_NT)
	ARCHIVE	= -lglfw3 -lopengl32 -lgdi32
    include Makefile_Windows.mk
else
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S), Linux)
		ARCHIVE	= -ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
        include Makefile_Unix.mk
	else ifeq ($(UNAME_S), Darwin)
		ARCHIVE	= -lglfw
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

.PHONY: all, clean, fclean, re