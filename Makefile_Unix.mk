# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile_Unix.mk                                   :+:    :+:             #
#                                                      +:+                     #
#    By: W2Wizard <w2.wizzard@gmail.com>              +#+                      #
#                                                    +#+                       #
#    Created: 2022/02/26 21:36:38 by W2Wizard      #+#    #+#                  #
#    Updated: 2022/08/24 16:29:24 by swofferh      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

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

# Just a colorful message to be printed out on screen:
MLX42 = $(BLUE)MLX$(YELLOW)42$(RESET)

start:
	@echo "$(CYAN)--------------------\n  Now making MLX42 \n--------------------$(RESET)"

#//= Make Rules =//#
$(NAME): $(OBJS)
	@ar rc $@ $^
	@echo "$(CYAN)Compiling$(RESET) with flags $(RED)-> $(RESET)$(CFLAGS)"
	@echo "$(CYAN)---------"
	@echo "$(CYAN)Compiling$(RESET) DONE."
	@echo "$(CYAN)---------"
	@echo "$(RESET)\n$(MLX42) powered by W2Wizard."

%.o: %.c $(HDRS)
	@echo "$(CYAN)Compiling$(RESET) $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

# Converting shaders to .c files
$(SRC_DIR)/mlx_%_shader.c: $(SHADER_DIR)/default.%
	@echo "$(BLUE)Converting$(RESET) $< $(RED)->$(RESET) $@"
	@bash tools/compile_shader.sh $< > $@

clean:
	@echo "$(RED)Cleaning $(PROJECT)"
	@rm -f $(OBJS) $(SHDR)

fclean: clean
	@rm -f $(NAME)
