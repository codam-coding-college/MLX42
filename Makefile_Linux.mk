# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Linux.mk                                  :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/01/16 00:41:08 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 	=	mlx42.a
CFLAGS	=	-Wextra -Wall -Werror -Wunreachable-code -O3
ARCHIVE	=	-ldl -lglfw -lGL -lX11 -lpthread -lXrandr -lXi
HEADERS =	-I include
