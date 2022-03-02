/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/03 05:19:30 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/*!
** @brief	game loop (tetris game loop)
** @param	v		tetris variables (structure)
** @return	status
*/
static void	game_loop(t_vars *v)
{
	// [ variables ]
	int rnd_now, rnd_next;
	unsigned long	keycode;

	// [ set parameter ]
	v->prev_y = 0;
	v->prev_x = 0;
	v->now_y = START_YCOORD;
	v->now_x = START_XCOORD;
	v->next_y = START_YCOORD;
	v->next_x = GRID_WIDTH + 1;

	// [ draw game screen ]
	// create next block
	rnd_now = rand() % BLOCK_NUM;
	set_block_now(v, rnd_now);
	print_block_now(v);
	rnd_next = rand() % BLOCK_NUM;
	set_block_next(v, rnd_next);
	print_block_next(v);

	// measuring time
	gettimeofday(&v->prev_time, NULL);	// set prev_time

	// [ run game main routine ]
	while (42)
	{
		v->prev_y = v->now_y;
		v->prev_x = v->now_x;
		
		// recieved keycode from stdin ?
		if (kbhit())
		{
			clear_block_now(v);
			keycode = getch();
// set_char_color(CLR_WHITE);
// printf("%lx\n", keycode);
// set_char_color(CLR_DEFAULT);
			if (keycode == KEY_ARROW_UP || keycode == 'w' ||
				keycode == '0' || keycode == ',')
				rotate_block(v, v->now_y, v->now_x, false);
			else if (keycode == '.')
				rotate_block(v, v->now_y, v->now_x, true);
			else if (keycode == KEY_ARROW_DOWN || keycode == 's')
			{
				while (check_grid(v, v->now_y + 1, v->now_x) == 0)
					v->now_y++;
			}
			else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
			{
				if (check_grid(v, v->now_y, v->now_x - 1) == 0)
					v->now_x--;
			}
			else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
			{
				if (check_grid(v, v->now_y, v->now_x + 1) == 0)
					v->now_x++;
			}
			// else
			// {
			// 	now_y = START_YCOORD;
			// 	now_x = START_XCOORD;
			// }
		}
		// measuring time ...
		gettimeofday(&v->now_time, NULL);
		v->duration = (v->now_time.tv_sec - v->prev_time.tv_sec)
				+ (v->now_time.tv_usec - v->prev_time.tv_usec) / 1000000.0;
		// gravity fall block
		if (LOOP_DURATION < v->duration)
		{
			// if (now_y < GRID_HEIGHT)
			if (check_grid(v, v->now_y + 1, v->now_x) == 0)
				v->now_y++;
			else
			{
				// game over ?
				if (v->now_y == START_YCOORD)
					exit_tetris();
				// fix block !
				put_grid(v, v->now_y, v->now_x);
				// delete lines
				deleteGrid(v);
				// create next block
				v->now_y = START_YCOORD;
				v->now_x = START_XCOORD;
				v->prev_y = START_YCOORD;
				v->prev_x = START_XCOORD;
				rnd_now = rnd_next;
				set_block_now(v, rnd_now);
				print_block_now(v);
				rnd_next = rand() % BLOCK_NUM;
				clear_block_next(v);
				set_block_next(v, rnd_next);
				print_block_next(v);				
			}
			v->prev_time = v->now_time;
		}
		// move block
		if (v->prev_y != v->now_y || v->prev_x != v->now_x)
		{
			// redraw block
			clear_block_prev(v);
			print_block_now(v);
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