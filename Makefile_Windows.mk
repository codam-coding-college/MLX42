# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Windows.mk                                :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>.                +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by fbes          #+#    #+#                  #
#    Updated: 2022/02/17 23:36:09 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

# //= Variables =// #

NAME 				=	libmlx42.a
ARCHIVE				=	-lgflfw3 -lopengl32 -lgdi32
override HEADERS	+=	-I include

# //= Colors =// #
# Nope :(