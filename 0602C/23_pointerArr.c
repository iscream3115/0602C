#include <stdio.h>


int main()
{

	//������ �迭

	int a = 10, b = 20, c = 30;
	int* pArr[3] = { &a, &b, &c };

	printf("%d\n", *pArr[0]);
	printf("%d\n", *pArr[1]);
	printf("%d\n\n", *pArr[2]);

	//�迭 ������ 

	int arr1[3] = { 0,1,2 };


	int arr2[2][3] = { {0,1,2},{3,4,5} };
	int arr3[3][3] = { {0,1,2},{3,4,5},{6,7,8}};

	//�̷��� ���� �׳� �� �� �ִ�. �ڿ� ��ȣ�� ���� ������� ���̴�. 
	int(*ptrArr)[3] = arr3;
	//ptrArr = arr3; �̰ſ� ��ǻ� ����

	for (int j = 0; j < 3; j++) printf("%d ", ptrArr[0][j]);
	printf("\n\n");

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%d,	", ptrArr[i][j]);
		}
		printf("\n");

	}

#pragma region ����
	{
		int i = 0;

		while (i != 4)
		{
			++i;
		}

	}
	{
		int a = 50;
		int* b;
		b = &a;
		*b += 20;
	}
	{
		int a[5];
		int* p = NULL;

		for (int i = 0; i < 5; i++)
			a[i] = i + 10;

		p = a;

		for (int i = 0; i < 5; i++)
		{
			printf("%d ", *(p + i));
			printf("%d ", p[i]);
		}
			
	}

	{



	}

#pragma endregion



	return 0;
}