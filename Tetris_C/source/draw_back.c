/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:03:51 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 19:20:29 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

extern t_envs	e;

static void		set_random_color(void)
{
	int		rnd1;
	int		rnd2;
	// [ set char color ]
	rnd1 = CLR_BLACK;
	// rnd1 = choose_random(BLOCK_NUM);
	set_char_color(rnd1);
	// [ set back color ]
	do
		rnd2 = choose_random(BLOCK_NUM);
	while (rnd1 == rnd2);
	set_back_color(rnd2);
}

static void		draw_screen_back(void)
{
	// [ draw screen back ]
	set_random_color();
	set_attribute(ATR_BLIGHT);
	for (int i = 0; i < e.back_size.height; i++)
		for (int j = 0 ; j < e.back_size.width; j++)
		{
			set_position(e.back_coord.y + i, e.back_coord.x + j);
			printf("%c%c", '#', '#');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_field_back(void)
{
	// [ draw field back ]
	set_font_color_basic();
	for (int i = 0; i < e.field_size.height; i++)
		for (int j = 0; j < e.field_size.width; j++)
		{
			set_position(e.field_coord.y + i, e.field_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_next_back(void)
{
	// [ draw next back ]
	set_font_color_basic();
	for (int i = 0; i < NEXT_HEIGHT; i++)
		for (int j = 0; j < NEXT_WIDTH; j++)
		{
			set_position(e.next1_coord.y + i, e.next1_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
			set_position(e.next2_coord.y + i, e.next2_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

static void		draw_score_back(void)
{
	// [ draw score back ]
	set_font_color_basic();
	for (int i = 0; i < SCORE_HEIGHT; i++)
		for (int j = 0; j < SCORE_WIDTH; j++)
		{
			set_position(e.score_coord.y + i, e.score_coord.x + j);
			printf("%c%c", ' ', ' ');
			fflush(stdout);
		}
	set_font_color_default();
}

/**
 * @brief		draw_background
 * @return		none
 */
void			draw_back(void)
{
	// [ draw background ]
	clear_terminal();
	draw_screen_back();
	draw_field_back();
	draw_next_back();
	draw_score_back();
}
