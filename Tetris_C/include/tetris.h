/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:10:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 06:31:32 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

// ============================ global variable ============================= //

// int				errno;
struct termios	otty;
struct termios	ntty;	

// ================================= library ================================ //

# include <stdio.h>
# include <time.h>
# include <sys/select.h>
# include <unistd.h>
// # include <errno.h>
// # include <sys/types.h>
# include <signal.h>
# include <stdlib.h>
// # include <termios.h>
# include <term.h>
# include <sys/time.h>
# include <stdbool.h>

// ================================== macro ================================= //

# define clear_terminal()			printf("\033[2J")
# define set_position(y, x)			printf("\033[%d;%dH", (y)+1, (x)*2+1)
# define set_char_color(n)			printf("\033[3%dm", (n))
# define set_back_color(n)			printf("\033[4%dm", (n))
# define set_attribute(n)			printf("\033[%dm", (n))
# define cursol_on()				printf("\033[?25h")
# define cursol_off()				printf("\033[?25l")

// ============================= const variable ============================= //

# define BLOCK_SIZE					4
# define BLOCK_NUM					7

# define GRID_WIDTH					10
# define GRID_HEIGHT				20
# define NEXT_WIDTH					BLOCK_SIZE
# define NEXT_HEIGHT				BLOCK_SIZE
# define SCORE_WIDTH				BLOCK_SIZE
# define SCORE_HEIGHT				1
# define BACK_WIDTH					GRID_WIDTH + BLOCK_SIZE + 3
# define BACK_HEIGHT				GRID_HEIGHT + 2

# define GRID_YCOORD				1
# define GRID_XCOORD				1
# define NEXT_YCOORD				1
# define NEXT_XCOORD				GRID_WIDTH + 2
# define SCORE_YCOORD				NEXT_YCOORD + BLOCK_SIZE + 1
# define SCORE_XCOORD				GRID_WIDTH + 2
# define BACK_YCOORD				0
# define BACK_XCOORD				0

# define START_YCOORD				0
# define START_XCOORD				GRID_WIDTH/2 - 1
# define LOOP_DURATION				0.5

// --------------------------------- score ---------------------------------- //

# define ERASE_1LINE				40
# define ERASE_2LINE				100
# define ERASE_3LINE				300
# define ERASE_4LINE				1200

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

// --------------------------------attribute -------------------------------- //

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

# define KEY_SPACE					0x20

# define KEY_EOT					0x4
# define KEY_RETURN					0xA

# define KEY_BACKSPACE				0x7F
# define KEY_DELETE					0x7E335B1B

# define KEY_HOME					0x485B1B
# define KEY_END					0x465B1B

// ================================= struct ================================= //

typedef struct		s_cell
{
	char			c;
	int				char_color;
	int				back_color;
	int				attribute;
}					t_cell;

typedef struct		s_vars
{
	t_cell			grid[GRID_HEIGHT][GRID_WIDTH];
	t_cell			block_type[BLOCK_NUM][BLOCK_SIZE][BLOCK_SIZE];
	t_cell			block_now[BLOCK_SIZE][BLOCK_SIZE];
	int				prev_y;
	int				prev_x;
	int				now_y;
	int				now_x;
	int				now_rnd;
	t_cell			block_next[BLOCK_SIZE][BLOCK_SIZE];
	int				next_rnd;
	int				score;
	double			duration;
	struct timeval	start_time;
	struct timeval	prev_time;
	struct timeval	now_time;	
}					t_vars;

// ========================= prototype declaration ========================== //

// io.c
int				kbhit(void);
unsigned long	getch(void);
int				tinit(void);
int				tfinal(void);

// init.c
void			init_vars(t_vars *v);

// utils.c
int				is_filled_cell(t_cell cell);
int	check_range(t_cell cell, int y, int x);
int	check_cell(t_vars *v, t_cell cell_self, int y, int x);

// canvas.c
void			draw_background(void);
void			draw_score(t_vars *v);

int				draw_cell(t_cell cell, int y, int x);
int				draw_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			draw_block_now(t_vars *v);
void			draw_block_next(t_vars *v);
void			draw_grid(t_vars *v);

int				clear_cell(t_cell cell, int y, int x);
void			clear_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			clear_block_prev(t_vars *v);
void			clear_block_now(t_vars *v);
void			clear_block_next(t_vars *v);

// block.c
void			set_new_block_now(t_vars *v, int type);
void			set_new_block_next(t_vars *v, int type);
void			rotate_block(t_vars *v, int y, int x, bool turn_right);

int				judge_collision(t_vars *v,
							t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			fix_block_to_grid(t_vars *v, int y, int x);
void			erase_lines(t_vars *v);

// main.c
int				exit_tetris(void);

#endif
