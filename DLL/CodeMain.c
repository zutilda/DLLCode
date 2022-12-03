#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <stdio.h>
#define PATH L"DLLCode.dll"

typedef int(_cdecl* MyFunctionCount)(int*);
typedef int(_cdecl* MyFunctionThreads)(int*, int);

int main(void)
{
	system("chcp 1251>nul");
	HINSTANCE hDLL;
	if ((hDLL = LoadLibrary(PATH)) == NULL) return 1;
	int* range = calloc(2, sizeof(int));

	range[0] = 2;
	range[1] = 100000;
	int cT = 7;

	/*printf("������ ���������: ");
	scanf_s("%d", &range[0]);
	printf("\n����� ���������: ");
	scanf_s("%d", &range[1]);
	int cT = 0;
	printf("\n���������� �������: ");
	scanf_s("%d", &cT);*/

	if ((range[0] <= 1) || (range[1] < range[0])) return 2;
	MyFunctionCount FuncCount = (MyFunctionCount)GetProcAddress(hDLL, "Count");
	int* result = calloc(2, sizeof(int));
	result = FuncCount(range);
	printf("���������� ������� ����� ��� �������: \n");
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", result[i]);
	}
	printf("\n���������� ������� ����� � ��������: \n");
	MyFunctionThreads FuncThread = (MyFunctionThreads)GetProcAddress(hDLL, "Threads");
	int* resultT = calloc(2, sizeof(int));
	resultT = FuncThread(range, cT);
	for (int i = 0; i < 2; i++)
	{
		printf("%d\n", resultT[i]);
	}
	FreeLibrary(hDLL);
	return 0;
}