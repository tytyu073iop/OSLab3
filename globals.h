#ifndef GLOBAL_WORLD
#define GLOBAL_WORLD

#include <Windows.h>

extern HANDLE* eventsArr;
extern HANDLE* continueEventsArr;
extern HANDLE* endEventsArr;
extern CRITICAL_SECTION* css;
extern CRITICAL_SECTION iocs;

#endif