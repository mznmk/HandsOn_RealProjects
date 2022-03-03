/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 04:02:20 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/*!
** @brief	choose random type (for choose now/next block)	
** @param	use_seed	use "random seed"
** @return				index of block_type
*/
static int		choose_random_type(bool change_seed)
{
	// [ create random number ]
	int rnd;
	if (change_seed)
		srand((unsigned int)time(NULL));
	rnd = rand() % BLOCK_NUM;

	// [ return ]
	return rnd;
}

/*!
** @brief	assign process, when key is pressed
** @param	v		tetris variables (structure)
** @param	keycode	pressed keycode
*/
static void		move_block(t_vars *v, unsigned long keycode)
{
	if (keycode == KEY_ARROW_UP || keycode == 'w' ||
		keycode == '0' || keycode == ',')
	{
		// rotate block to left
		rotate_block(v, v->now_y, v->now_x, false);
	}
	else if (keycode == '.')
	{
		// rotate block to right
		rotate_block(v, v->now_y, v->now_x, true);
	}
	else if (keycode == KEY_ARROW_DOWN || keycode == 's')
	{
		// move block to bottom
		while (check_grid(v, v->now_y + 1, v->now_x) == 0)
			v->now_y++;
		// update score (drop point)
		v->score += v->now_y - v->prev_y;
		draw_score(v);
	}
	else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
	{
		// move block to left
		if (check_grid(v, v->now_y, v->now_x - 1) == 0)
			v->now_x--;
	}
	else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
	{
		// move block to right
		if (check_grid(v, v->now_y, v->now_x + 1) == 0)
			v->now_x++;
	}
}

/*!
** @brief	game loop (tetris game loop)
** @param	v		tetris variables (structure)
*/
static void	game_loop(t_vars *v)
{
	// [ variables ]
	int rnd_now, rnd_next;
	unsigned long	keycode;

	// [ set parameter ]
	v->score = 0;
	v->prev_y = 0;
	v->prev_x = 0;
	v->now_y = START_YCOORD;
	v->now_x = START_XCOORD;

	// [ draw game screen ]
	draw_background();
	// create next block
	rnd_now = choose_random_type(true);
	set_block_now(v, rnd_now);
	draw_block_now(v);
	rnd_next = choose_random_type(false);
	set_block_next(v, rnd_next);
	draw_block_next(v);
	draw_score(v);

	// measuring time
	gettimeofday(&v->prev_time, NULL);	// set prev_time

	// [ run game main routine ]
	while (42)
	{
		// store coords berore moving block
		v->prev_y = v->now_y;
		v->prev_x = v->now_x;
		
		// [ what keycode recieved from stdin ? ]
		if (kbhit())
		{
			keycode = getch();
			move_block(v, keycode);
		}

		// [ block fell regularly by gravity :) ]
		// measuring time ...
		gettimeofday(&v->now_time, NULL);
		v->duration = (v->now_time.tv_sec - v->prev_time.tv_sec)
				+ (v->now_time.tv_usec - v->prev_time.tv_usec) / 1000000.0;
		// fell regularly
		if (LOOP_DURATION < v->duration)
		{
			// can move block to bottom ?
			if (check_grid(v, v->now_y + 1, v->now_x) == 0)
				// [ can move block to bottom ]
				v->now_y++;
			else
			{
				// [ can not move block to bottom  ]
				// game over ?
				if (v->now_y == START_YCOORD)
					exit_tetris();
				// fix block !
				fix_block_to_grid(v, v->now_y, v->now_x);
				// erase lines
				erase_lines(v);
				// create next block
				v->now_y = START_YCOORD;
				v->now_x = START_XCOORD;
				v->prev_y = START_YCOORD;
				v->prev_x = START_XCOORD;
				rnd_now = rnd_next;
				set_block_now(v, rnd_now);
				draw_block_now(v);
				rnd_next = choose_random_type(true);
				clear_block_next(v);
				set_block_next(v, rnd_next);
				draw_block_next(v);				
			}
			v->prev_time = v->now_time;
		}

		// [ block moved ? -> redraw block ]
		if (v->prev_y != v->now_y || v->prev_x != v->now_x)
		{
			// redraw block
			clear_block_prev(v);
			draw_block_now(v);
		}
	}
}

/*!
** @brief	exit tetris (other exit point)
** @return	status
*/
int		exit_tetris(void)
{
	// [ finalize tetris ]
	reset_screen();

	// [ return (exit point) ]
	exit(0);
}

/*!
** @brief	main (tetris entry point)
** @param	argc	argument count
** @param	argv	argument contents
** @return	status
*/
int	main(int argc, char **argv)
{
	// [ variables ]
	(void)argc;
	(void)argv;
	t_vars	v;

	// [ execute tetris ]
	// initialize tetris
	init_vars(&v);
	init_screen();
	// execute tetris
	game_loop(&v);
	// finalize tetris
	reset_screen();

	// [ return ]
	return 0;
}