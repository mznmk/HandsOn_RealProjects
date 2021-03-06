/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:57 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 20:42:24 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief		can swap cell (in range?)
 * @param		y	cell coord y
 * @param		x	cell coord x
 * @return		true (can swap): 0 / false (cannot swap): -1
 */
static int		can_swap_cell(int y, int x)
{
	// [ can swap cell? ]
	if (!(0 <= y && y < e.grid_size.height))
		return -1;
	if (!(0 <= x && x < e.grid_size.width))
		return -1;
	// [ return (true) ]
	return 0;
}

void			press_key_up(void)
{
	if (can_swap_cell(v.black_coord.y - 1, v.black_coord.x) == 0)
	{
		// swap cell
		swap_cell(conv_grid_coord(v.black_coord.y, v.black_coord.x),
					conv_grid_coord(v.black_coord.y - 1, v.black_coord.x));
		// update block coord
		v.black_coord.y -= 1;			
	}
}

void			press_key_down(void)
{
	if (can_swap_cell(v.black_coord.y + 1, v.black_coord.x) == 0)
	{
		// swap cell
		swap_cell(conv_grid_coord(v.black_coord.y, v.black_coord.x),
					conv_grid_coord(v.black_coord.y + 1, v.black_coord.x));
		// update block coord
		v.black_coord.y += 1;			
	}
}

void			press_key_left(void)
{
	if (can_swap_cell(v.black_coord.y, v.black_coord.x - 1) == 0)
	{
		// swap cell
		swap_cell(conv_grid_coord(v.black_coord.y, v.black_coord.x),
					conv_grid_coord(v.black_coord.y, v.black_coord.x - 1));
		// update block coord
		v.black_coord.x -= 1;			
	}
}

void			press_key_right(void)
{
	if (can_swap_cell(v.black_coord.y, v.black_coord.x + 1) == 0)
	{
		// swap cell
		swap_cell(conv_grid_coord(v.black_coord.y, v.black_coord.x),
					conv_grid_coord(v.black_coord.y, v.black_coord.x + 1));
		// update block coord
		v.black_coord.x += 1;			
	}
}

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		press_key(unsigned long keycode)
{
	if (keycode == KEY_ARROW_UP || keycode == 'w')
		press_key_up();
	else if (keycode == KEY_ARROW_DOWN || keycode == 's')
		press_key_down();
	else if (keycode == KEY_ARROW_LEFT || keycode == 'a')
		press_key_left();
	else if (keycode == KEY_ARROW_RIGHT || keycode == 'd')
		press_key_right();
}

/*!
** @brief	game loop (15puzzle game loop)
*/
static void		game_loop(void)
{
	// [ declare variables ]
	unsigned long	keycode;

	// draw screen
	draw_back();
	set_number_to_grid();
	draw_number();
	draw_stat();

	// [ run main routine ]
	while (42) {
		// [ pressed key ? ]
		if (kbhit())
		{
			// recieve keycode
			keycode = getch();
			// move blank cell
			press_key(keycode);
			// draw screen
			draw_number();
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
