# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: w2wizard <w2wizard@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2022/01/15 15:06:20 by w2wizard      #+#    #+#                  #
#    Updated: 2022/01/15 15:35:03 by w2wizard      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

OS_NAME	=	$(shell uname -s | tr A-Z a-z)

ifeq ($(OS_NAME), linux)
CC = gcc
include Makefile_Linux.mk
else ifeq ($(OS_NAME), darwin)
CC = clang
include Makefile_Darwin.mk
else
$(error OS: $(OS_NAME) - Is not supported!)
endif