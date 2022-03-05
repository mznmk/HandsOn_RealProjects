/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:10:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 00:51:41 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

// ================================= library ================================ //

# include <stdio.h>
# include <time.h>
# include <sys/select.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <term.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/ioctl.h>

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

# define NEXT_WIDTH					BLOCK_SIZE
# define NEXT_HEIGHT				BLOCK_SIZE
# define SCORE_WIDTH				NEXT_WIDTH
# define SCORE_HEIGHT				2

# define FALL_TIME_MAX				0.5
# define FALL_SPEED_BASE			0.002
# define FALL_SPEED_MIN				1
# define FALL_SPEED_MAX				9

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

// --------------------------------- helper --------------------------------- //

typedef struct		s_cell
{
	char			c;
	int				char_color;
	int				back_color;
	int				attribute;
}					t_cell;

typedef struct		s_size
{
	int				width;
	int				height;
}					t_size;


typedef struct		s_coord
{
	int				y;
	int				x;
}					t_coord;

// --------------------------------- struct --------------------------------- //

typedef struct		s_envs
{
	t_size			term_size;
	t_size			back_size;
	t_size			field_size;
	t_size			field_size_max;
	t_size			field_size_min;
	t_size			next1_size;
	t_size			next2_size;
	t_size			score_size;
	t_coord			back_coord;
	t_coord			field_coord;
	t_coord			next1_coord;
	t_coord			next2_coord;
	t_coord			score_coord;
	t_coord			start_coord;
	struct termios	otty;
	struct termios	ntty;
}					t_envs;

typedef struct		s_vars
{
	t_cell			*field;
	t_cell			block_type[BLOCK_NUM][BLOCK_SIZE][BLOCK_SIZE];
	t_cell			block_now[BLOCK_SIZE][BLOCK_SIZE];
	int				prev_y;
	int				prev_x;
	int				now_y;
	int				now_x;
	int				now_rnd;
	t_cell			block_next1[BLOCK_SIZE][BLOCK_SIZE];
	int				next1_rnd;
	t_cell			block_next2[BLOCK_SIZE][BLOCK_SIZE];
	int				next2_rnd;
	int				score;
	double			fall_time_now;
	double			fall_time_max;
	double			fall_speed;
	struct timeval	start_time;
	struct timeval	prev_time;
	struct timeval	now_time;	
}					t_vars;

// ============================ global variable ============================= //

t_envs			e;
t_vars			v;

// ========================= prototype declaration ========================== //

// io.c
int				kbhit(void);
unsigned long	getch(void);

// init_env.c
void			init_envs(int argc, char **argv);

// init_vars.c
void			init_vars(void);

// init_term.c
void			init_tetris(int argc, char **argv);

// fin_term.c
void			fin_tetris(void);

// memory.c
void			allocate_memory(void);
void			deallocate_memory(void);
int				conv_field_coord(int y, int x);

// utils.c
int				choose_random(int size);
void			set_font_color_default(void);
void			set_font_color_basic(void);
int				is_filled_cell(t_cell cell);
int	check_range(t_cell cell, int y, int x);
int	check_cell(t_cell cell_self, int y, int x);

// draw_back.c
void			draw_back(void);

// draw_game.c

void			draw_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			draw_block_now(void);
void			draw_block_next(void);
void			draw_field(void);
void			draw_score(void);
void			clear_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			clear_block_prev(void);
void			clear_block_now(void);
void			clear_block_next(void);

// move_block.c
void			set_new_block_now(int type);
void			set_new_block_next(int type1, int type2);
void			rotate_block(int y, int x, bool rotate_right);
int				judge_collision(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x);
void			fix_block_to_field(int y, int x);
void			erase_lines(void);

// main.c
void			exit_tetris(void);

#endif
