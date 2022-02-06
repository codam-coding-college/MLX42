# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Linux.mk                                  :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/02/06 22:30:18 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	mlx42.a
CFLAGS	=	-Wextra -Wall -Werror -Wunreachable-code -g # -Wpedantic
ARCHIVE	=	-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
HEADERS =	-I include
