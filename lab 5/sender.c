#include <windows.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

#define WM_MY_MESSAGE (WM_USER + 1) // w³asny komunikat

int main() {
    HWND hwndReceiver = FindWindow(NULL, L"Receiver Window");

    if (hwndReceiver == NULL) {
        printf("Nie znaleziono okna odbiorcy!\n");
        return 1;
    }

    SendMessage(hwndReceiver, WM_MY_MESSAGE, 0, 0);

    printf("Wyslano komunikat do Receiver.\n");
    return 0;
}