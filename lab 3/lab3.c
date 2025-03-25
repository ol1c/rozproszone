#include <unistd.h>
#include <stdio.h>

int main()
{
    printf("Tutaj: %d - ", getpid()); // wyświetlenie, który proces aktualnie się wykonuje

    int pid = fork(); // utworzenie procesu potomnego, który jest kopią tego macierzystego
                      // od tego momentu zaczyna się wykonywać podproces
                      
    printf("Tutaj: %d - ", getpid()); // wyświetlenie, który proces aktualnie się wykonuje
    
    if (pid < 0) // sprawdzenie czy nie wystąpił błąd przy tworzeniu procesu
    {
        perror("Blad utworzenia procesu potomnego!");
        return 1;
    }
    else if (pid == 0) // sprawdzenie czy jest to proces potomny
    {
        printf("Jestem podprocesem procesu: %d\n", getppid());
        sleep(5);
        return 0;
    }
    else // jeśli nie jest to proces potomny jest to proces macierzysty
    {
        waitpid(pid, NULL, 0);
        printf("Podproces: %d sie skonczyl\n", pid); // w tym przypadku pid przechowuje id podprocesu
        return 0;
    }
}