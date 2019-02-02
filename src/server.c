/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:42 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/02 21:48:19 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int						*g_binary;

static void	ft_print_header(void)
{
	pid_t				pid;

	pid = getpid();
	ft_putstr("You can now send messages with: ./client ");
	ft_putnbr(pid);
	ft_putendl(" \"message\"");
}

static char	*ft_binary(char *str, int *tmp)
{
	static int	buff = 0;

	if (buff > 510)
		str = ft_realloc(str, BUFF_SIZE);
	str[buff++] = (char)ft_bin_to_dec(tmp);
	if ((char)ft_bin_to_dec(tmp) == '\0')
	{
		ft_putstr("Ping from PID ");
		ft_putnbr(ft_ping_getset(0, 0));
		ft_putendl(" !");
		ft_putendl(str);
		kill(ft_ping_getset(0, 0), SIGUSR1);
		buff = 0;
	}
	g_binary = tmp;
	ft_bzero(g_binary, 8);
	return (str);
}

static void	ft_sigusr_handler(int sig, siginfo_t *info, void *cont)
{
	*g_binary++ = (sig == SIGUSR2);
	ft_ping_getset(1, info->si_pid);
	(void)cont;
}

static void	ft_handle_sigusr(void)
{
	struct sigaction	action;

	action.sa_sigaction = ft_sigusr_handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}

int			main(void)
{
	int					i;
	int					*tmp;
	char				*str;

	i = 0;
	g_binary = (int*)(malloc(sizeof(int) * 8));
	str = (char*)malloc(sizeof(char) * BUFF_SIZE);
	ft_bzero(g_binary, 8);
	tmp = g_binary;
	ft_print_header();
	ft_handle_sigusr();
	while (1)
	{
		if (i > 7)
		{
			str = ft_binary(str, tmp);
			i = 0;
		}
		pause();
		i++;
	}
	free(g_binary);
	free(str);
	return (0);
}
