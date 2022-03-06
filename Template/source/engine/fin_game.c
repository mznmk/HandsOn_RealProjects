/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fin_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:08 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 11:38:14 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/template.h"

extern t_envs	e;

/**
 * @brief 		save terminal setting (termcap)
 */
static void		fin_term(void)
{
	// [ save terminal setting ]
	tcsetattr(1, TCSADRAIN, &e.otty);
	write(1, "\n", 1);
}

/**
 * @brief		finalize game
 */
void			fin_game(void)
{
	// [ reset terminal config ]
	set_back_color(CLR_DEFAULT);
	set_char_color(CLR_DEFAULT);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_on();

	// [ load terminal config (termcap) ]
	fin_term();

	// [ deallocate memory (field) ]
	deallocate_memory();
}
