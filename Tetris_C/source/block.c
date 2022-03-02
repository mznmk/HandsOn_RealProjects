/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:22:11 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/02 12:47:42 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

int check_range(t_cell cell, int y, int x)
{
	if (cell.c == '\0')
		return -1;
	if ((0 <= y && y < FLD_HEIGHT) && (0 <= x && x < FLD_WIDTH))
		return 0;
	else
		return -1;
}

int	print_cell(t_cell cell, int y, int x)
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

int	clear_cell(t_cell cell, int y, int x)
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
int		print_block(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			print_cell(v->block[i][j], y + i, x + j);
	return 0;
}

int		clear_block(t_vars *v, int y, int x)
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			clear_cell(v->block[i][j], y + i, x + j);
	return 0;
}

void	copy_block(t_vars *v, t_cell src[BLOCK_SIZE][BLOCK_SIZE])
{
	for (int i = 0; i < BLOCK_SIZE; i++)
		for (int j = 0; j < BLOCK_SIZE; j++)
			v->block[i][j] = src[i][j];
	return;
}
