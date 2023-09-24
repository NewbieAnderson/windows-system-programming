#include <stdio.h>
#include <Windows.h>

DWORD WINAPI routine(LPVOID arg)
{
    printf("Awaken!\n");
    return 0;
}

int main(void)
{
    DWORD tid = 0;
    HANDLE threadHandle = NULL;
    threadHandle = _beginthreadex(NULL, 0, routine, NULL, 0, &tid);
    if (threadHandle == NULL) {
        printf("failed to create new thread!\n");
        return 1;
    }
    SuspendThread(threadHandle);
    printf("Sleeping for 5 seconds...\n");
    Sleep(5000);
    ResumeThread(threadHandle);
    WaitForSingleObject(threadHandle, INFINITE);
    CloseHandle(threadHandle);
    threadHandle = NULL;
    return 0;
}