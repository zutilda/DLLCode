#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#include <malloc.h>

#define PATH L"DLLCode.dll"

typedef int(_cdecl* MyFunctionCount)(int*);
typedef int(_cdecl* MyFunctionThreads)(int*, int);

int main(void)
{
	system("chcp 1251>nul");
	HINSTANCE hDLL;
	if ((hDLL = LoadLibrary(PATH)) == NULL) return 1;
	int* range = calloc(2, sizeof(int));
	int* result = calloc(2, sizeof(int));

	range[0] = 2;
	range[1] = 200000;
	int cT = 8;

	/*printf("Начало диапазона: ");
	scanf_s("%d", &range[0]);
	printf("\nКонец диапазона: ");
	scanf_s("%d", &range[1]);
	int cT = 0;
	printf("\nКоличество потоков: ");
	scanf_s("%d", &cT);*/

	if ((range[0] <= 1) || (range[1] < range[0])) return 2;
	MyFunctionCount FuncCount = (MyFunctionCount)GetProcAddress(hDLL, "Count");
	MyFunctionThreads FuncThread = (MyFunctionThreads)GetProcAddress(hDLL, "Threads");

	
	result = FuncCount(range);
	printf("Количество простых чисел без потоков: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}
	
	result = FuncThread(range, cT);
	printf("\nКоличество простых чисел с потоками: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}

	cT = 4;
	result = FuncThread(range, cT);
	printf("\nКоличество простых чисел с 4 потоками: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}
	cT = 6;
	result = FuncThread(range, cT);
	printf("\nКоличество простых чисел с 6 потоками: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}

	cT = 2;
	result = FuncThread(range, cT);
	printf("\nКоличество простых чисел с 2 потоками: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}
	FreeLibrary(hDLL);
	return 0;
}