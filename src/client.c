#include "minitalk.h"

void	ft_send(pid_t pid, int *b)
{
	int	i;

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

int   ft_transcript(pid_t pid, char *s)
{
	int i;
	int *b;

	i = 0;
	while (s[i] != '\0')
	{
		b = ft_dec_to_bin((int)s[i]);
		ft_send(pid, b);
		i++;
	}
	b = ft_dec_to_bin((int)'\0');
	ft_send(pid, b);
  return (0);
}

int   main(int ac, char **av)
{
  pid_t pid;

	if (ac == 3)
  {
    pid = ft_atoi(av[1]);
    if (pid == 0 || pid == -1)
		  ft_putendl_fd("Invalid PID", 2);
    else
		  return (ft_transcript(pid, av[2]));
  }
	else
		ft_putendl_fd("Usage: ./client PID message", 2);
	return (1);
}