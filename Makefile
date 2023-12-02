# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oscarmathot <oscarmathot@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/09 01:41:47 by oscarmathot       #+#    #+#              #
#    Updated: 2023/12/02 23:30:17 by oscarmathot      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#---------------------------------
#VARIABLES

NAME 	:= philo
SRC 	:= main.c initialize.c threads.c helpers.c routines.c observer.c
SUBDIR	:= srcs/
SRCS	:= $(addprefix $(SUBDIR),$(SRC))
OBJ 	:= $(SRCS:.c=.o)
LIBFT_A	:= lib/libft/libft.a
CMP		:= gcc
FLAGS 	:= -Werror -Wall -Wextra -pthread -fsanitize=thread -I lib

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

$(NAME) : $(OBJ) $(LIBFT_A) philo.h
		@echo "$(CYAN)Creating the executable...$(RESET)"
		@$(CC) $(FLAGS) $(OBJ) $(LIBFT_A) -o $(NAME)

%.o : %.c philo.h
		@echo "$(CYAN)Compiling...$(RESET) $<"
		$(call prettycomp, $(CMP) -c $(FLAGS) -o $@ $<)

$(LIBFT_A) : 
		@echo "$(BLUE)Building libft library...$(RESET)\n"
		$(call prettycomp, @make -C lib/libft)

clean :
		@rm -f $(OBJ) ./lib/libft/libft.a
		@echo "$(GREEN)Cleaned up the artifacts !$(RESET)"

fclean :
		@rm -f $(NAME) $(OBJ)
		@echo "$(MAGENTA)Cleaned up executable !$(RESET)"

hardclean : 
		@make fclean
		cd ./lib/libft && make clean
		cd ./lib/libft && make fclean
		@echo "$(MAGENTA)Cleaned up all built files!$(RESET)"

re : fclean all
	
.PHONY : clean fclean re hardclean
