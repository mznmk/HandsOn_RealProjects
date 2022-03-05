/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:12:21 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 18:45:10 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

static void		set_random_color(void)
{
	int		rnd1;
	int		rnd2;
	// [ set char color ]
	rnd1 = CLR_BLACK;
	// rnd1 = choose_random(BLOCK_NUM);
	set_char_color(rnd1);
	// [ set back color ]
	do
		rnd2 = choose_random(BLOCK_NUM);
	while (rnd1 == rnd2);
	set_back_color(rnd2);
}

static void		draw_screen_back(void)
{
	// [ draw screen back ]
	set_random_color();
	set_attribute(ATR_BLIGHT);
	for (int i = 0; i < e.back_size.height; i++)
		for (int j = 0 ; j < e.back_size.width; j++)
		{
			set_position(e.back_coord.y + i, e.back_coord.x + j);
			printf("%c%c", '#', '#');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_field_back(void)
{
	// [ draw field back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = 0; i < e.field_size.height; i++)
		for (int j = 0; j < e.field_size.width; j++)
		{
			set_position(e.field_coord.y + i, e.field_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_next_back(void)
{
	// [ draw next back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = 0; i < NEXT_HEIGHT; i++)
		for (int j = 0; j < NEXT_WIDTH; j++)
		{
			set_position(e.next1_coord.y + i, e.next1_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
			set_position(e.next2_coord.y + i, e.next2_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_score_back(void)
{
	// [ draw score back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = 0; i < SCORE_HEIGHT; i++)
		for (int j = 0; j < SCORE_WIDTH; j++)
		{
			set_position(e.score_coord.y + i, e.score_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

void			draw_back(void)
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
	set_font_color_default();
	
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
	draw_block(v.block_next1, e.next1_coord.y, e.next1_coord.x);
	draw_block(v.block_next2, e.next2_coord.y, e.next2_coord.x);
}

// -------------------------------------------------------------------------- //

void		draw_field(void)
{
	// draw screen
	for (int i = 0; i < e.field_size.height; i++)
		for (int j = 0; j < e.field_size.width; j++)
			draw_cell(v.field[conv_field_coord(i, j)],
						e.field_coord.y + i, e.field_coord.x + j);
}

void	draw_score(void)
{
	// [ draw score ]
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
		set_attribute(ATR_BLIGHT);
	set_position(e.score_coord.y, e.score_coord.x);
	printf("score");
	set_position(e.score_coord.y + 1, e.score_coord.x);
	printf("%8d", v.score);
	fflush(stdout);
	set_font_color_default();

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
	set_font_color_default();

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
	clear_block(v.block_next1, e.next1_coord.y, e.next1_coord.x);
	clear_block(v.block_next2, e.next2_coord.y, e.next2_coord.x);

	// [ return ]
	return;
}

// ========================================================================== //
