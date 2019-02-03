/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguiot-- <aguiot--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:53:42 by aguiot--          #+#    #+#             */
/*   Updated: 2019/02/03 17:18:00 by aguiot--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int						*g_binary;

static void	ft_print_header(void)
{
	pid_t				pid;

	pid = getpid();
	ft_putstr("You can now send messages with: ./client "C_MAGENTA);
	ft_putnbr(pid);
	ft_putendl(C_NONE" \"message\""C_NONE);
}

static char	*ft_decode_append(char *str, int *tmp, int seqcount)
{
	static int	i = 0;

	if (i > BUFF_SIZE)
		str = ft_realloc(str, sizeof(char) * (ft_strlen(str) + BUFF_SIZE));
	while (seqcount > 0)
	{
		str[i++] = (char)ft_bin_to_dec(tmp);
		--seqcount;
	}
	if ((char)ft_bin_to_dec(tmp) == '\0')
	{
		ft_putstr(C_CYAN"Ping from PID ");
		ft_putnbr(ft_ping_getset(0, 0));
		ft_putendl(" !"C_NONE);
		ft_putendl(str);
		kill(ft_ping_getset(0, 0), SIGUSR1);
		i = 0;
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
	int					seqcount;
	int					seqmode;

	g_binary = (int*)(malloc(sizeof(int) * 8));
	str = (char*)malloc(sizeof(char) * BUFF_SIZE);
	ft_bzero(g_binary, 8);
	tmp = g_binary;
	ft_print_header();
	ft_handle_sigusr();
	seqmode = 0;
	i = 0;
	while (1)
	{
		if (i == 8 && seqmode == 0)
		{
			g_binary -= 8;
			seqcount = ft_bin_to_dec(g_binary);
			seqmode = 1;
			i = 0;
		}
		if (i == 8 && seqmode == 1)
		{
			str = ft_decode_append(str, tmp, seqcount);
			seqcount = 0;
			seqmode = 0;
			i = 0;
		}
		++i;
		pause();
	}
	free(g_binary);
	free(str);
	return (0);
}
