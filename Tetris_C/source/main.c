/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 12:18:03 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/*!
** @brief	exit tetris (other exit ponint)
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
	copy_block(&v, v.block_type[1]);
	
	init_screen();
	int count;
	int i = 5;
	int j = 10;
	unsigned long	keycode;
	print_block(&v, i, j);
	for (count = 0; i < 10; )
	// while (42)
	{
		if (kbhit())
		{
			clear_block(&v, i, j);
			keycode = getch();
// set_char_color(CLR_WHITE);
// printf("%lx\n", keycode);
// set_char_color(CLR_DEFAULT);
			if (keycode == KEY_ARROW_UP)
				i--;
			else if (keycode == KEY_ARROW_DOWN)
				i++;
			else if (keycode == KEY_ARROW_LEFT)
				j--;
			else if (keycode == KEY_ARROW_RIGHT)
				j++;
			else
			{
				reset_screen();
				exit(1);
			}
			count++;
			print_block(&v, i, j);
		}
	}
	reset_screen();

	return 0;
}