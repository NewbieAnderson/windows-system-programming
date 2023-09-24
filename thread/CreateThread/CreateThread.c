#include <stdio.h>
#include <Windows.h>

DWORD WINAPI routine(LPVOID arg)
{
    printf("message : \"%s\"\n", (const char*)arg);
    return 0;
}

int main(void)
{
    DWORD tid = 0;
    HANDLE threadHandle = NULL;
    const char* msg = "CreateThread()!";
    /* _beginthreadex() is more recommended! */
    threadHandle = CreateThread(NULL, 0, routine, (LPVOID)msg, 0, &tid);
    if (threadHandle == NULL) {
        printf("failed to create new thread!\n");
        return 1;
    }
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    threadHandle = NULL;
    return 0;
}