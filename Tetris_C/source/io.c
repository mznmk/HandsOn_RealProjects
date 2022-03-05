/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 04:59:20 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/05 11:07:33 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/tetris.h"

/**
 * @brief		judge if certain key pressed ?
 * @return		1:true / 0:false
 */
int     		kbhit(void)
{
	fd_set          rfd;
	struct timeval  timeout = {0, 0};
	FD_ZERO(&rfd);
	FD_SET(STDIN_FILENO, &rfd);
	int ret = select(1, &rfd, NULL, NULL, &timeout);
	if (ret == 1)
		return 1;
	else
		return 0;
}

/**
 * @brief		receive keyboard input
 * @return		keycode of key pressed
 */
unsigned long	getch(void)
{
	unsigned long   keycode;
	int             rtn;
	while (42)
	{
		keycode = 0UL;
		rtn = read(STDIN_FILENO, &keycode, 8);
		if (!(rtn < 0))
			break;
	} 
	if (rtn == 0)
		return -1;
	else
		return keycode;
}
