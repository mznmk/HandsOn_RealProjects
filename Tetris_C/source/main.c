/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 03:41:55 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/*!
** @brief	choose random type (for choose now/next block)	
** @param	use_seed	use "random seed"
** @return				index of block_type
*/
static int		choose_random_type(bool use_seed)
{
	// [ create random number ]
	int rnd;
	if (use_seed)
		srand((unsigned int)time(NULL));
	rnd = rand() % BLOCK_NUM;

	// [ return ]
	return rnd;
}

// -------------------------------------------------------------------------- //

static void		init_screen(void)
{
	// [ save terminal config (termcap) ]
	tinit();

	// [ set terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_off();
}

// -------------------------------------------------------------------------- //

static void		reset_screen(void)
{
	// [ reset terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_on();

	// [ load terminal config (termcap) ]
	tfinal();

	// [ deallocate memory ]
	deallocate_memory();
}

// -------------------------------------------------------------------------- //

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		move_block(unsigned long keycode)
{
	if (keycode == KEY_ARROW_UP || keycode == 'w' ||
		keycode == '0' || keycode == ',')
	{
		// rotate block to left
		rotate_block(v.now_y, v.now_x, false);
	}
	else if (keycode == '.')
	{
		// rotate block to right
		rotate_block(v.now_y, v.now_x, true);
	}
	else if (keycode == KEY_ARROW_DOWN || keycode == 's')
	{
		// move block to bottom
		while (judge_collision(v.block_now, v.now_y + 1, v.now_x) == 0)
			v.now_y++;
		// update score (drop point)
		v.score += v.now_y - v.prev_y;
		draw_score();
	}
	else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
	{
		// move block to left
		if (judge_collision(v.block_now, v.now_y, v.now_x - 1) == 0)
			v.now_x--;
	}
	else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
	{
		// move block to right
		if (judge_collision(v.block_now, v.now_y, v.now_x + 1) == 0)
			v.now_x++;
	}
}

// -------------------------------------------------------------------------- //

/*!
** @brief	game loop (tetris game loop)
*/
static void		game_loop(void)
{
	// [ variables ]
	int rnd_now, rnd_next1, rnd_next2;
	unsigned long	keycode;

	// [ set parameter ]
	v.score = 0;
	v.prev_y = 0;
	v.prev_x = 0;
	v.now_y = e.start_coord.y;
	v.now_x = e.start_coord.x;
	v.fall_time_max = LOOP_DURATION;

	// [ draw game screen ]
	draw_background();
	// create next block
	rnd_now = choose_random_type(true);
	set_new_block_now(rnd_now);
	draw_block_now();
	rnd_next1 = choose_random_type(false);
	rnd_next2 = choose_random_type(false);
	set_new_block_next(rnd_next1, rnd_next2);
	draw_block_next();
	draw_score();

	// measuring time
	gettimeofday(&v.prev_time, NULL);	// set prev_time

	// [ run game main routine ]
	while (42)
	{
		// store coords berore moving block
		v.prev_y = v.now_y;
		v.prev_x = v.now_x;
		
		// [ what keycode recieved from stdin ? ]
		if (kbhit())
		{
			keycode = getch();
			move_block(keycode);
		}

		// [ block fell regularly by gravity  ]
		// measuring time
		gettimeofday(&v.now_time, NULL);
		v.fall_time_now = (v.now_time.tv_sec - v.prev_time.tv_sec)
					+ (v.now_time.tv_usec - v.prev_time.tv_usec) / 1000000.0;
		// fell regularly
		if (v.fall_time_max < v.fall_time_now)
		{
			// can move block to bottom ?
			if (judge_collision(v.block_now,v.now_y + 1, v.now_x) == 0)
				// [ can move block to bottom ]
				v.now_y++;
			else
			{
				// [ can not move block to bottom  ]
				// game over ?
				if (v.now_y == e.start_coord.y)
					exit_tetris();
				// fix block !
				fix_block_to_field(v.now_y, v.now_x);
				// erase lines
				erase_lines();
				// create next block
				v.now_y = e.start_coord.y;
				v.now_x = e.start_coord.x;
				v.prev_y = e.start_coord.y;
				v.prev_x = e.start_coord.x;
				rnd_now = rnd_next1;
				set_new_block_now(rnd_now);
				draw_block_now();
				rnd_next1 = rnd_next2;
				rnd_next2 = choose_random_type(false);
				clear_block_next();
				set_new_block_next(rnd_next1, rnd_next2);
				draw_block_next();				
			}
			v.prev_time = v.now_time;
		}

		// [ block moved ? -> redraw block ]
		if (v.prev_y != v.now_y || v.prev_x != v.now_x)
		{
			// redraw block
			clear_block_prev();
			draw_block_now();
		}
	}
}

// -------------------------------------------------------------------------- //

/*!
** @brief	main (tetris entry point)
** @param	argc	argument count
** @param	argv	argument contents
** @return	status
*/
int				main(int argc, char **argv)
{
	// [ execute tetris ]
	// initialize tetris
	init_envs(argc, argv);
	allocate_memory();
	init_vars();
	init_screen();
	// execute tetris
	game_loop();
	// finalize tetris
	reset_screen();

	// [ return ]
	return 0;
}

// ========================================================================== //

/*!
** @brief	exit tetris (other exit point)
** @return	status
*/
void			exit_tetris(void)
{
	// [ finalize tetris ]
	reset_screen();

	// [ return (exit point) ]
	exit(0);
}
