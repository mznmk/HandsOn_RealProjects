/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:11:12 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 18:19:11 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fifteen_puzzle.h"

extern t_envs	e;
extern t_vars	v;

static int		choose_random(int size)
{
	// [ return ]
	return rand() % size;
}

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

/**
 * @brief		judge if cleared geme
 * @return int 
 */
int				judge_game_clear(void)
{
	// [ judge if cleared game ]
	for (int i = 0; i < e.cell_size; i++)
		if (v.grid[i] != (i+1) % e.cell_size)
			return -1;
	// [ return (success) ]
	return 0;
}

void		draw_stat(void)
{
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_BLIGHT);

	for (int i = 0; i < e.stat_size.width; i++)
	{
		set_position(e.stat_coord.y, e.stat_coord.x + i);
		printf("  ");
		fflush(stdout);
	}
	set_position(e.stat_coord.y, e.stat_coord.x);
	printf("y: %d x: %d", v.black_cell.y, v.black_cell.x);
	fflush(stdout);

	set_position(e.stat_coord.y, e.stat_coord.x);
	if (judge_game_clear() == 0)
	{
		printf("clear!");
		fflush(stdout);

	}

	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);

}

void			find_blank_cell(void)
{
	for (int i = 0; i < e.grid_size.height; i++)
		for (int j = 0; j < e.grid_size.width; j++)
			if (v.grid[conv_grid_coord(i, j)] == 0)
			{
				v.black_cell.y = i;
				v.black_cell.x = j;
			}
}

// static void		set_number_to_grid(void)
// {
// 	for (int i = 0; i < e.cell_size; i++)
// 		v.grid[i] = (i + 1) % e.cell_size;
// }

void			swap_cell(int coord_1d_1, int coord_1d_2)
{
	// [ swap cell ]
	int		temp;
	temp = v.grid[coord_1d_1];
	v.grid[coord_1d_1] = v.grid[coord_1d_2];
	v.grid[coord_1d_2] = temp;
}

void			swap_cell_at_random(void)
{
	int loop_times = e.cell_size * e.cell_size * e.cell_size;
	int		rnd1;
	int		rnd2;
	for (int i = 0; i < loop_times; i++)
	{
		rnd1 = choose_random(e.cell_size);
		rnd2 = choose_random(e.cell_size);
		swap_cell(rnd1, rnd2);		
	}
}
