/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tetris.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 22:10:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 05:11:06 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TETRIS_H
# define TETRIS_H

// ================================= library ================================ //

# include <ctype.h>
# include <stdio.h>
# include <time.h>

// ================================== macro ================================= //

# define clear_screen()				printf("\033[2J")
# define set_position(y, x)			printf("\033[%d;%dH", (y)+1, (x)*2+1)
# define set_char_color(n)			printf("\033[3%dm", (n))
# define set_back_color(n)			printf("\033[4%dm", (n))
# define set_attribute(n)			printf("\033[%dm", (n))
# define cursol_on()				printf("\033[?25h")
# define cursol_off()				printf("\033[?25l")

// ============================= const variable ============================= //

# define FLD_WIDTH					20
# define FLD_HEIGHT					30
# define BLOCK_SIZE					4
# define BLOCK_NUM					7

// -------------------------------- message --------------------------------- //


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

// ================================= struct ================================= //

typedef struct	s_cell
{
	char	c;
	int		char_color;
	int		back_color;
	int		attribute;
}				t_cell;

// --------------------------------- struct --------------------------------- //

typedef struct	s_vars
{
	t_cell	block_type[BLOCK_NUM][BLOCK_SIZE][BLOCK_SIZE];
	t_cell	field[FLD_HEIGHT][FLD_WIDTH];
	t_cell	block[BLOCK_SIZE][BLOCK_SIZE];
}				t_vars;

// ========================= prototype declaration ========================== //

int wait(int msec);

void	init_screen(void);
void	reset_screen(void);

void	init_vars(t_vars *v);

int check_range(t_cell cell, int y, int x);
int	print_cell(t_cell cell, int y, int x);
int	clear_cell(t_cell cell, int y, int x);
int		print_block(t_vars *v, int y, int x);
int		clear_block(t_vars *v, int y, int x);
void	copy_block(t_vars *v, t_cell src[BLOCK_SIZE][BLOCK_SIZE]);

#endif
