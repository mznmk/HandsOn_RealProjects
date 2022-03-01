/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 23:01:35 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 07:43:18 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/*!
** @brief	main (tetris entry point)
** @param	argc	argument count
** @param	argv	argument contents
** @return	status
*/
// int	main(int argc, char **argv)
// {
// 	(void)argc;
// 	(void)argv;

// 	t_vars	v;

// 	init_vars(&v);

// 	copy_block(&v, v.block_type[6]);

// 	init_screen(&v);
// 	int y = 0;
// 	int x = 10;
// 	for (y = 1; y < 25; y++)
// 	{
// 		print_block(&v, y, x + y%3);
// 		wait(500);
// 		clear_block(&v, y, x + y%3);
// 	}
// 	reset_screen(&v);

// 	return 0;
// }

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	t_vars	v;

	init_vars(&v);
	copy_block(&v, v.block_type[6]);
	
	init_screen(&v);
	int c;
	for (int i = 1; i < 10; )
	{
		if (kbhit() != 0)
		{
			print_block(&v, i, i);
			c = getch();
			printf("%x", c);
			clear_block(&v, i, i);
			i++;
		}
	}
	reset_screen(&v);

	return 0;
}