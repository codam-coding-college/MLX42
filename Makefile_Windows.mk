# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Windows.mk                                :+:    :+:             #
#                                                      +:+                     #
#    By: fbes <fbes@student.codam.nl>.                +#+                      #
#                                                    +#+                       #
#    Created: 2021/12/28 01:01:14 by fbes          #+#    #+#                  #
#    Updated: 2022/02/14 11:44:35 by fbes          ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME 				=	mlx42.a
ARCHIVE				=	-lgflfw3 -lopengl32 -lgdi32
override HEADERS	+=	-I include
