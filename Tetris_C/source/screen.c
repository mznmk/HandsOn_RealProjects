/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 00:07:13 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/03 07:10:32 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/tetris.h"

void	init_screen(void)
{
	// [ save terminal config (termcap) ]
	tinit();

	// [ set terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_board();
	cursol_off();

	// [ return ]
	return;
}

void	reset_screen(void)
{
	// [ reset terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_board();
	cursol_on();

	// [ load terminal config (termcap) ]
	tfinal();

	// [ return ]
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