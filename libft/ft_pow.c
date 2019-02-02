int   ft_pow(int x, int y)
{
	int p;

	p = 1;
	while (y > 0)
	{
		p = p * x;
		y--;
	}
	return (p);
}
