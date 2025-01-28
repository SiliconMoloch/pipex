# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/18 18:29:37 by yabokhar          #+#    #+#              #
#    Updated: 2025/01/24 18:17:08 by yabokhar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS    =    pipex.c        \
            pipex_utils.c	\
	    libft/ft_bzero.c	\
	    libft/ft_calloc.c	\
	    libft/ft_split.c	\
	    libft/ft_strjoin.c	\
	    libft/ft_strlen.c	\
	    libft/ft_strncmp.c	\
	    libft/ft_str_is_space.c

BNS	=	pipex_bonus/pipex_bonus.c	\
		pipex_bonus/pipex_utils_bonus.c	\
		pipex_bonus/pipex_utils_bis_bonus.c	\
		pipex_bonus/libft_bonus/ft_bzero_bonus.c	\
		pipex_bonus/libft_bonus/ft_calloc_bonus.c	\
		pipex_bonus/libft_bonus/ft_split_bonus.c	\
		pipex_bonus/libft_bonus/ft_strjoin_bonus.c	\
		pipex_bonus/libft_bonus/ft_strlen_bonus.c	\
		pipex_bonus/libft_bonus/ft_strncmp_bonus.c	\
		pipex_bonus/libft_bonus/ft_str_is_space_bonus.c	\
		pipex_bonus/get_next_line/get_next_line.c	\
		pipex_bonus/get_next_line/get_next_line_utils.c	\
		pipex_bonus/ft_printf/basic_tools.c		\
		pipex_bonus/ft_printf/flags_tools.c		\
		pipex_bonus/ft_printf/ft_printf.c		\
		pipex_bonus/ft_printf/handle_c.c		\
		pipex_bonus/ft_printf/handle_d_i.c		\
		pipex_bonus/ft_printf/handle_flags.c		\
		pipex_bonus/ft_printf/handle_s.c

OBJ_DIR =   .objects/

OBJS	=	${SRCS:%.c=${OBJ_DIR}%.o}

B_OBJS	=	${BNS:%.c=${OBJ_DIR}%.o}

HEAD	=	pipex.h

NAME	=	pipex

CC	=	cc

FLAGS	=	-Wall -Wextra -Werror

all	:	${NAME}

${OBJS} :   ${OBJ_DIR}%.o : %.c ${HEAD} Makefile
	mkdir -p $(dir $@)
	${CC} ${FLAGS} -c $< -o $@

${NAME}	:	${OBJ_DIR} ${OBJS} 
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${OBJ_DIR}  :
	mkdir -p ${OBJ_DIR}

bonus	:
	make SRCS="${BNS}"

clean	:
	rm -rf ${OBJ_DIR} #${B_OJS}
	find . -type f -name "*.o" -delete

fclean	:	clean
	rm -f ${NAME} ${B_OBJS}

re	:	fclean all

.PHONY	:	all clean fclean re bonus
