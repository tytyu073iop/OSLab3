#include "maker.h"
#include "comunication.h"
#include "globals.h"
#include <random>
#include <iostream>

DWORD WINAPI maker(LPVOID comm) {
    Comunication* obj = reinterpret_cast<Comunication*>(comm);

    srand(obj->pos);

    size_t pom = 0;

    while (true) {
        int number = std::rand() % obj->size;
        EnterCriticalSection(&css[number]);
        if (obj->arr[number] == 0) {
            Sleep(5);
            obj->arr[number] = obj->pos + 1;
            Sleep(5);
            pom++;
            LeaveCriticalSection(&css[number]);
        } else {
            LeaveCriticalSection(&css[number]);
            EnterCriticalSection(&iocs);
            std::cout << "object: " << obj->pos << ' ' << pom << ' ' << number << '\n';
            LeaveCriticalSection(&iocs);

            if (!SetEvent(eventsArr[obj->pos])) {
                std::cout << "error: " << GetLastError() << '\n';
                exit(1);
            }
            HANDLE myHandles[]{continueEventsArr[obj->pos], endEventsArr[obj->pos]};
            DWORD event = WaitForMultipleObjects(2, myHandles, FALSE, INFINITE) - WAIT_OBJECT_0;
            if (event == 1) {
                for (size_t i = 0; i < obj->size; i++)
                {
                    if(obj->arr[i] == obj->pos + 1) {
                        obj->arr[i] = 0;
                    }
                }
                
                break;
            }
        }
    }
}