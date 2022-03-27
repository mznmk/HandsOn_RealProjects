/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 18:34:33 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/27 21:08:21 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bomberman.h"

extern t_vars		v;

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

static void		draw_field(int y, int x)
{
	set_position(y, x);
	set_char_color(CLR_GREEN);
	set_back_color(CLR_GREEN);
	set_attribute(ATR_REVERSE);
	printf("%c%c" , ' ', ' ');
	fflush(stdout);
}

static void		draw_hard_block(int y, int x)
{
	set_position(y, x);
	set_char_color(CLR_WHITE);
	set_back_color(CLR_WHITE);
	set_attribute(ATR_REVERSE);
	printf("%c%c" , ' ', ' ');
	fflush(stdout);
}

static void		draw_screen(void)
{
	set_font_color_default();
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (v.map[i][j] == FIELD) {
				draw_field(i, j);
			}
			else if (v.map[i][j] == HARD_BLOCK) {
				draw_hard_block(i, j);
			}
		}
	}
	set_font_color_default();
}

/**
 * @brief		draw_background
 */
void			draw_back(void)
{
	// [ draw background ]
	draw_screen();
}

// -------------------------------------------------------------------------- //

static void		draw_player(void)
{
	set_font_color_default();
	set_position(v.player.y, v.player.x);
	set_char_color(CLR_BLACK);
	set_back_color(CLR_GREEN);
	set_attribute(ATR_BLIGHT);
	printf("%c%c" , 'P', 'L');
	fflush(stdout);
	set_font_color_default();
}

static void		draw_enemy(void)
{
	set_font_color_default();
	for (int i = 0; i < ENEMY_COUNT; i++) {
		set_position(v.enemy[i].y, v.enemy[i].x);
		set_char_color(CLR_BLACK);
		set_back_color(CLR_GREEN);
		set_attribute(ATR_BLIGHT);
		printf("%c%c" , 'E', 'N');
		fflush(stdout);
	}
	set_font_color_default();
}

static void		draw_softblock(void)
{
	set_font_color_default();
	for (int i = 0; i < SOFTBLOCK_COUNT; i++) {
		set_position(v.softblock[i].y, v.softblock[i].x);
		set_char_color(CLR_WHITE);
		set_back_color(CLR_GREEN);
		set_attribute(ATR_BLIGHT);
		printf("%c%c" , '#', '#');
		fflush(stdout);
	}
	set_font_color_default();
}

static void		draw_door(void)
{
	set_font_color_default();
	set_position(v.door.y, v.door.x);
	set_char_color(CLR_RED);
	set_back_color(CLR_GREEN);
	set_attribute(ATR_BLIGHT);
	printf("%c%c" , '[', ']');
	fflush(stdout);
	set_font_color_default();
}

/**
 * @brief		draw_charactor
 */
void			draw_chara(void)
{
	draw_player();
	draw_enemy();
	draw_softblock();
	draw_door();
}