# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Linux.mk                                  :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/17 23:36:06 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# //= Variables =// #

NAME 	=	libmlx42.a
ARCHIVE	=	-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
HEADERS =	-I include

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
