/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 23:56:19 by mmizuno          ###   ########.fr       */
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
	int now_y = START_YCOORD;
	int now_x = START_XCOORD;
	int prev_y, prev_x;
	int rnd;
	unsigned long	keycode;

	// draw game screen
	// create next block
	rnd = rand() % BLOCK_NUM;
	copy_block(v, v->block_type[rnd]);
	print_block(v, now_y, now_x);

	// measuring time
	gettimeofday(&v->prev_time, NULL);	// set prev_time

	// run game main routine
	while (42)
	{
		prev_y = now_y;
		prev_x = now_x;
		
		// recieved keycode from stdin ?
		if (kbhit())
		{
			clear_block(v, now_y, now_x);
			keycode = getch();
// set_char_color(CLR_WHITE);
// printf("%lx\n", keycode);
// set_char_color(CLR_DEFAULT);
			if (keycode == KEY_ARROW_UP || keycode == 'w' ||
				keycode == '0' || keycode == ',')
				rotate_block(v, now_y, now_x, false);
			else if (keycode == '.')
				rotate_block(v, now_y, now_x, true);
			else if (keycode == KEY_ARROW_DOWN || keycode == 's')
			{
				while (check_grid(v, now_y + 1, now_x) == 0)
					now_y++;
			}
			else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
			{
				if (check_grid(v, now_y, now_x - 1) == 0)
					now_x--;
			}
			else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
			{
				if (check_grid(v, now_y, now_x + 1) == 0)
					now_x++;
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
			if (check_grid(v, now_y + 1, now_x) == 0)
				now_y++;
			else
			{
				// game over ?
				if (now_y == 0)
					exit_tetris();
				// fix block !
				put_grid(v, now_y, now_x);
				// create next block
				now_y = START_YCOORD;
				now_x = START_XCOORD;
				prev_y = START_YCOORD;
				prev_x = START_XCOORD;
				rnd = rand() % BLOCK_NUM;
				copy_block(v, v->block_type[rnd]);
				print_block(v, now_y, now_x);
			}
			v->prev_time = v->now_time;
		}
		// move block
		if (prev_y != now_y || prev_x != now_x)
		{
			// redraw block
			clear_block(v, prev_y, prev_x);
			print_block(v, now_y, now_x);
		}
	}
}

/*!
** @brief	exit tetris (other exit point)
** @return	status
*/
int		exit_tetris(void)
{
	reset_screen();
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
	(void)argc;
	(void)argv;
	t_vars	v;

	init_vars(&v);
	init_screen();
	game_loop(&v);
	reset_screen();

	return 0;
}