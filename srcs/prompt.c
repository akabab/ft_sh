/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/19 17:54:56 by ycribier          #+#    #+#             */
/*   Updated: 2015/02/19 17:55:08 by ycribier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	char	*pwd;
	char	*home;
	char	*home_ptr;
	char	*user;

	if ((pwd = get_env_value("PWD")))
	{
		home = get_env_value("HOME");
		user = get_env_value("USER");
		ft_printf("[%s:", user);
		if ((home_ptr = ft_strstr(pwd, home)))
			ft_printf("~%s]", home_ptr + ft_strlen(home));
		else
			ft_printf("%s]", pwd);
	}
	ft_putstr("$> ");
}
