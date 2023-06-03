#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

	int N = 0,M = 0;
	int count = 0,total = 0;
	int max = 0;


	int card[100] = { 0 };

	srand((unsigned int)time(NULL));

	while (N < 3 || N>100 || M < 10 || M > 300000)
	{
		scanf_s("%d",&N);
		scanf_s("%d", &M);
	}

	for (int i = 0; i < N; i++)
	{
		card[i] = rand() % M;
		printf("%d		", card[i]);
	}

	while (total < M)
	{
		if (count < 3)
		{
			total += card[rand() % N];
			count++;
		}
		else 
		{
			max = total;

			printf("%d \n", max);

		}


	}











	return 0;
}