#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <malloc.h>
#include <time.h>

BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}

HANDLE* threads = NULL;
int result = 0;
int* arr = 0;
int countThread = 0;
CRITICAL_SECTION section = { 0 };

extern __declspec(dllimport) int Count(int*);

int Count(int* n)
{
	arr = calloc(2, sizeof(int));
	
	EnterCriticalSection(&section);
	for (n[0]; n[0] <= n[1]; n[0]++)
	{
		
		int  k = 0;
		for (int i = 2; i < n[0]; i++)
		{
			if (n[0] % i == 0) k++;
			else k += 0;
		}
		if (k == 0) result++;
		else result += 0;
		
	}	
	
	
	if (threads != NULL)
	{
		for (int i = 0; i < countThread; i++)
		{
			LeaveCriticalSection(&section);
			ExitThread(0);
		}
	}
	else
	{
		arr[0] = result;
		arr[1] = clock();
		return arr;
	}
	
}

extern __declspec(dllimport) int Threads(int*, int);

int Threads(int* n, int countTreads)
{

	threads = calloc(countTreads, sizeof(HANDLE));
	countThread = countTreads;
	DWORD lpThreadId;
	InitializeCriticalSection(&section);
	for (int i = 0; i < countThread; i++)
	{
		
		threads[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Count, n, 0, &lpThreadId);
	}
	WaitForMultipleObjects(1, threads, TRUE, INFINITE);
	DeleteCriticalSection(&section);

	arr[0] = result;
	arr[1] = clock();

	return arr;

}