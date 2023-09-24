#include <stdio.h>
#include <Windows.h>

CRITICAL_SECTION g_lock;
int g_data = 0;

void thread_1(LPVOID arg)
{
	int count;
	for (count = 0; count < 100000; ++count) {
		EnterCriticalSection(&g_lock);
		++g_data;
		printf("g_data in t1 : %d\n", g_data);
		LeaveCriticalSection(&g_lock);
	}
}

void thread_2(LPVOID arg)
{
	int count;
	for (count = 0; count < 100000; ++count) {
		EnterCriticalSection(&g_lock);
		--g_data;
		printf("g_data in t2 : %d\n", g_data);
		LeaveCriticalSection(&g_lock);
	}
}

int main(void)
{
	DWORD tidOfT1 = 0;
	DWORD tidOfT2 = 0;
	HANDLE handleOfT1 = NULL;
	HANDLE handleOfT2 = NULL;
	printf("g_data : %d\n", g_data);
	InitializeCriticalSection(&g_lock);
	handleOfT1 = _beginthreadex(NULL, 0, thread_1, NULL, 0, &tidOfT1);
	handleOfT2 = _beginthreadex(NULL, 0, thread_2, NULL, 0, &tidOfT2);
	WaitForSingleObject(handleOfT1, INFINITE);
	WaitForSingleObject(handleOfT2, INFINITE);
	CloseHandle(handleOfT1);
	CloseHandle(handleOfT2);
	handleOfT1 = NULL;
	handleOfT2 = NULL;
	DeleteCriticalSection(&g_lock);
	printf("g_data : %d\n", g_data);
	return 0;
}