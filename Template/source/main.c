/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:57 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 11:39:00 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/template.h"

extern t_envs	e;

/*!
** @brief	assign process, when key is pressed
** @param	keycode	pressed keycode
*/
static void		press_key(unsigned long keycode)
{
	if (keycode == KEY_ARROW_UP)
	{
		printf("up!\n");
	}
	else if (keycode == KEY_ARROW_DOWN)
	{
		printf("down!\n");
	}
	else if (keycode == KEY_ARROW_LEFT)
	{
		printf("left!\n");
	}
	else if (keycode == KEY_ARROW_RIGHT)
	{
		printf("right!\n");
	}
}

static void		game_loop(void)
{
	// [ declare variables ]
	unsigned long	keycode;

	// [ run main routine ]
	while (42) {
		if (kbhit())
		{
			keycode = getch();
			press_key(keycode);
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
