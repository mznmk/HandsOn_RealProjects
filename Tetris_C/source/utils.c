/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 05:38:47 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 03:12:40 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

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
