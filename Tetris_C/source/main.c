/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 12:14:16 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		move_block(unsigned long keycode)
{
	// rotate block to left
	if (keycode == KEY_ARROW_UP || keycode == 'w' ||
		keycode == '0' || keycode == ',')
	{
		rotate_block(v.now_y, v.now_x, false);
	}
	// rotate block to right
	else if (keycode == '.')
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
	// v.score = 0;
	// v.prev_y = 0;
	// v.prev_x = 0;
	// v.now_y = e.start_coord.y;
	// v.now_x = e.start_coord.x;
	// v.fall_time_max = FALL_TIME_MAX;
	// v.fall_speed = FALL_SPEED_BASE;

	// [ draw game screen ]
	draw_background();
	// create next block
	rnd_now = choose_random(BLOCK_NUM);
	set_new_block_now(rnd_now);
	draw_block_now();
	rnd_next1 = choose_random(BLOCK_NUM);
	rnd_next2 = choose_random(BLOCK_NUM);
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
				rnd_next2 = choose_random(BLOCK_NUM);
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
	// [ initialize ]
	init_tetris(argc, argv);

	// [ execute tetris ]
	game_loop();

	// [ finalize ]
	fin_tetris();

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
	fin_tetris();

	// [ return (exit point) ]
	exit(0);
}
