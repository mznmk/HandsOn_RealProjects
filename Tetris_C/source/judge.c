/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   judge.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 03:09:08 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 03:13:12 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief		cell is filled ?
 * @param		cell	judged cell
 * @return		true (filled): 0 / false (not filled): -1
 */
int				is_filled_cell(t_cell cell)
{
	// [ cell is filled ? ]
	if (cell.c == '\0')
		return -1;
	else
		return 0;
}

/**
 * @brief		cell in in field ?
 * @param		y	cell coord y
 * @param		x	cell coord x
 * @return		true (in field): 0 / false (not in field): -1
 */
static int		is_cell_in_field(int y, int x)
{
	// [ cell is in field ? ]
	if ((0 <= y && y < e.field_size.height) && 
		(0 <= x && x < e.field_size.width))
		return 0;
	else
		return -1;
}

/**
 * @brief		check if can use cell ?
 * @param		cell	checked cell
 * @param		y		cell coord y
 * @param		x		cell coord x
 * @return		true (can use): 0 / false (cannot use): -1
 */
int				can_use_cell(t_cell cell, int y, int x)
{
	// [ can use cell ? ]
	if (is_filled_cell(cell) == 0 &&
		is_cell_in_field(y, x) == 0 &&
		is_filled_cell(v.field[conv_field_coord(y, x)]) == -1)
		return 0;
	else
		return -1;
}


// -------------------------------------------------------------------------- //

/**
 * @brief		judge collision
 * @param		block	to be judged
 * @param		y		block coord y
 * @param		x		block coord x
 * @return		true (no collision): 0 / false (collision): -1
 */
int				judge_collision(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x)
{
	// [ judge collision ]
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (block[i][j].c == '\0')
				continue;
			else
				if (can_use_cell(block[i][j], y + i, x + j))
					return -1;
		}
	// [ return ]
	return 0;
}
