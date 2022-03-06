/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:23 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/06 11:54:51 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/fifteen_puzzle.h"

extern t_envs	e;

/**
 * @brief		attach event to signal
 * @param sig	signal
 */
static void		handle_signal(int sig)
{
	// [ attach event to signal ]
	switch (sig)
	{
		case SIGINT:
		case SIGQUIT:
		case SIGTERM:
		case SIGHUP:
			exit_game();
			break;    
	}
}

/**
 * @brief		save terminal setting (termcap)
 * @return		true (success):0 / false (failure): -1
 */
static int		init_term(void)
{
	// [ save terminal setting ]
	if(tcgetattr(1, &e.otty) < 0)
		return -1;
	e.ntty = e.otty;
	e.ntty.c_iflag &= ~(INLCR|ICRNL|IXON|IXOFF|ISTRIP);
	e.ntty.c_oflag &= ~OPOST;
	e.ntty.c_lflag &= ~(ICANON|ECHO);
	e.ntty.c_cc[VMIN] = 1;
	e.ntty.c_cc[VTIME] = 0;
	tcsetattr(1, TCSADRAIN, &e.ntty);

	// [ return ]
	return 0;
}

/**
 * @brief		initialize game
  */
void			init_game(int argc, char **argv)
{
	// [ initialize environment variables ]
	init_envs(argc, argv);

	// [ allocate memory (field) ]
	allocate_memory();

	// [ initialize game variables ]
		
	// [ save terminal config (termcap) ]
	if (init_term() != 0)
		deallocate_memory();

	// [ set signal ]
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
	signal(SIGHUP, handle_signal);

	// [ set terminal config ]
	set_back_color(CLR_BLACK);
	set_char_color(CLR_WHITE);
	set_attribute(ATR_NORMAL);
	clear_terminal();
	cursol_off();
}
