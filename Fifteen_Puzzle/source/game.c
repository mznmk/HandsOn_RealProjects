/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:11:12 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 19:23:57 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief	convert grid coord (2D->1D)
 * @param	y		coord y
 * @param	x		coord x
 * @return			grid index
 */
int				conv_grid_coord(int y, int x)
{
	// [ return ]
	return e.grid_size.width * y + x;
}

// -------------------------------------------------------------------------- //

/*!
** @brief		choose random
** @param		size (choose range size)
** @return		random number
*/
static int		choose_random(int size)
{
	// [ return ]
	return rand() % size;
}

// -------------------------------------------------------------------------- //

static void		set_random_color(void)
{
	int		rnd;
	// [ set char color ]
	set_char_color(CLR_BLACK);
	// [ set back color ]
	do
		rnd = choose_random(8);
	while (rnd == CLR_BLACK);
	set_back_color(rnd);
}

/**
 * @brief		draw_background
 */
void			draw_back(void)
{
	// [ draw back ]
	set_random_color();
	set_attribute(ATR_BLIGHT);
	for (int i = 0; i < e.back_size.height; i++)
		for (int j = 0; j < e.back_size.width; j++)
		{
			set_position(e.back_coord.y + i,e.back_coord.x + j);
			printf("##");
			fflush(stdout);
		}
	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
}

// -------------------------------------------------------------------------- //

/**
 * @brief		swap cell (coord1 <-> coord2)
 * 
 * @param		coord_1d_1	swapped cell coord (1d)
 * @param		coord_1d_2	swapped cell coord (1d)
 */
void			swap_cell(int coord_1d_1, int coord_1d_2)
{
	// [ swap cell ]
	int		temp;
	temp = v.grid[coord_1d_1];
	v.grid[coord_1d_1] = v.grid[coord_1d_2];
	v.grid[coord_1d_2] = temp;
}

// -------------------------------------------------------------------------- //

/**
 * @brief		set number to grid & swap number at random
 */
void			set_number_to_grid(void)
{
	// [ set number to grid ]
	for (int i = 0; i < e.cell_size; i++)
		v.grid[i] = (i + 1) % e.cell_size;
	// [ swap number at random ]
	int		rnd1;
	int		rnd2;
	int		loop;
	loop = e.cell_size * e.cell_size * e.cell_size;
	for (int i = 0; i < loop; i++)
	{
		rnd1 = choose_random(e.cell_size);
		rnd2 = choose_random(e.cell_size);
		swap_cell(rnd1, rnd2);		
	}
}

// -------------------------------------------------------------------------- //

/**
 * @brief		find coord of blank cell
 */
void			find_blank_cell(void)
{
	for (int i = 0; i < e.grid_size.height; i++)
		for (int j = 0; j < e.grid_size.width; j++)
			if (v.grid[conv_grid_coord(i, j)] == 0)
			{
				v.black_coord.y = i;
				v.black_coord.x = j;
			}
}

// -------------------------------------------------------------------------- //

/**
 * @brief		draw_number
 */
void			draw_number(void)
{
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_BLIGHT);
	for (int i = 0; i < e.grid_size.height; i++)
		for (int j = 0; j < e.grid_size.width; j++)
		{
			set_position(e.grid_coord.y + i*2, e.grid_coord.x + j*2);
			if (v.grid[conv_grid_coord(i, j)] == BLANK_NUMBER)
				printf("  ");
			else
				printf("%2d", v.grid[conv_grid_coord(i, j)]);
			fflush(stdout);
		}
	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
}

// -------------------------------------------------------------------------- //

/**
 * @brief		judge if cleared geme
 * @return		true (clear): 0 / false (not clear): -1
 */
int				judge_game_clear(void)
{
	// [ judge if cleared game ]
	for (int i = 0; i < e.cell_size; i++)
		if (v.grid[i] != (i+1) % e.cell_size)
			return -1;
	return 0;
}

/**
 * @brief		draw_stat
 */
void			draw_stat(void)
{
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_BLIGHT);

	// [ draw status ]
	for (int i = 0; i < e.stat_size.width; i++)
	{
		set_position(e.stat_coord.y, e.stat_coord.x + i);
		printf("  ");
		fflush(stdout);
	}
	// [ game clear ? ]
	if (judge_game_clear() == 0)
	{
		set_position(e.stat_coord.y, e.stat_coord.x);
		printf("clear!");
		fflush(stdout);
	}

	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
}
