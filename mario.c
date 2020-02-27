
#include <stdio.h>

int		main(void)
{
	float			test;
	unsigned int	*bits;
	int				iter;

	test = 893759835.8476;
	bits = &test;
	iter = 0;
	printf("\e[1;31mAS FLOAT: %.24f\nAS DIGIT: %d\e[0;36m\n\n", test, *bits);
	while (iter < 32)
	{
		printf("%d", *bits << iter >> 31);
		if (iter == 0 || iter == 8)
			printf(" ");
		iter++;
	}
	printf("\e[0m\n");
}
