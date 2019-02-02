#include "minitalk.h"

int		*ft_dec_to_bin(int dec)
{
	int	*bin;
	int	i;

	bin = (int*)malloc(sizeof(int) * 8);
  ft_bzero(bin, 8);
	i = 0;
	while (dec > 0)
	{
		bin[i++] = dec % 2;
		dec /= 2;
	}
	return (bin);
}

int		ft_bin_to_dec(int *bin)
{
	int	dec;
	int	i;

	dec = 0;
	i = 0;
	while (i < 8)
	{
    dec += bin[i] * ft_pow(2, i);
    ++i;
  }
	return (dec);
}
