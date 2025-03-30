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
        funkcja_podprocesu(); // wywo�uje funkcje przeznaczon� dla podprocesu
    }
    else // uruchomienie programu bez argument�w
    {    // domy�lnie uruchomienie "g��wnego procesu"
        STARTUPINFO si;
        PROCESS_INFORMATION pi;

        // inicjalizacja struktur
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        wchar_t programPath[MAX_PATH]; // �cie�ka programu podprocesu
        GetModuleFileNameW(NULL, programPath, MAX_PATH); // pobrranie aktualnej �cie�ki

        wchar_t commandLine[MAX_PATH + 50]; // �cie�ka i argument uruchomienia programu podprocesu
        swprintf(commandLine, MAX_PATH + 50, L"\"%s\" podproces", programPath);

        // Tworzenie podprocesu
        if (!CreateProcess(
            NULL,   // Nazwa programu
            commandLine,   // Argumenty (NULL oznacza brak argument�w)
            NULL,          // Atrybuty bezpiecze�stwa procesu
            NULL,          // Atrybuty bezpiecze�stwa w�tku
            FALSE,         // Nie dziedziczy uchwyt�w
            0,             // Flagi tworzenia procesu
            NULL,          // Zmienne �rodowiskowe
            NULL,          // Katalog roboczy
            &si,           // Wska�nik do struktury STARTUPINFO
            &pi))          // Wska�nik do struktury PROCESS_INFORMATION
        {
            wprintf(L"B��d CreateProcess (%d).\n", GetLastError());
            return 1;
        }

        printf("Proces glowny uruchomil podproces.\n");

        // Oczekiwanie na zako�czenie podprocesu
        //WaitForSingleObject(pi.hProcess, INFINITE);

        // Zamkni�cie uchwyt�w do procesu i w�tku
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        Sleep(1000);

        printf("Proces glowny zakonczyl dzialanie.\n");
    }
    return 0;
}
