/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: intonoya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 15:50:33 by intonoya          #+#    #+#             */
/*   Updated: 2022/09/28 16:55:32 by intonoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

static void	ft_action(int sig)
{
	static int	i = 0;

	if (sig == SIGUSR1)
		++i;
	else
	{
		ft_putnbr_fd(i, 1);
		ft_putchar_fd('\n', 1);
		exit(0);
	}
}

static void	ft_kill(int pid, char *str)
{
	int		i;
	char	c;

	while (*str)
	{
		i = 8;
		c = *str++;
		while (i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			usleep(100);
		}	
	}
	i = 8;
	while (i--)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}	
}

int	main(int argc, char **argv)
{
	char	*tmp;

	if (argc != 3 || !ft_strlen(argv[2]))
		return (1);
	ft_putstr_fd("Sent: ", 1);
	ft_putnbr_fd(ft_strlen(argv[2]), 1);
	ft_putchar_fd('\n', 1);
	ft_putstr_fd("Received: ", 1);
	signal(SIGUSR1, ft_action);
	signal(SIGUSR2, ft_action);
	tmp = ft_strjoin(argv[2], "\n");
	ft_kill(ft_atoi(argv[1]), tmp);
	while (1)
		pause();
	free(tmp);
	return (0);
}
