# -----------------------------------------------------------------------------
# Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
# See README in the root project for more information.
# -----------------------------------------------------------------------------

NAME	:= test
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
SRCS	:= unit.c tests.c
OBJS	:= ${SRCS:.c=.o}
LIBMLX	:= ../
LIBS	:= $(LIBMLX)build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build

$(NAME): libmlx $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@echo "Compiling: $(notdir $<)"
	@$(CC) $(CFLAGS) -I ../include -o $@ -c $<

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean $(NAME)