# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: omathot <omathot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 01:41:47 by oscarmathot       #+#    #+#              #
#    Updated: 2023/12/08 11:54:30 by omathot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------
#VARIABLES

NAME 	:= philo
SRC 	:= main.c initialize.c threads.c helpers.c routines.c observer.c
SUBDIR	:= srcs/
SRCS	:= $(addprefix $(SUBDIR),$(SRC))
OBJ 	:= $(SRCS:.c=.o)
CMP		:= gcc
FLAGS 	:= -Werror -Wall -Wextra -pthread #-g -fsanitize=thread

#---------------------------------
#FORMATTING AND FUN

clear_line = \033[K
move_up = \033[A
define prettycomp
	@printf "$(1)$(clear_line)\n"
	@$(1)
	@printf "$(move_up)"
endef

RED		:= \033[31m
GREEN 	:= \033[32m
YELLOW	:= \033[33m
BLUE	:= \033[38;5;87m
MAGENTA := \033[35m
CYAN	:= \033[36m
RESET	:= \033[0m

#---------------------------------
#RULES

all	: $(NAME)
		@echo "a\\n"
		@echo "$(GREEN)Project built successfully !$(RESET)"

$(NAME) : $(OBJ) philo.h
		@echo "$(CYAN)Creating the executable...$(RESET)"
		@$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.c philo.h
		@echo "$(CYAN)Compiling...$(RESET) $<"
		$(call prettycomp, $(CMP) -c $(FLAGS) -o $@ $<)

clean :
		@rm -f $(OBJ)
		@echo "$(GREEN)Cleaned up the artifacts !$(RESET)"

fclean :
		@rm -f $(NAME) $(OBJ)
		@echo "$(MAGENTA)Cleaned up executable !$(RESET)"

re : fclean all
	
.PHONY : clean fclean re
