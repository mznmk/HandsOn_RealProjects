/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:12:21 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 22:07:55 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

static void		draw_screen_back(void)
{
	// [ draw screen back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_WHITE);
	set_attribute(ATR_BLIGHT);
	for (int i = e.back_coord.y; i < e.back_coord.y + e.back_size.height; i++)
		for (int j = e.back_coord.x; j < e.back_coord.x + e.back_size.width; j++)
		{
			set_position(i, j);
			printf("%c%c", '#', '#');
		}
	fflush(stdout);
}

static void		draw_field_back(void)
{
	// [ draw field back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = e.field_coord.y; i < e.field_coord.y + e.field_size.height; i++)
		for (int j = e.field_coord.x; j < e.field_coord.x + e.field_size.width; j++)
		{
			set_position(i, j);
			printf("%c%c", ' ', ' ');
		}
	fflush(stdout);
}

static void		draw_next_back(void)
{
	// [ draw next back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = e.next_coord.y; i < e.next_coord.y + NEXT_HEIGHT; i++)
		for (int j = e.next_coord.x; j < e.next_coord.x + NEXT_WIDTH; j++)
		{
			set_position(i, j);
			printf("%c%c", ' ', ' ');
		}
	fflush(stdout);
}

static void		draw_score_back(void)
{
	// [ draw score back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = e.score_coord.y; i < e.score_coord.y + SCORE_HEIGHT; i++)
		for (int j = e.score_coord.x; j < e.score_coord.x + SCORE_WIDTH; j++)
		{
			set_position(i, j);
			printf("%c%c", ' ', ' ');
		}
	fflush(stdout);
}

void			draw_background(void)
{
	// [ draw background ]
	clear_terminal();
	draw_screen_back();
	draw_field_back();
	draw_next_back();
	draw_score_back();
}

// -------------------------------------------------------------------------- //

int			draw_cell(t_cell cell, int y, int x)
{
	// if (check_range(cell, y, x) == -1)
	// 	return -1;

	// [ cell is filled ? ]
	if (is_filled_cell(cell) == -1)
		return -1;

	// [ print cell ]
	set_position(y, x);
	set_char_color(cell.char_color);
	set_back_color(cell.back_color);
	set_attribute(cell.attribute);
	printf("%c%c", cell.c, cell.c);
	fflush(stdout);
	
	// [ return ]
	return 0;
}

int			draw_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			draw_cell(block[i][j], y + i, x + j);

	return 0;
}

void		draw_block_now(void)
{
	draw_block(v.block_now, e.field_coord.y + v.now_y, e.field_coord.x + v.now_x);
}

void		draw_block_next(void)
{
	draw_block(v.block_next, e.next_coord.y, e.next_coord.x);
}

// -------------------------------------------------------------------------- //

void		draw_field(void)
{
	// draw screen
	for (int i = 0; i < e.field_size.height; i++)
		for (int j = 0; j < e.field_size.width; j++)
			draw_cell(v.field[calc_field_index(i, j)],
						e.field_coord.y + i, e.field_coord.x + j);
}

void	draw_score(void)
{
	// [ draw score ]
	set_position(e.score_coord.y, e.score_coord.x);
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	set_attribute(ATR_BLIGHT);
	printf("%8d", v.score);
	fflush(stdout);

	// [ return ]
	return;	
}

// ========================================================================== //

int			clear_cell(t_cell cell, int y, int x)
{
	// [ cell is filled ]
	if (is_filled_cell(cell) == -1)
		return -1;

	// [ clear cell ]
	set_position(y, x);
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	printf("  ");
	fflush(stdout);

	// [ return ]
	return 0;
}

void		clear_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x)
{
	// [ clear block ]
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			clear_cell(block[i][j], y + i, x + j);

	// [ return ]
	return;
}

void		clear_block_prev(void)
{
	// [ clear block_now ]
	clear_block(v.block_now, e.field_coord.y + v.prev_y, e.field_coord.x + v.prev_x);

	// [ return ]
	return;
}

void		clear_block_now(void)
{
	// [ clear block_now ]
	clear_block(v.block_now, e.field_coord.y + v.now_y, e.field_coord.x + v.now_x);

	// [ return ]
	return;
}

void		clear_block_next(void)
{
	// [ clear block_next ]
	clear_block(v.block_next, e.next_coord.y, e.next_coord.x);

	// [ return ]
	return;
}

// ========================================================================== //
