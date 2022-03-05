/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_tetris.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 11:08:05 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 00:56:54 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/**
 * @brief 		load terminal setting (termcap)
 */
static void		fin_term(void)
{
	// [ load terminal setting ]
	tcsetattr(1, TCSADRAIN, &e.otty);
	write(1, "\n", 1);
}

/**
 * @brief		finalize tetris
 */
void			fin_tetris(void)
{
	// [ reset terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_on();

	// [ load terminal config (termcap) ]
	fin_term();

	// [ deallocate memory (field) ]
	deallocate_memory();
}
