/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:22:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 03:13:16 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

extern t_envs	e;
extern t_vars	v;

/**
 * @brief		set new block to now/next block
 * @param		dest	copy destination
 * @param		src		copy source
 */
static void		set_block(t_cell dest[BLOCK_SIZE][BLOCK_SIZE],
										t_cell src[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			dest[i][j] = src[i][j];
}

/**
 * @brief		set new block to now block
 * @param		type	block_type index
 */
void			set_new_block_now(int type)
{
	set_block(v.block_now, v.block_type[type]);
}

/**
 * @brief		set new block to next block
 * @param		type	block_type index
 */
void		set_new_block_next(int type1, int type2)
{
	set_block(v.block_next1, v.block_type[type1]);
	set_block(v.block_next2, v.block_type[type2]);
}

// -------------------------------------------------------------------------- //

/**
 * @brief		rotate block if can move
 * @param		y				block coord y
 * @param		x				block coord x
 * @param		rotate_right	true: rotate right / false: rotate left
 */
void			rotate_block(int y, int x, bool rotate_right)
{
	// [ variable ]
	t_cell	block_tmp[BLOCK_SIZE][BLOCK_SIZE];

	// [ rotate block ]
	// rotate & copy block ( block -> block_tmp )
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		{
			if (rotate_right)
				block_tmp[j][BLOCK_SIZE - 1 - i] = v.block_now[i][j];
			else
				block_tmp[BLOCK_SIZE - 1 - j][i] = v.block_now[i][j];
		}
	// judge collision
	if (judge_collision(block_tmp, y, x) != 0)
		return;
	// clear block ( block )
	clear_block(v.block_now, e.field_coord.y + y, e.field_coord.x + x);
	// copy block ( block_tmp -> block )
	set_block(v.block_now, block_tmp);
	// print block ( rotated block )
	draw_block(v.block_now, e.field_coord.y + y, e.field_coord.x + x);
}

// -------------------------------------------------------------------------- //

/**
 * @brief		write block data to field
 * @param		y	block coord y
 * @param		x	block coord x
 */
void			fix_block_to_field(int y, int x)
{
	// [ fix block to field ]
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
		if (can_use_cell(v.block_now[i][j], y + i, x + j) == 0)
			v.field[conv_field_coord(y+i, x+j)] = v.block_now[i][j];
}

// -------------------------------------------------------------------------- //

/**
 * @brief		judge if need to erase line
 * @param		y	line coord y
 * @return		true (need to erase): 0 / false (need not to erase): -1
 */
static int		need_to_erase_line(int y)
{
	// all cells filled in line ?
	for (int j = 0; j < e.field_size.width; j++)
		if (v.field[conv_field_coord(y, j)].c == '\0')
			return -1;
	// [ return ]
	return 0;
}

static void		erase_line(int y)
{
	// [ erase line from bottom to top ]
	for (int i = y; i > 0; i--)
		for (int j = 0; j < e.field_size.width; j++)
			v.field[conv_field_coord(i, j)] = v.field[conv_field_coord(i-1, j)];
	
	// [ redraw screen ]
	draw_back();
	draw_field();

	// [ return ]
	return;
}

/**
 * @brief		erase lines if filled by cell
 */
void			erase_lines(void)
{
	// [ need to erase line ? ]
	int erase_count = 0;
	for (int i = 0; i < e.field_size.height; i++)
		if (need_to_erase_line(i) == 0)
		{
			erase_line(i);
			erase_count++;
		}
	if (erase_count == 0)
		return;
	
	// [ update score (erase line) ]
	switch (erase_count)
	{
		case 1:
			v.score += ERASE_1LINE;
			break;
		case 2:
			v.score += ERASE_2LINE;
			break;
		case 3:
			v.score += ERASE_3LINE;
			break;
		case 4:
			v.score += ERASE_4LINE;
			break;
	}
	draw_score();

	// [ fall speed up ]
	v.fall_time_max -= v.fall_speed;

	// [ return ]
	return;
}