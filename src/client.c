/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:27 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 14:34:36 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_send_char(pid_t pid, int *b)
{
	int		i;

	i = 0;
	while (i < 8)
	{
		if (b[i] == 0)
		{
			if (kill(pid, SIGUSR1) == -1)
			{
				ft_putendl_fd("An error occured while sending bit '0'.", 2);
				exit(1);
			}
		}
		if (b[i] == 1)
		{
			if (kill(pid, SIGUSR2) == -1)
			{
				ft_putendl_fd("An error occured while sending bit '1'.", 2);
				exit(1);
			}
		}
		usleep(150);
		i++;
	}
}

static int	ft_send_word(pid_t pid, char *s)
{
	int		i;
	int		*b;

	i = 0;
	while (s[i] != '\0')
	{
		b = ft_dec_to_bin((int)s[i]);
		ft_send_char(pid, b);
		i++;
	}
	b = ft_dec_to_bin((int)'\0');
	ft_send_char(pid, b);
	return (0);
}

int			main(int ac, char **av)
{
	pid_t	pid;

	ft_handle_pong();
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (pid == 0 || pid == -1)
			ft_putendl_fd("Invalid PID", 2);
		else
			return (ft_send_word(pid, av[2]));
	}
	else
		ft_putendl_fd("Usage: ./client PID message", 2);
	return (1);
}
