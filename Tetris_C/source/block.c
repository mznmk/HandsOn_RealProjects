/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:22:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/04 04:12:42 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

// static int	is_cell_in_grid(t_cell cell, int y, int x)
// {
// 	// [ cell is in grid ? ]
// 	if ((0 <= y && y < GRID_HEIGHT) && (0 <= x && x < GRID_WIDTH))
// 		return 0;
// 	else
// 		return -1;
// }

static int	check_range(t_cell cell, int y, int x)
{
	if (cell.c == '\0')
		return -1;
	if ((0 <= y && y < GRID_HEIGHT) && (0 <= x && x < GRID_WIDTH))
		return 0;
	else
		return -1;
}

static int	check_cell(t_vars *v, t_cell cell, int y, int x)
{
	if (check_range(cell, y, x) || v->grid[y][x].c != '\0')
		return -1;

	return 0;
}

// ========================================================================== //

static void	set_block(t_cell dest[BLOCK_SIZE][BLOCK_SIZE],
										t_cell src[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			dest[i][j] = src[i][j];

	return;
}

void		set_block_now(t_vars *v, int type)
{
	set_block(v->block_now, v->block_type[type]);
	// [ return ]
	return;
}

void		set_block_next(t_vars *v, int type)
{
	set_block(v->block_next, v->block_type[type]);
	// [ return ]
	return;
}

// ========================================================================== //

void		rotate_block(t_vars *v, int y, int x, bool turn_right)
{
	t_cell	block_tmp[BLOCK_SIZE][BLOCK_SIZE];

	// rotate & copy block ( block -> block_tmp )
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (turn_right)
				block_tmp[j][BLOCK_SIZE - 1 - i] = v->block_now[i][j];
			else
				block_tmp[BLOCK_SIZE - 1 - j][i] = v->block_now[i][j];
		}
	// clear block ( block )
	clear_block(v->block_now, y, x);
	// copy block ( block_tmp -> block )
	set_block(v->block_now, block_tmp);
	// print block ( rotated block )
	draw_block(v->block_now, y, x);

	return;
}

// ========================================================================== //

int			check_grid(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (v->block_now[i][j].c == '\0')
				continue;
			else
				if (check_cell(v, v->block_now[i][j], y + i, x + j))
					return -1;
		}
	
	return 0;
}

void		fix_block_to_grid(t_vars *v, int y, int x)
{
	// [ fix block to grid ]
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		if (check_cell(v, v->block_now[i][j], y + i, x + j) == 0)
			v->grid[y+i][x+j] = v->block_now[i][j];
	
	// [ return ]
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

static void		erase_line(t_vars *v, int y)
{
	// [ erase line from bottom to top ]
	for (int i = y; i > 0; i--)
		for (int j = 0; j < GRID_WIDTH; j++)
			v->grid[i][j] = v->grid[i-1][j];
	
	// [ redraw screen ]
	// set_back_color(CLR_BLACK);
	// clear_terminal();
	draw_background();
	draw_grid(v);

	// [ return ]
	return;
}

void			erase_lines(t_vars *v)
{
	// [ need to erase line ? ]
	int erase_count = 0;
	for (int i = 0; i < GRID_HEIGHT; i++)
		if (check_line(v, i) == 0)
		{
			erase_line(v, i);
			erase_count++;
		}

	// [ update score (erase line) ]
	switch (erase_count)
	{
		case 1:
			v->score += ERASE_1LINE;
			break;
		case 2:
			v->score += ERASE_2LINE;
			break;
		case 3:
			v->score += ERASE_3LINE;
			break;
		case 4:
			v->score += ERASE_4LINE;
			break;
	}
	draw_score(v);

	// [ return ]
	return;
}