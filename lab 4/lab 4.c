#include <windows.h>
#include <stdio.h>

void funkcja_podprocesu()
{
    Sleep(3000);
    printf("Tutaj podproces\n");
    Sleep(1000);
}

int main(int argc, char** argv)
{
    if (argc > 1) // uruchomienie programu z argumentem
    {
        funkcja_podprocesu(); // wywo³uje funkcje przeznaczon¹ dla podprocesu
    }
    else // uruchomienie programu bez argumentów
    {    // domyœlnie uruchomienie "g³ównego procesu"
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        // inicjalizacja struktur
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        wchar_t programPath[MAX_PATH]; // œcie¿ka programu podprocesu
        GetModuleFileNameW(NULL, programPath, MAX_PATH); // pobrranie aktualnej œcie¿ki

        wchar_t commandLine[MAX_PATH + 50]; // œcie¿ka i argument uruchomienia programu podprocesu
        swprintf(commandLine, MAX_PATH + 50, L"\"%s\" podproces", programPath);

        // Tworzenie podprocesu
        if (!CreateProcess(
            NULL,   // Nazwa programu
            commandLine,   // Argumenty (NULL oznacza brak argumentów)
            NULL,          // Atrybuty bezpieczeñstwa procesu
            NULL,          // Atrybuty bezpieczeñstwa w¹tku
            FALSE,         // Nie dziedziczy uchwytów
            0,             // Flagi tworzenia procesu
            NULL,          // Zmienne œrodowiskowe
            NULL,          // Katalog roboczy
            &si,           // WskaŸnik do struktury STARTUPINFO
            &pi))          // WskaŸnik do struktury PROCESS_INFORMATION
        {
            wprintf(L"B³¹d CreateProcess (%d).\n", GetLastError());
            return 1;
        }

        printf("Proces glowny uruchomil podproces.\n");

        // Oczekiwanie na zakoñczenie podprocesu
        //WaitForSingleObject(pi.hProcess, INFINITE);

        // Zamkniêcie uchwytów do procesu i w¹tku
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        Sleep(1000);

        printf("Proces glowny zakonczyl dzialanie.\n");
    }
    return 0;
}
