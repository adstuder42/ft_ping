# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adstuder <adstuder@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 12:29:40 by adstuder          #+#    #+#              #
#    Updated: 2021/03/04 17:59:50 by adstuder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all, clean, fclean, re, lib, $(NAME)

# **************************************************************************** #
#                                SOURCE FILES                                  #
# **************************************************************************** #

SRCS_PATH  = srcs/
OBJS_PATH  = objs/

NAME       = ft_ping
SRC_NAME   = main.c networking.c utilities.c init_set.c send_ping.c 
OBJ_NAME   = $(SRC_NAME:.c=.o)
SRCS       = $(addprefix $(SRCS_PATH),$(SRC_NAME))
OBJS       = $(addprefix $(OBJS_PATH),$(OBJ_NAME))

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all           : $(NAME) 

CC            = gcc -O3
CFLAGS        = -Wall -Wextra -Werror

clean         :
	@rm -rf objs
	@printf "make: objs cleaned\\n"

fclean        : clean
	@rm -rf $(NAME)
	@printf "make: programs cleaned\\n"

re            : fclean all

# **************************************************************************** #
#                                COMPILATION                                   #
# **************************************************************************** #

$(OBJS_PATH)%.o : $(SRCS_PATH)%.c Makefile includes/ft_ping.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf "\033[K"
	@printf "make: compiling $<\\r"

$(NAME)         : $(OBJS)
	@printf "\033[K"
	@$(CC) $(CFLAGS) $^ -o $(NAME)
	@printf "\033[37;1m-- $(NAME)        [ \033[32;1mOK\033[37;1m ]\033[0m\\n"
	@sudo setcap cap_net_raw=pe ft_ping

# ***************************************************************************** #