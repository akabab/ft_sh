# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/11/26 16:39:11 by ycribier          #+#    #+#              #
#    Updated: 2015/02/18 14:43:06 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
FLAGS			=	-O2 -Wall -Wextra -Werror
NAME			=	ft_minishell1
LIB				=	libft/libft.a
LIB_PATH		=	libft/
INCLUDES		=	-I $(LIB_PATH)./includes -I ./includes
SRCS			=	srcs/minishell.c				\
					srcs/cmd.c						\
					srcs/env.c						\
					srcs/env_tools.c				\
					srcs/cd.c
OBJS			=	$(SRCS:srcs/%.c=objs/%.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: obj $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME) ] $(SUCCESS)

$(LIB):
	@make -C $(LIB_PATH)

obj:
	@mkdir -p objs

objs/%.o: srcs/%.c ./includes/minishell.h
	@$(CC) $(FLAGS) -c -o $@ $< $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJS)
	@rm -rf objs
	@echo "Cleaning" [ $(NAME) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME) ] $(OK)

re: fclean all

.PHONY: clean all re fclean
