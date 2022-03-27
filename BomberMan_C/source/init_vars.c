/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:48:50 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/27 21:05:59 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bomberman.h"

extern t_vars	v;

/*!
** @brief	initialize data container (field / hard block)
*/
static void		init_vars_field_hardblock(void)
{
	// [ initialize map ]
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++) {
			v.map[i][j] = FIELD;
			if (i == 0 || i == MAP_HEIGHT - 1 ||
				j == 0 || j == MAP_WIDTH - 1 ||
				(i % 2 == 0 && j % 2 == 0))
				v.map[i][j] = HARD_BLOCK;
		}
}

/*!
** @brief	initialize data container (player / enemy)
*/
static void		init_vars_player_enemy(void)
{
	// [ initialize player ]
	v.player.y = PLAYER_Y;
	v.player.x = PLAYER_X;
	v.player.life = PLAYER_LIFE;
	
	// [ initialize enemy ]
	for (int i = 0; i < ENEMY_COUNT; i++) {
		v.enemy[i].y = 0;
		v.enemy[i].x = 0;
		v.enemy[i].life = ENEMY_LIFE;
	}
	for (int i = 0; i < ENEMY_COUNT; i++) {
		bool can_set = false;
		while (!can_set) {
			int y = rand() % MAP_HEIGHT;
			int x = rand() % MAP_WIDTH;
			can_set = true;
			can_set &= !is_hard_block(y, x);
			can_set &= !is_player(y, x);
			can_set &= !is_enemy(y, x);
			if (can_set) {
				v.enemy[i].y = y;
				v.enemy[i].x = x;
			}
		}
	}
}

/*!
** @brief	initialize data container (door / soft block)
*/
static void		init_vars_door_softblock(void)
{
	// [ initialize softblock ]
	for (int i = 0; i < SOFTBLOCK_COUNT; i++) {
		v.softblock[i].y = 0;
		v.softblock[i].x = 0;
		v.softblock[i].life = SOFTBLOCK_LIFE;
	}
	for (int i = 0; i < SOFTBLOCK_COUNT; i++) {
		bool can_set = false;
		while (!can_set) {
			int y = rand() % MAP_HEIGHT;
			int x = rand() % MAP_WIDTH;
			can_set = true;
			can_set &= !is_hard_block(y, x);
			can_set &= !is_player(y, x);
			can_set &= !is_enemy(y, x);
			can_set &= !is_softblock(y, x);
			if (can_set) {
				v.softblock[i].y = y;
				v.softblock[i].x = x;
			}
		}
		// [ initialize door ]
		if (i == 0) {
			v.door.y = v.softblock[i].y;
			v.door.x = v.softblock[i].x;
			v.door.life = DOOR_LIFE;
		}
	}
}

// -------------------------------------------------------------------------- //

/*!
** @brief	initialize data container
*/
void			init_vars(void)
{
	init_vars_field_hardblock();
	init_vars_player_enemy();
	init_vars_door_softblock();
}