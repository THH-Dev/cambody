#include "stdafx.h"
#include <stdio.h>  
#include <stdarg.h>  
#include <string>
using namespace std;
#include <stdio.h>
#include <time.h>


void my_log(const char *pszFormat, ...)
{
	char szBuffer[1024];
	char szFileName[300];
	memset(szFileName, 0, sizeof(szFileName));
	memset(szBuffer, 0, sizeof(szBuffer));
	// Fill in the time information
	time_t tTime;
	time(&tTime);
	tm* tmNow = localtime(&tTime);
	sprintf(szFileName, "D:/log_%.4d%.2d%.2d.log", tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday);

	sprintf(szBuffer, "%04d.%02d.%02d %02d:%02d:%02d ", 
		tmNow->tm_year + 1900, tmNow->tm_mon + 1, tmNow->tm_mday, 
		tmNow->tm_hour, tmNow->tm_min, tmNow->tm_sec);
	va_list argList;
	va_start(argList, pszFormat);
	vsprintf(szBuffer + 20, pszFormat, argList);
	va_end(argList);
	//	ASSERT(lstrlen(szBuffer) < 1024);
	FILE *fp = fopen(szFileName, "a+t");
	if (fp == NULL)
	{
		return;
	}
	fprintf(fp, "%s\n", szBuffer);
	printf("%s\n", szBuffer);
	fclose(fp);
	return;
}
