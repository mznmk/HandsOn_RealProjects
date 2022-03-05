/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 05:38:47 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 01:01:42 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_vars	v;

/*!
** @brief		choose random
** @param		size (choose range size)
** @return		random number
*/
int				choose_random(int size)
{
	// [ return ]
	return rand() % size;
}

// -------------------------------------------------------------------------- //

/**
 * @brief		set font color default
 */
void			set_font_color_default(void)
{
	set_char_color(CLR_DEFAULT);
	set_back_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
}

/**
 * @brief		set font color basic
 */
void			set_font_color_basic(void)
{
	set_char_color(CLR_BLACK);
	set_back_color(CLR_BLACK);
	set_attribute(ATR_NORMAL);
}

// -------------------------------------------------------------------------- //

int				is_filled_cell(t_cell cell)
{
	// [ cell is filled ? ]
	if (cell.c == '\0')
		return -1;
	return 0;
}

static int		is_cell_in_field(int y, int x)
{
	// [ cell is in field ? ]
	if ((0 <= y && y < e.field_size.height) && 
		(0 <= x && x < e.field_size.width))
		return 0;
	else
		return -1;
}

int				check_range(t_cell cell, int y, int x)
{
	if (cell.c == '\0')
		return -1;
	return is_cell_in_field(y, x);
}

int				check_cell(t_cell cell_self, int y, int x)
{
	if (check_range(cell_self, y, x) ||
		v.field[conv_field_coord(y, x)].c != '\0')
		return -1;

	return 0;
}
