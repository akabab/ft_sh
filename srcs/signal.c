/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/09 23:31:54 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/20 15:53:15 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

void			signal_reset(void)
{
	signal(SIGINT, SIG_DFL);
}

void			sigint_one(int sig)
{
	if (sig == SIGINT)
		ft_putchar('\n');
}

void			sigint_two(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
	}
}
