# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abarthel <abarthel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/25 14:03:51 by abarthel          #+#    #+#              #
#    Updated: 2019/08/01 17:23:01 by abarthel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

-include minishell.mk

#OPTIMIZATION	:= -O2 -fno-builtin
OPTIMIZATION	:=
DEBUGGING	:= -g
SANITIZE	:= -fsanitize=address
WARNING		:= -Wall -Wextra -Werror
ANSI		:= -ansi

CFLAGS += $(WARNING) $(ANSI) $(DEBUGGING) $(SANITIZE) $(OPTIMIZATION)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME)	: $(OBJECTS)
	@make lib -j -C $(PATH_LIB)
	@$(CC) $(CFLAGS) $^ -o $@ $(LIB)
	@printf "\n\e[38;5;44m%4s [\e[1m$(NAME) built]\n\n\e[0m"

clean:
	@$(RM) $(OBJECTS) $(DEPENDS)
	@make clean -C $(PATH_LIB)

fclean:
	@$(RM) $(OBJECTS) $(DEPENDS) $(NAME)
	@make fclean -C $(PATH_LIB)

re: fclean $(NAME)

test: all
	@bash $(TESTS_PATH)$(TESTS_SCRIPT)

-include $(DEPENDS)

%.o: %.c Makefile
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@
	@printf "\e[38;5;155m%-24s \e[38;5;37mobject built\n\e[0m" $(notdir $(basename $@))
