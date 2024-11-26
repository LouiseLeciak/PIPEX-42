# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lleciak <lleciak@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/25 18:39:11 by lleciak           #+#    #+#              #
#    Updated: 2024/03/25 09:30:23 by lleciak          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#########################################
##ARGUMENTS

NAME		= pipex
CFLAGS		= -Wall -Werror -Wextra -g3
CC			= cc
RM			= rm -f

HEAD		= ./utils/headers/ft_printf.h ./utils/headers/pipex.h

BUILD_DIR		= ./objects

# CONST
CONST_FILES		= utils.c ft_split.c path.c 
CONST_OBJECTS	= $(patsubst %.c, %.o, $(addprefix $(BUILD_DIR)/, $(CONST_FILES)))

# PRINTF		  
PRINTF_FILES	= ./utils/ft_printf/ft_printf.c ./utils/ft_printf/ft_char_str.c \
				  ./utils/ft_printf/ft_putnbr.c
PRINTF_OBJECTS 	= $(PRINTF_FILES:.c=.o)

# GNL	  
GNL_FILES	= ./utils/get_next_line/get_next_line.c ./utils/get_next_line/get_next_line_utils.c
GNL_OBJECTS 	= $(GNL_FILES:.c=.o)

# MANDATORY
MANDATORY		= pipex.c exec.c
MANDATORY_OBJ	= $(patsubst %.c, %.o, $(addprefix $(BUILD_DIR)/, $(MANDATORY)))

# BONUS
BONUS_BUILD_DIR	= ./objects_bonus
BONUS_FILES		= pipex_bonus.c here_doc.c exec_bonus.c
BONUS_OBJ	= $(patsubst %.c, %.o, $(addprefix $(BONUS_BUILD_DIR)/, $(BONUS_FILES)))

##########################################
##RULES

all:	${NAME}

%.o: %.c 
		${CC} ${CFLAGS} -c -I ./ $< -o $@

$(BUILD_DIR)/%.o:%.c
				@mkdir -p $(BUILD_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@
				
$(BONUS_BUILD_DIR)/%.o:%.c
				@mkdir -p $(BONUS_BUILD_DIR)
				@$(CC) $(CFLAGS) -c $< -o $@
				
${NAME}: ${PRINTF_OBJECTS} ${GNL_OBJECTS} ${CONST_OBJECTS} ${MANDATORY_OBJ} ${HEAD} 
		@$(CC) $(CFLAGS) -I ./headers -o $(NAME) $(PRINTF_OBJECTS) ${GNL_OBJECTS} $(CONST_OBJECTS) $(MANDATORY_OBJ)
		@echo "\033c\033[0;32mMandatory part compiled 🥳\033[0;37m"

clean:	
		@$(RM) $(CONST_OBJECTS) $(MANDATORY_OBJ) $(BONUS_OBJ) $(PRINTF_OBJECTS) ${GNL_OBJECTS}
						@echo "\033[0;33m🧽Cleaned🫧\033[0;37m"

fclean: clean
		@$(RM) $(NAME)

bonus: fclean ${PRINTF_OBJECTS} ${GNL_OBJECTS} ${CONST_OBJECTS} ${BONUS_OBJ} ${HEAD}
		@$(CC) $(CFLAGS) -I ./headers -o $(NAME) $(PRINTF_OBJECTS) ${GNL_OBJECTS} $(CONST_OBJECTS) $(BONUS_OBJ)
		@echo "\033c\033[0;32mBonus part compiled 🥳\033[0;37m"
		
re: fclean all

.PHONY: all clean fclean re bonus