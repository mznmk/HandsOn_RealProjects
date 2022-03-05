/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 23:18:56 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		press_key(unsigned long keycode)
{
	// rotate block to left
	if (keycode == KEY_ARROW_UP || keycode == 'w' ||
		keycode == '0' || keycode == 'j')
	{
		rotate_block(v.now_y, v.now_x, false);
	}
	// rotate block to right
	else if (keycode == '.' || keycode == 'k')
	{
		rotate_block(v.now_y, v.now_x, true);
	}
	// move block to bottom
	else if (keycode == KEY_ARROW_DOWN || keycode == 's')
	{
		while (judge_collision(v.block_now, v.now_y + 1, v.now_x) == 0)
			v.now_y++;
		// update score (drop point)
		v.score += v.now_y - v.prev_y;
		draw_score();
	}
	// move block to left
	else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
	{
		if (judge_collision(v.block_now, v.now_y, v.now_x - 1) == 0)
			v.now_x--;
	}
	// move block to right
	else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
	{
		if (judge_collision(v.block_now, v.now_y, v.now_x + 1) == 0)
			v.now_x++;
	}
}

static void		set_start_block(void)
{
	// draw_back
	draw_back();
	// set/draw now block
	v.now_rnd = choose_random(BLOCK_NUM);
	set_new_block_now(v.now_rnd);
	draw_block_now();
	// set/draw next block
	v.next1_rnd = choose_random(BLOCK_NUM);
	v.next2_rnd = choose_random(BLOCK_NUM);
	set_new_block_next(v.next1_rnd, v.next2_rnd);
	draw_block_next();
	// draw score
	draw_score();
}

static void		complete_fall_block(void)
{
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
	// set/draw now block
	v.now_rnd = v.next1_rnd;
	set_new_block_now(v.now_rnd);
	draw_block_now();
	// set/draw next block
	v.next1_rnd = v.next2_rnd;
	v.next2_rnd = choose_random(BLOCK_NUM);
	clear_block_next();
	set_new_block_next(v.next1_rnd, v.next2_rnd);
	draw_block_next();
}

static void		move_block(void)
{
	// [ move block ]
	clear_block_prev();
	draw_block_now();
}

/*!
** @brief	game loop (tetris game loop)
*/
static void		game_loop(void)
{
	// [ variables ]
	unsigned long	keycode;

	// [ run game main routine ]
	// draw game screen
	set_start_block();
	// measuring time (set prev_time)
	gettimeofday(&v.prev_time, NULL);
	// run game main routine
	while (42)
	{
		// [ store coords berore moving block ]
		v.prev_y = v.now_y;
		v.prev_x = v.now_x;

		// [ what keycode recieved from stdin ? ]
		if (kbhit())
		{
			keycode = getch();
			press_key(keycode);
		}

		// [ fall block regularly by gravity ]
		// measuring time (calc fall time)
		gettimeofday(&v.now_time, NULL);
		v.fall_time_now = (v.now_time.tv_sec - v.prev_time.tv_sec)
					+ (v.now_time.tv_usec - v.prev_time.tv_usec) / 1000000.0;
		// complete to fall block ?
		if (v.fall_time_max < v.fall_time_now)
		{
			// can move block to bottom ? -> move next block
			if (judge_collision(v.block_now,v.now_y + 1, v.now_x) == 0)
				v.now_y++;
			else
				complete_fall_block();
			// measuring time (set prev_time)
			v.prev_time = v.now_time;
		}

		// [ block moved ? -> redraw block ]
		if (v.prev_y != v.now_y || v.prev_x != v.now_x)
			move_block();
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
	// [ initialize ]
	init_tetris(argc, argv);

	// [ execute tetris ]
	game_loop();

	// [ finalize ]
	fin_tetris();

	// [ return ]
	return 0;
}

// -------------------------------------------------------------------------- //

/*!
** @brief	exit tetris (other exit point)
** @return	status
*/
void			exit_tetris(void)
{
	// [ finalize tetris ]
	fin_tetris();

	// [ return (exit point) ]
	exit(0);
}
