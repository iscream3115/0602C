#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int card[] = { 0 };

int main()
{
	int N = 0,M = 0;
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
		scanf_s("%d", &card[i]);
	}

	//재귀함수로
	//for (int i = 0; i < N; i++)
	//{
	//	blackjack(0, i, 1);

	//	if (max == 0) break;
	//}

	for (int i = 0; i < N - 2; i++)
	{
		for (int j = i + 1; j < N - 1; j++)
		{
			for (int k = j + 1; k < N; k++)
			{
				if (max < (card[i] + card[j] + card[k]) && (card[i] + card[j] + card[k]) <= M)
				{
					max = card[i] + card[j] + card[k];
					//printf("합계: %d, 뽑은 숫자: %d %d %d\n", max, card[i], card[j], card[k]);
				}

			}

		}

	}

	printf("%d\n", max);

	return 0;
}


void blackjack(int sum, int curr, int count)
{

	

}