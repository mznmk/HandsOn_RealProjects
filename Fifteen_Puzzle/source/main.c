/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:57 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 18:02:27 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		press_key(unsigned long keycode)
{
	if (keycode == KEY_ARROW_UP)
	{
		if (can_swap_cell(v.black_cell.y - 1, v.black_cell.x) == 0)
			swap_cell(conv_grid_coord(v.black_cell.y, v.black_cell.x),
						conv_grid_coord(v.black_cell.y - 1, v.black_cell.x));
		}
	else if (keycode == KEY_ARROW_DOWN)
	{
		if (can_swap_cell(v.black_cell.y + 1, v.black_cell.x) == 0)
			swap_cell(conv_grid_coord(v.black_cell.y, v.black_cell.x),
						conv_grid_coord(v.black_cell.y + 1, v.black_cell.x));
	}
	else if (keycode == KEY_ARROW_LEFT)
	{
		if (can_swap_cell(v.black_cell.y, v.black_cell.x - 1) == 0)
			swap_cell(conv_grid_coord(v.black_cell.y, v.black_cell.x),
						conv_grid_coord(v.black_cell.y, v.black_cell.x - 1));
	}
	else if (keycode == KEY_ARROW_RIGHT)
	{
		if (can_swap_cell(v.black_cell.y, v.black_cell.x + 1) == 0)
			swap_cell(conv_grid_coord(v.black_cell.y, v.black_cell.x),
						conv_grid_coord(v.black_cell.y, v.black_cell.x + 1));
	}
}

static void		game_loop(void)
{
	// [ declare variables ]
	unsigned long	keycode;

	// draw back
	draw_back();

	// set number	
	for (int i = 0; i < e.cell_size; i++)
		v.grid[i] = (i + 1) % e.cell_size;

	// swap at random
	swap_cell_at_random();

	// find blank cell
	find_blank_cell();

	// draw number
	draw_number();

	// draw_stat
	draw_stat();

	// [ run main routine ]
	while (42) {
		if (kbhit())
		{
			keycode = getch();
			press_key(keycode);

			draw_number();

			find_blank_cell();
			draw_stat();
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
	// [ declare variable ]

	// [ initialize ]
	init_game(argc, argv);

	// [ execute 15puzzle ]
	game_loop();

	// [ finallize ]
	fin_game();

	// [ return ]
	return 0;
}

// -------------------------------------------------------------------------- //

/*!
** @brief	exit game (other exit point)
** @return	status
*/
void			exit_game(void)
{
	// [ finalize game ]
	fin_game();

	// [ return (exit point) ]
	exit(0);
}
