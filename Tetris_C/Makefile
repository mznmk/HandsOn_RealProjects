# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/01 13:17:41 by mmizuno           #+#    #+#              #
#    Updated: 2022/03/06 03:10:08 by mmizuno          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Variable ================================= #

NAME				= tetris

PRJ_DIR				= ./

TETRIS_DIR			= $(PRJ_DIR)
TETRIS_INCDIR		= $(TETRIS_DIR)include/
TETRIS_SRCDIR		= $(TETRIS_DIR)source/
TETRIS_SRCNAME		= io.c \
					  memory.c \
					  init_envs.c \
					  init_vars.c \
					  init_tetris.c \
					  fin_tetris.c \
					  utils.c \
					  judge.c \
					  draw_back.c \
					  draw_game.c \
					  move_block.c \
					  main.c
TETRIS_SRCS			= $(addprefix $(TETRIS_SRCDIR), $(TETRIS_SRCNAME))
TETRIS_OBJS			= $(TETRIS_SRCS:.c=.o)

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -g -fsanitize=address
INCDIR				= -I $(TETRIS_INCDIR)

RM					= rm -f

# ---------------------------------- color ----------------------------------- #

ESC_RESET			= \033[0m
FNT_BOLD			= \033[1m
FNT_FINE			= \033[2m
FNT_ITALIC			= \033[3m
FNT_ULINE			= \033[4m
CLR_BLACK			= \033[38;5;00m
CLR_RED				= \033[38;5;01m
CLR_GREEN			= \033[38;5;02m
CLR_YELLOW			= \033[38;5;03m
CLR_BLUE			= \033[38;5;04m
CLR_MAGENTA			= \033[38;5;05m
CLR_CYAN			= \033[38;5;06m
CLR_WHITE			= \033[38;5;07m
CLR_PINK			= \033[38;5;213m

# =============================== Make Command =============================== #

# ---------------------------------- .c.o ------------------------------------ #

.c.o:
					$(CC) $(CFLAGS) $(INCDIR) -c $< -o $(<:.c=.o)

# --------------------------------- $(NAME) ---------------------------------- #

$(NAME):			$(TETRIS_OBJS)
					$(CC) $(CFLAGS) $(TETRIS_OBJS) -o $(NAME)
					@echo "$(FNT_BOLD)$(CLR_GREEN)[ $(NAME) successfully compiled !! ]$(ESC_RESET)"

# ----------------------------------- all ------------------------------------ #

all: 				$(NAME)


# ---------------------------------- clean ----------------------------------- #

clean:
					$(RM) $(TETRIS_OBJS)

# ---------------------------------- fclean ---------------------------------- #

fclean:				clean
					$(RM) $(NAME)

# ------------------------------------ re ------------------------------------ #

re:					fclean all

# ---------------------------------- .PHONY ---------------------------------- #

.PHONY:				all clean fclean re
