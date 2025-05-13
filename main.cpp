#include "maker.h"
#include "comunication.h"
#include "globals.h"
#include <iostream>

int main() {
    std::cout << "enter size of array: ";
    size_t size;
    std::cin >> size;
    
    int* arr = new int[size]{0};
    
    std::cout << "how much makers to run: ";
    size_t amountOfMakers;
    std::cin >> amountOfMakers;
    
    eventsArr = new HANDLE[amountOfMakers];
    continueEventsArr = new HANDLE[amountOfMakers];
    endEventsArr = new HANDLE[amountOfMakers];
    HANDLE* threads = new HANDLE[amountOfMakers];
    css = new CRITICAL_SECTION[size];
    for (size_t i = 0; i < size; i++)
    {
        InitializeCriticalSection(&css[i]);
    }
    
    InitializeCriticalSection(&iocs);
    for (size_t i = 0; i < amountOfMakers; i++)
    {
        eventsArr[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (eventsArr[i] == NULL) {
            std::cout << "error creating event for: i=" << i << " code: " << GetLastError() << '\n';
        }
        continueEventsArr[i] =  CreateEvent(NULL, FALSE, FALSE, NULL);
        endEventsArr[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        Comunication* c = new Comunication{.arr = arr, .size = size, .pos = i}; 
        auto h = CreateThread(NULL, 0, maker, c, NULL, NULL);
        if (h == NULL) {
            std::cout << "ERROR!!! in thread creation: " << GetLastError() << '\n';
            ExitProcess(1);
        }
        
        threads[i] = h;
        
    }
    
    for (DWORD j = amountOfMakers; j > 0; j--) {
        auto c = WaitForMultipleObjects(j, eventsArr, TRUE, INFINITE);
        if (c == WAIT_FAILED) {
            std::cout << "wait error: " << GetLastError() << '\n';
            ExitProcess(1);
        }
        
        std::cout << "array: ";
        for (size_t i = 0; i < size; i++)
        {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';
        
        std::cout << "who to kill: ";
        size_t whoKill;
        std::cin >> whoKill;
        
        if (!SetEvent(endEventsArr[whoKill])) {
            std::cout << "Error killing: " << GetLastError() << '\n';
        }
        
        WaitForSingleObject(threads[whoKill], INFINITE);
        if (!CloseHandle(threads[whoKill])) {
            std::cout << "Can't close handle: " << GetLastError() << '\n';
        }
        std::cout << "array: ";
        for (size_t i = 0; i < size; i++)
        {
            std::cout << arr[i] << ' ';
        }
        std::cout << '\n';

        eventsArr[whoKill] = eventsArr[j - 1];
        
        for (size_t i = 0; i < amountOfMakers; i++)
        {
            if (!SetEvent(continueEventsArr[i])) {
                std::cout << "Can't set event: " << GetLastError() << '\n';
            }
        }
        
    }
    
}