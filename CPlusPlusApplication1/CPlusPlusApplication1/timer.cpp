#define _CRT_SECURE_NO_WARNINGS
#define _AFXDLL
#include "afx.h"
#include <iostream>
#include <stdlib.h>

#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <afxmt.h>

unsigned long WINAPI Thread(PVOID  pvoid);
unsigned long WINAPI Thread_input(PVOID  pvoid);
CEvent g_event;

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

	while (hThread)
	{
		DWORD dwwait = WaitForSingleObject(g_event, 1000 * 10);
		boolean restartThread = false;
		switch (dwwait)
		{
		case WAIT_ABANDONED:
			printf("main thread waitForSingleObject return WAIT_ABANDONED\n");
			break;
		case WAIT_OBJECT_0:
			printf("main thread waitForSingleObject return WAIT_OBJECT_0\n");
			restartThread = true;
			break;
		case WAIT_TIMEOUT:
			printf("main thread waitForSingleObject return WAIT_TIMEOUT\n");
			break;
		}
		time_t timep;
		time(&timep);
		printf("%s", ctime(&timep));
		if (restartThread)
		{
			CloseHandle(hThread);
		    HANDLE hThread = CreateThread(
				NULL,    //   no   security   attributes      
				0,       //   use   default   stack   size        
				Thread,  //   thread   function      
				0,       //   argument   to   thread   function        
				0,       //   use   default   creation   flags      
				&dwThreadId);
		}
	}
	CloseHandle(hThread);
	_getch();
}

unsigned long WINAPI Thread(PVOID pvoid)
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	UINT timerid = SetTimer(NULL, 111, 5000, NULL);
	BOOL bRet;
	int count = 0;
	printf("work thread of timer start here\n");
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			count++;
			printf("WM_TIMER in work thread timer count=%d\n", count);
			if (count > 4)
				break;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			count++;
			printf("WM_TIMER in work thread timer count=%d\n", count);
			if (count > 10)
				break;
		}
	}
	g_event.SetEvent();
	KillTimer(NULL, timerid);
	printf("work thread of timer end here\n");
	return 0;
}

unsigned long WINAPI Thread_input(PVOID pvoid)
{
	MSG msg;
	PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
	BOOL bRet;
	int count = 0;
	printf("work thread of input start here\n");
	while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
		{
			count++;
			printf("WM_TIMER in work thread input count=%d\n", count);
			if (count > 4)
				break;
		}
		else
		{
			printf("Message type is %d\n", msg.message);
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			count++;
			printf("WM_TIMER in work thread input count=%d\n", count);
			if (count > 10)
				break;
		}
	}
	g_event.SetEvent();
	printf("work thread of input end here\n");
	return 0;
}