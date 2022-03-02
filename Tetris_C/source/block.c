/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:22:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/03 02:41:34 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

static int	check_range(t_cell cell, int y, int x)
{
	if (cell.c == '\0')
		return -1;
	if ((0 <= y && y < GRID_HEIGHT) && (0 <= x && x < GRID_WIDTH))
		return 0;
	else
		return -1;
}

int			print_cell(t_cell cell, int y, int x)
{
	if (check_range(cell, y, x) == -1)
		return -1;
	set_position(y, x);
	set_char_color(cell.char_color);
	set_back_color(cell.back_color);
	set_attribute(cell.attribute);
	printf("%c%c", cell.c, cell.c);
	fflush(stdout);
	
	return 0;
}

int			clear_cell(t_cell cell, int y, int x)
{
	if (check_range(cell, y, x) == -1)
		return -1;
	set_position(y, x);
	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
	printf("  ");
	fflush(stdout);

	return 0;
}

static int	check_cell(t_vars *v, t_cell cell, int y, int x)
{
	if (check_range(cell, y, x) || v->grid[y][x].c != '\0')
		return -1;

	return 0;
}

int			print_block(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			print_cell(v->block[i][j], y + i, x + j);

	return 0;
}

int			clear_block(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			clear_cell(v->block[i][j], y + i, x + j);

	return 0;
}

void		copy_block(t_vars *v, t_cell src[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			v->block[i][j] = src[i][j];

	return;
}

void		rotate_block(t_vars *v, int y, int x, bool turn_right)
{
	t_cell	block_tmp[BLOCK_SIZE][BLOCK_SIZE];

	// rotate & copy block ( block -> block_tmp )
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (turn_right)
				block_tmp[j][BLOCK_SIZE - 1 - i] = v->block[i][j];
			else
				block_tmp[BLOCK_SIZE - 1 - j][i] = v->block[i][j];
		}
	// clear block ( block )
	clear_block(v, y, x);
	// copy block ( block_tmp -> block )
	copy_block(v, block_tmp);
	// print block ( rotated block )
	print_block(v, y, x);

	return;
}

int			check_grid(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (v->block[i][j].c == '\0')
				continue;
			else
				if (check_cell(v, v->block[i][j], y + i, x + j))
					return -1;
		}
	
	return 0;
}

void		put_grid(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		if (check_cell(v, v->block[i][j], y + i, x + j) == 0)
			v->grid[y+i][x+j] = v->block[i][j];

	return;
}


static void		print_grid(t_vars *v)
{
	// draw screen
	for (int i = 0; i < GRID_HEIGHT; i++)
		for (int j = 0; j < GRID_WIDTH; j++)
			print_cell(v->grid[i][j], i, j);
	// [ return ;]
	return;
}

static int		check_line(t_vars *v, int y)
{
	// all cells filled in line ?
	for (int j = 0; j < GRID_WIDTH; j++)
		if (v->grid[y][j].c == '\0')	// fail ?
			return -1;
	// return
	return 0;
}

static void		deleteLine(t_vars *v, int y)
{
	// move line from bottom to top
	for (int i = y; i > 0; i--)
		for (int j = 0; j < GRID_WIDTH; j++)
			v->grid[i][j] = v->grid[i-1][j];
	// redraw screen
	set_back_color(CLR_BLACK);
	clear_board();
	print_grid(v);
	// return
	return;
}

void			deleteGrid(t_vars *v)
{
	// need to delete line ?
	for (int i = 0; i < GRID_HEIGHT; i++)
		if (check_line(v, i) == 0)
			deleteLine(v, i);
	// return
	return;
}