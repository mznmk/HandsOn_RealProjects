/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:12:21 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 03:06:27 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief		draw cell when cell filled
 * @param		cell	draw source
 * @param		y		draw coord y
 * @param		x		draw coord x
 * @return		true (draw success): 0 / false (draw failure): -1
 */
static int		draw_cell(t_cell cell, int y, int x)
{
	// [ cell is filled ? ]
	if (is_filled_cell(cell) == -1)
		return -1;

	// [ draw cell ]
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

/**
 * @brief		draw block
 * @param		block	draw source
 * @param		y		draw coord y
 * @param		x		draw coord x
 */
void			draw_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			draw_cell(block[i][j], y + i, x + j);
}

/**
 * @brief	draw now block
 */
void			draw_block_now(void)
{
	draw_block(v.block_now, e.field_coord.y + v.now_y, e.field_coord.x + v.now_x);
}

/**
 * @brief	draw next1/next2 block
 */
void			draw_block_next(void)
{
	draw_block(v.block_next1, e.next1_coord.y, e.next1_coord.x);
	draw_block(v.block_next2, e.next2_coord.y, e.next2_coord.x);
}

/**
 * @brief		draw game field
 */
void			draw_field(void)
{
	// [ draw game field ]
	for (int i = 0; i < e.field_size.height; i++)
		for (int j = 0; j < e.field_size.width; j++)
			draw_cell(v.field[conv_field_coord(i, j)],
						e.field_coord.y + i, e.field_coord.x + j);
}

/**
 * @brief		draw score
 */
void			draw_score(void)
{
	// [ draw score ]
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_BLIGHT);
	set_position(e.score_coord.y, e.score_coord.x);
	printf("score   ");
	set_position(e.score_coord.y + 1, e.score_coord.x);
	printf("%8d", v.score);
	fflush(stdout);
	set_font_color_default();

	// [ return ]
	return;	
}

// -------------------------------------------------------------------------- //

/**
 * @brief		clear cell when cell filled
 * @param		cell	clear source
 * @param		y		clear coord y
 * @param		x		clear coord x
 * @return		true (clear success): 0 / false (clear failure): -1
 */
static int		clear_cell(t_cell cell, int y, int x)
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

/**
 * @brief		clear block
 * @param		block	clear source
 * @param		y		clear coord y
 * @param		x		clear coord x
 */
void			clear_block(t_cell block[BLOCK_SIZE][BLOCK_SIZE], int y, int x)
{
	// [ clear block ]
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			clear_cell(block[i][j], y + i, x + j);
}

/**
 * @brief		clear prev block (use when block move)
 */
void			clear_block_prev(void)
{
	// [ clear block_now ]
	clear_block(v.block_now, e.field_coord.y + v.prev_y, e.field_coord.x + v.prev_x);
}

/**
 * @brief		clear now block
 */
void			clear_block_now(void)
{
	// [ clear block_now ]
	clear_block(v.block_now, e.field_coord.y + v.now_y, e.field_coord.x + v.now_x);
}

/**
 * @brief		clear next1/next2 block
 */
void			clear_block_next(void)
{
	// [ clear block_next ]
	clear_block(v.block_next1, e.next1_coord.y, e.next1_coord.x);
	clear_block(v.block_next2, e.next2_coord.y, e.next2_coord.x);
}
