/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bomberman.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 10:29:07 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/27 20:59:55 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOMBERMAN_H
# define BOMBERMAN_H

// ================================= library ================================ //

# include <term.h>
# include <signal.h>
# include <sys/select.h>
# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>
# include <time.h>
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

# define MAP_HEIGHT					13
# define MAP_WIDTH					31
# define SCREEN_WIDTH				16

# define PLAYER_Y					1
# define PLAYER_X					1
# define PLAYER_LIFE				1
# define ENEMY_COUNT				5
# define ENEMY_LIFE					1
# define SOFTBLOCK_COUNT			20
# define SOFTBLOCK_LIFE				1
# define DOOR_LIFE					1

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

// ================================== enum ================================== //

enum				e_status
{
	TITLE,
	GAME_PLAY,
	GAME_CLEAR,
	GAME_OVER
};

enum				e_field
{
	FIELD,
	HARD_BLOCK,
	SOFT_BLOCK
};

// ================================= struct ================================= //

// --------------------------------- helper --------------------------------- //

typedef struct		s_chara
{
	int				x;
	int				y;
	int				life;
}					t_chara;



// --------------------------------- struct --------------------------------- //

typedef struct		s_envs
{
	struct termios	otty;
	struct termios	ntty;
}					t_envs;

typedef struct		s_vars
{
	int				map[MAP_HEIGHT][MAP_WIDTH];
	t_chara			player;
	t_chara			enemy[ENEMY_COUNT];
	t_chara			softblock[SOFTBLOCK_COUNT];
	t_chara			door;
	int				status;
}					t_vars;


// ============================ global variable ============================= //

t_envs				e;
t_vars				v;

// ========================= prototype declaration ========================== //

// io.c
int     		kbhit(void);
unsigned long	getch(void);

// memory.c
void			allocate_memory(void);
void			deallocate_memory(void);

// collision.c
bool			is_in_map(int y, int x);
bool			is_hard_block(int y, int x);
bool			is_player(int y, int x);
bool			is_enemy(int y, int x);
bool			is_softblock(int y, int x);
bool			is_door(int y, int x);

// init_envs.c
void			init_envs(int argc, char **argv);

// init_vars.c
void			init_vars(void);

// init_game.c
void			init_game(int argc, char **argv);

// fin_game.c
void			fin_game(void);

// draw_back.c
void			draw_back(void);
void			draw_chara(void);

// main.c
void			exit_game(void);

#endif