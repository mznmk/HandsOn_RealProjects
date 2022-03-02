/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 03:59:19 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 16:28:05 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

static void	init_block_type(t_vars *v) 
{
	for (int i = 0; i < BLOCK_NUM; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			for (int k = 0; k < BLOCK_SIZE; k++)
			{
				// c
				v->block_type[i][j][k].c = '\0';
				// char_color
				switch (i)
				{
					case 0:
						v->block_type[i][j][k].char_color = CLR_RED;
						break;
					case 1:
						v->block_type[i][j][k].char_color = CLR_GREEN;
						break;
					case 2:
						v->block_type[i][j][k].char_color = CLR_YELLOW;
						break;
					case 3:
						v->block_type[i][j][k].char_color = CLR_BLUE;
						break;
					case 4:
						v->block_type[i][j][k].char_color = CLR_MAGENTA;
						break;
					case 5:
						v->block_type[i][j][k].char_color = CLR_CYAN;
						break;
					case 6:
						v->block_type[i][j][k].char_color = CLR_WHITE;
						break;
					default:
						v->block_type[i][j][k].char_color = CLR_BLACK;
						break;
				}
				// back_color
				v->block_type[i][j][k].back_color = CLR_BLACK;
				// attribute
				v->block_type[i][j][k].attribute = ATR_NORMAL;
			}
	return;
}

static void	set_block_type_helper(t_vars *v, int n,
									int y[BLOCK_SIZE], int x[BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
	{
		// c
		v->block_type[n][y[i]][x[i]].c = ' ';
		// attribute
		v->block_type[n][y[i]][x[i]].attribute = ATR_REVERSE;
	}
	return;
}

static void	set_block_type(t_vars *v)
{
	int y[BLOCK_SIZE];
	int x[BLOCK_SIZE];

	// [ type 0 ]
	// ..#.
	// .##.
	// .#..
	// ....
	y[0] = 0; x[0] = 2;
	y[1] = 1; x[1] = 1;
	y[2] = 1; x[2] = 2;
	y[3] = 2; x[3] = 1;
	set_block_type_helper(v, 0, y, x);
	// [ type 1 ]
	// .##,
	// .#..
	// .#..
	// ....
	y[0] = 0; x[0] = 1;
	y[1] = 0; x[1] = 2;
	y[2] = 1; x[2] = 1;
	y[3] = 2; x[3] = 1;
	set_block_type_helper(v, 1, y, x);
	// [ type 2 ]
	// ..,,
	// .##.
	// ##..
	// ....
	y[0] = 1; x[1] = 1;
	y[1] = 1; x[1] = 2;
	y[2] = 2; x[2] = 0;
	y[3] = 2; x[3] = 1;
	set_block_type_helper(v, 2, y, x);
	// [ type 3 ]
	// ..,,
	// .##.
	// .##.
	// ....
	y[0] = 1; x[0] = 1;
	y[1] = 1; x[1] = 2;
	y[2] = 2; x[2] = 1;
	y[3] = 2; x[3] = 2;
	set_block_type_helper(v, 3, y, x);
	// [ type 4 ]
	// .#,,
	// .#..
	// .#..
	// .#..
	y[0] = 0; x[0] = 1;
	y[1] = 1; x[1] = 1;
	y[2] = 2; x[2] = 1;
	y[3] = 3; x[3] = 1;
	set_block_type_helper(v, 4, y, x);
	// [ type 5 ]
	// ..,,
	// ###.
	// .#..
	// ....
	y[0] = 1; x[0] = 0;
	y[1] = 1; x[1] = 1;
	y[2] = 1; x[2] = 2;
	y[3] = 2; x[3] = 1;
	set_block_type_helper(v, 5, y, x);
	// [ type 6 ]
	// .#,,
	// .#..
	// .##.
	// ....
	y[0] = 0; x[0] = 1;
	y[1] = 1; x[1] = 1;
	y[2] = 2; x[2] = 1;
	y[3] = 2; x[3] = 2;
	set_block_type_helper(v, 6, y, x);
	
	return;
}

/*!
** @brief	initialize data container (block_type)
** @param	v			tetris variables (structure)
** @return	none
*/
static void	init_vars_block_type(t_vars *v) 
{
	init_block_type(v);
	set_block_type(v);
	return;
}

/*!
** @brief	initialize data container (grid)
** @param	v			tetris variables (structure)
** @return	none
*/
static void	init_vars_grid(t_vars *v)
{
	// t_cell	templete = {'\0', CLR_BLACK, CLR_BLACK, ATR_NORMAL};
	t_cell	templete;
	templete.c = '\0';
	templete.char_color = CLR_BLACK;
	templete.back_color = CLR_BLACK;
	templete.attribute = ATR_NORMAL;
	
	for (int i = 0; i < GRID_HEIGHT; i++)
		for (int j = 0; j < GRID_WIDTH; j++)
			v->grid[i][j] = templete;

	return;
}

/*!
** @brief	initialize data container
** @param	v			tetris variables (structure)
** @return	none
*/
void		init_vars(t_vars *v)
{
	init_vars_block_type(v);
	init_vars_grid(v);
	return;
}