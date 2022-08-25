# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: lde-la-h <lde-la-h@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/19 08:43:31 by lde-la-h      #+#    #+#                  #
#    Updated: 2022/07/21 10:34:17 by lde-la-h      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

#//= Variables =//#

rwildcard = $(subst \,/,$(sort $(foreach d,$(wildcard $1/*),$(call rwildcard,$d,$2) $(wildcard $1/$2))))

#//= Colors =//#

BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME		:= test
SRC_DIR		:= .
SRCS		:= $(call rwildcard,$(SRC_DIR),*.c)
OBJS		:= $(sort $(patsubst %.c,%.o,$(SRCS)))
CFLAGS		:= -Wextra -Wall -Wunreachable-code -Wno-char-subscripts -Wno-unused-variable

ifeq ($(OS), Windows_NT)
	$(error Not supported)
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S), Linux)
		MLX_FLAGS := -ldl -lglfw -pthread -lm
	else ifeq ($(UNAME_S), Darwin)
		MLX_FLAGS := -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
	endif
endif

#//= Recipes =//#
# TODO: Check if any failed and only at the end error!

all: # Redirect to run target
	@$(MAKE) -si run

run: mlx $(OBJS)

mlx:
	@echo "\033[30;1m[Running tests]\033[0m"
	@$(MAKE) -s re DEBUG=1 -C ../
	@echo "\n"

%.o: %.c
	@gcc $^ -o $(NAME) ../libmlx42.a -I . -I ../include $(MLX_FLAGS) $(CFLAGS) && ./$(NAME)
	@rm -rf $(NAME)
