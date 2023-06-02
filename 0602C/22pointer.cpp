#include <stdio.h>

void maxAndMin(int* arr, int size, int** minPtr, int** maxPtr);


int main()
{

	int arr[5];
	int* minPtr;
	int* maxPtr;


	for (int i = 0; i < 5; i++)
	{
		printf("���� �Է�: ");
		scanf_s("%d",&arr[i]);

	}

	maxAndMin(arr, 5, &minPtr, &maxPtr);

	printf("�ּ�: %d, �ִ�: %d", *minPtr, *maxPtr);

	return 0;
}

void maxAndMin(int* arr, int size, int** minPtr, int** maxPtr)
{
	int* max, * min;

	max = min = &arr[0];

	for (int i = 0; i < size; i++)
	{
		if (*max < arr[i]) max = &arr[i];
		if (*min > arr[i]) min = &arr[i];

	}

	*maxPtr = max;
	*minPtr = min;


}
