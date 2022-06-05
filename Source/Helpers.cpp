int intlen(int num)
{
	if (num == 0)
	{
		return 1;
	}

	int length = 0;

	while (num != 0)
	{
		length++;
		num = num / 10;
	}

	return length;
}
int isPrime(int num)
{
	if (num == 1)
	{
		return -1;
	}
	
	int i = 2;

	while (i * i <= num)
	{
		if (num % i == 0)
		{
			return i;
		}

		i++;
	}
	
	return 0;
}
