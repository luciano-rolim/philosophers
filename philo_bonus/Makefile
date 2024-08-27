# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmeneghe <lmeneghe@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 12:12:03 by lmeneghe          #+#    #+#              #
#    Updated: 2024/08/27 10:23:39 by lmeneghe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME            = philo

# Compiler and Flags
CC              = gcc
CFLAGS          = -Wall -Wextra -Werror -pthread -O3

# Source Files
SRC_FILES       =	src/arg_check_extra.c src/arg_check.c src/basic_utils.c \
					src/cleaning.c src/main.c src/program_utils.c \
					src/start_philos.c src/start_variables.c \
					src/thread_philos.c src/thread_death.c src/thread_utils.c \
					src/time.c

# Object files
OBJS_DIR        = obj/
OBJS            = $(SRC_FILES:src/%.c=$(OBJS_DIR)%.o)

# Main rule: compile the program.
$(NAME):		$(OBJS)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Make instruction on how to compile .o if is not up to date
$(OBJS_DIR)%.o: src/%.c
				@mkdir -p $(OBJS_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@

# Standard all command
all:            $(NAME)

# Clean: removes all .o files, if the obj folder exists
clean:
				@if [ -d "$(OBJS_DIR)" ]; then find $(OBJS_DIR) -type f -name "*.o" -delete; fi

# Fclean: call clean + remove program file
fclean:         clean
				@rm -f $(NAME)

# Standard re command
re:             fclean all

# Standard .PHONY protection
.PHONY:         all clean fclean re

# Ensure "make" command behave as "make all"
.DEFAULT_GOAL := all
