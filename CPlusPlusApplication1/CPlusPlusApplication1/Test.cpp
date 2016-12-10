#define _CRT_SECURE_NO_WARNINGS

//#include "afx.h"
#include <iostream>
#include <stdlib.h>

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

/*
unsigned long WINAPI Thread(PVOID  pvoid);

void main()
{
	DWORD dwThreadId;
	printf("use timer in workthread of console application<masterz>\n");
	HANDLE hThread = CreateThread(
		NULL,    //   no   security   attributes      
		0,       //   use   default   stack   size        
		Thread,  //   thread   function      
		0,       //   argument   to   thread   function        
		0,       //   use   default   creation   flags      
		&dwThreadId);
	
	int timerTimes = 0;

	while (timerTimes ++ <=5)
	{
		DWORD dwwait = WaitForSingleObject(hThread, 1000 * 5);
		switch (dwwait)
		{
		case WAIT_ABANDONED:
			printf("main thread waitForSingleObject return WAIT_ABANDONED\n");
			break;
		case WAIT_OBJECT_0:
			printf("main thread waitForSingleObject return WAIT_OBJECT_0\n");
			break;
		case WAIT_TIMEOUT:
			printf("main thread waitForSingleObject return WAIT_TIMEOUT\n");
			break;
		}
		time_t timep;
		time(&timep);
		printf("%s", ctime(&timep));
		
	}
	CloseHandle(hThread);
	_getch();
}

unsigned long WINAPI Thread(PVOID pvoid)
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	UINT timerid = SetTimer(NULL, 111, 3000, NULL);
	BOOL bRet;
	int count = 0;
	printf("thread start here\n");
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			count++;
			printf("WM_TIMER in work thread count=%d\n", count);
			if (count > 4)
				break;
		}
		else 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	KillTimer(NULL, timerid);
	printf("thread end here\n");
	return 0;
}

*/