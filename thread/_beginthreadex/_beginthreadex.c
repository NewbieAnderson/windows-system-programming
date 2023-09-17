#include <stdio.h>
#include <Windows.h>

int g_data = 12;

DWORD WINAPI routine(LPVOID arg)
{
    int i;
    printf("message : \"%s\"\n", (const char*)arg);
    for (i = 0; i < 10; ++i)
        ++g_data;
    printf("g_data in new thread %d\n", g_data);
    return 0;
}

int main(void)
{
    DWORD tid = 0;
    HANDLE threadHandle = NULL;
    const char* msg = "_beginthreadex()!";
    /*
        more recommanded than CreateThread()
        TLS(Therad Local Storage) is applied and thread-safe.
    */
    threadHandle = _beginthreadex(NULL, 0, routine, (LPVOID)msg, 0, &tid);
    if (threadHandle == NULL) {
        printf("failed to create new thread!\n");
        return 1;
    }
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    threadHandle = NULL;
    printf("g_data in main thread : %d\n", g_data);
    return 0;
}