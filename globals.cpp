#include "globals.h"

// Реальное определение переменных
HANDLE* eventsArr = nullptr;
HANDLE* continueEventsArr = nullptr;
HANDLE* endEventsArr = nullptr;
CRITICAL_SECTION* css = nullptr;
CRITICAL_SECTION iocs;