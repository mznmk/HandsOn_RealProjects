/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 14:36:37 by mmizuno          ###   ########.fr       */
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
	int now_y = 0;
	int now_x = 10;
	int prev_y, prev_x;
	unsigned long	keycode;

	copy_block(v, v->block_type[1]);

	print_block(v, now_y, now_x);

	gettimeofday(&v->prev_time, NULL);	// set prev_time

	for ( ; now_y < FLD_HEIGHT; )
	// while (42)
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
			if (keycode == KEY_ARROW_UP)
				rotate_block(v, now_y, now_x, true);
			else if (keycode == KEY_ARROW_DOWN)
				now_y++;
			else if (keycode == KEY_ARROW_LEFT)
				now_x--;
			else if (keycode == KEY_ARROW_RIGHT)
				now_x++;
			else
			{
				now_y = START_YCOORD;
				now_x = START_XCOORD;
			}
		}
		// measuring time ...
		gettimeofday(&v->now_time, NULL);
		v->duration = (v->now_time.tv_sec - v->prev_time.tv_sec)
				+ (v->now_time.tv_usec - v->prev_time.tv_usec) / 1000000.0;
		// gravity fall block
		if (LOOP_DURATION < v->duration)
		{
			v->prev_time = v->now_time;
			now_y++;
		}
		// move block
		if (prev_y != now_y || prev_x != now_x)
		{
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
	return 0;
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