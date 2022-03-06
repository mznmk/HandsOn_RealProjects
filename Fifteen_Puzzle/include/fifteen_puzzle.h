/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifteen_puzzle.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:50:58 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 11:51:14 by mmizuno          ###   ########.fr       */
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

// ================================== macro ================================= //

# define clear_terminal()			printf("\033[2J")
# define set_position(y, x)			printf("\033[%d;%dH", (y)+1, (x)*2+1)
# define set_char_color(n)			printf("\033[3%dm", (n))
# define set_back_color(n)			printf("\033[4%dm", (n))
# define set_attribute(n)			printf("\033[%dm", (n))
# define cursol_on()				printf("\033[?25h")
# define cursol_off()				printf("\033[?25l")

// ============================= const variable ============================= //



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

typedef struct		s_envs
{
	struct termios	otty;
	struct termios	ntty;
}					t_envs;


// ============================ global variable ============================= //

t_envs			e;

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


// main.c
void			exit_game(void);

#endif