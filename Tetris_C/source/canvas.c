/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:12:21 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 04:34:00 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

// ========================================================================== //

static int	is_cell_filled(t_cell cell)
{
	// [ cell is filled ? ]
	if (cell.c == '\0')
		return -1;
	return 0;
}

// ========================================================================== //

static void		draw_screen_back(void)
{
	// [ draw screen back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_WHITE);
	set_attribute(ATR_BLIGHT);
	for (int i = BACK_YCOORD; i < BACK_YCOORD + BACK_HEIGHT; i++)
		for (int j = BACK_XCOORD; j < BACK_XCOORD + BACK_WIDTH; j++)
		{
			set_position(i, j);
			printf("%c%c", '#', '#');
		}
	fflush(stdout);
}

static void		draw_grid_back(void)
{
	// [ draw grid back ]
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	for (int i = GRID_YCOORD; i < GRID_YCOORD + GRID_HEIGHT; i++)
		for (int j = GRID_XCOORD; j < GRID_XCOORD + GRID_WIDTH; j++)
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
	for (int i = NEXT_YCOORD; i < NEXT_YCOORD + NEXT_HEIGHT; i++)
		for (int j = NEXT_XCOORD; j < NEXT_XCOORD + NEXT_WIDTH; j++)
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
	for (int i = SCORE_YCOORD; i < SCORE_YCOORD + SCORE_HEIGHT; i++)
		for (int j = SCORE_XCOORD; j < SCORE_XCOORD + SCORE_WIDTH; j++)
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
	draw_grid_back();
	draw_next_back();
	draw_score_back();
}

// -------------------------------------------------------------------------- //

int			draw_cell(t_cell cell, int y, int x)
{
	// if (check_range(cell, y, x) == -1)
	// 	return -1;

	// [ cell is filled ? ]
	if (is_cell_filled(cell) == -1)
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
			draw_cell(block[i][j], GRID_YCOORD + y + i, GRID_XCOORD + x + j);

	return 0;
}

void		draw_block_now(t_vars *v)
{
	draw_block(v->block_now, v->now_y, v->now_x);
}

void		draw_block_next(t_vars *v)
{
	draw_block(v->block_next, NEXT_YCOORD, NEXT_XCOORD);
}

// -------------------------------------------------------------------------- //

void		draw_grid(t_vars *v)
{
	// draw screen
	for (int i = 0; i < GRID_HEIGHT; i++)
		for (int j = 0; j < GRID_WIDTH; j++)
			draw_cell(v->grid[i][j], GRID_YCOORD + i, GRID_XCOORD + j);
	// [ return ;]
	return;
}

void	draw_score(t_vars *v)
{
	// [ draw score ]
	set_position(SCORE_YCOORD, SCORE_XCOORD);
	set_char_color(CLR_WHITE);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
	set_attribute(ATR_BLIGHT);
	printf("%8d", v->score);
	fflush(stdout);

	// [ return ]
	return;	
}

// ========================================================================== //

int			clear_cell(t_cell cell, int y, int x)
{
	// [ cell is filled ]
	if (is_cell_filled(cell) == -1)
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
			clear_cell(block[i][j], GRID_YCOORD + y + i, GRID_XCOORD + x + j);

	// [ return ]
	return;
}

void		clear_block_prev(t_vars *v)
{
	// [ clear block_now ]
	clear_block(v->block_now, v->prev_y, v->prev_x);

	// [ return ]
	return;
}

void		clear_block_now(t_vars *v)
{
	// [ clear block_now ]
	clear_block(v->block_now, v->now_y, v->now_x);

	// [ return ]
	return;
}

void		clear_block_next(t_vars *v)
{
	// [ clear block_next ]
	clear_block(v->block_next, NEXT_YCOORD, NEXT_XCOORD);

	// [ return ]
	return;
}

// ========================================================================== //
