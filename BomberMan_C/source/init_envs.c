/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_envs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmizuno <mmizuno@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:38:48 by mmizuno           #+#    #+#             */
/*   Updated: 2022/03/27 17:15:16 by mmizuno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/bomberman.h"

extern t_envs	e;

/**
 * @brief		initialize environment variables
** @param		argc	argument count
** @param		argv	argument contents
 */
void			init_envs(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	printf("init envs!\n");
}