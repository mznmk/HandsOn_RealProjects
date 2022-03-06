# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/06 11:37:57 by mmizuno           #+#    #+#              #
#    Updated: 2022/03/06 19:26:53 by mmizuno          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ================================= Variable ================================= #

NAME				= puzzle

PRJ_DIR				= ./

PUZZLE_DIR			= $(PRJ_DIR)
PUZZLE_INCDIR		= $(PUZZLE_DIR)include/
PUZZLE_SRCDIR		= $(PUZZLE_DIR)source/
PUZZLE_SRCNAME		= engine/io.c \
					  memory.c \
					  init_envs.c \
					  engine/init_game.c \
					  engine/fin_game.c \
					  game.c \
					  main.c
PUZZLE_SRCS			= $(addprefix $(PUZZLE_SRCDIR), $(PUZZLE_SRCNAME))
PUZZLE_OBJS			= $(PUZZLE_SRCS:.c=.o)

CC					= gcc
CFLAGS				= -Wall -Wextra -Werror -g -fsanitize=address
INCDIR				= -I $(PUZZLE_INCDIR)

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

$(NAME):			$(PUZZLE_OBJS)
					$(CC) $(CFLAGS) $(PUZZLE_OBJS) -o $(NAME)
					@echo "$(FNT_BOLD)$(CLR_GREEN)[ $(NAME) successfully compiled !! ]$(ESC_RESET)"

# ----------------------------------- all ------------------------------------ #

all: 				$(NAME)


# ---------------------------------- clean ----------------------------------- #

clean:
					$(RM) $(PUZZLE_OBJS)

# ---------------------------------- fclean ---------------------------------- #

fclean:				clean
					$(RM) $(NAME)

# ------------------------------------ re ------------------------------------ #

re:					fclean all

# ---------------------------------- .PHONY ---------------------------------- #

.PHONY:				all clean fclean re
