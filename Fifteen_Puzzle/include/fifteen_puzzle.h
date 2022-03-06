/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifteen_puzzle.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:50:58 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 19:11:00 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIFTEEN_PUZZLE_H
# define FIFTEEN_PUZZLE_H

// ================================= library ================================ //

# include <term.h>
# include <signal.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>

// ================================== macro ================================= //

# define clear_terminal()			printf("\033[2J")
# define set_position(y, x)			printf("\033[%d;%dH", (y)+1, (x)*2+1)
# define set_char_color(n)			printf("\033[3%dm", (n))
# define set_back_color(n)			printf("\033[4%dm", (n))
# define set_attribute(n)			printf("\033[%dm", (n))
# define cursol_on()				printf("\033[?25h")
# define cursol_off()				printf("\033[?25l")

// ============================= const variable ============================= //

# define GRID_SIZE_MIN				3
# define GRID_SIZE_MAX				9
# define GRID_HEIGHT				4
# define GRID_WIDTH					4
# define GRID_COORD_Y				1
# define STAT_HEIGHT				1

# define BLANK_NUMBER				0

// --------------------------------- color ---------------------------------- //

# define CLR_BLACK					0
# define CLR_RED					1
# define CLR_GREEN					2
# define CLR_YELLOW					3
# define CLR_BLUE					4
# define CLR_MAGENTA				5
# define CLR_CYAN					6
# define CLR_WHITE					7
# define CLR_DEFAULT				9

// ------------------------------- attribute -------------------------------- //

# define ATR_NORMAL					0
# define ATR_BLIGHT					1
# define ATR_DIM					2
# define ATR_UNDERBAR				4
# define ATR_BLINK					5
# define ATR_REVERSE				7
# define ATR_HIDE					8
# define ATR_STRIKE					9

// ---------------------------------- key ----------------------------------- //

# define KEY_ARROW_UP				0x415B1B
# define KEY_ARROW_DOWN				0x425B1B
# define KEY_ARROW_RIGHT			0x435B1B
# define KEY_ARROW_LEFT				0x445B1B

// ================================= struct ================================= //

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_size
{
	int				height;
	int				width;
}					t_size;

// -------------------------------------------------------------------------- //

typedef struct		s_envs
{
	t_size			grid_size;
	t_size			back_size;
	t_size			stat_size;
	t_coord			grid_coord;
	t_coord			back_coord;
	t_coord			stat_coord;
	int				cell_size;
	struct termios	otty;
	struct termios	ntty;
}					t_envs;

typedef struct		s_vars
{
	int				*grid;
	t_coord			black_coord;
}					t_vars;

// ============================ global variable ============================= //

t_envs			e;
t_vars			v;

// ========================= prototype declaration ========================== //

// io.c
int     		kbhit(void);
unsigned long	getch(void);

// memory.c
void			allocate_memory(void);
void			deallocate_memory(void);

// init_game.c
void			init_game(int argc, char **argv);

// fin_game.c
void			fin_game(void);

// init_envs.c
void			init_envs(int argc, char **argv);

// utils.c
// int				can_swap_cell(int y, int x);

// game.c
int				conv_grid_coord(int y, int x);
void			draw_back(void);
void			draw_number(void);
void			draw_stat(void);
void			find_blank_cell(void);
void			swap_cell(int coord_1d_1, int coord_1d_2);
void			set_number_to_grid(void);

// main.c
void			exit_game(void);

#endif