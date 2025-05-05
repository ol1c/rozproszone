#include <unistd.h>
 #include <stdio.h>
 #define ODCZYT 0
 #define ZAPIS 1

 int main()
 {
    int potok1[2];
    int potok2[2];
    char buff[50];
    int buff_size = sizeof(buff);
    pipe(potok1);
    int proces2 = fork();
    if (proces2 < 0)
    {
        perror("fork");
        return 1;
    }
    if(proces2) // jeśli nie jest zero to znaczy że jest to proces 1
    {
        close(potok1[ODCZYT]);
        puts("P1 wczytuje string");
        scanf("%s", buff); 
        buff[buff_size-1] = '\0';
        write(potok1[ZAPIS], buff, buff_size);
        close(potok1[ZAPIS]);
        wait(NULL);
        wait(NULL);
    }
    else
    {
        pipe(potok2);
        int proces3 = fork();
        if (proces3 < 0)
        {
            perror("fork");
            return 1;
        }
        if(proces3)  // jeśli nie jest zero to znaczy że jest to proces 2
        {
            close(potok1[ZAPIS]);
            read(potok1[ODCZYT], buff, buff_size);
            puts("P2 odczytal i przetwarza");
            for(int i = 0; i < buff_size; i++) // zmiana znaków 'a' -> 'A'
            {
                if(buff[i] == '\0') break;
                if(buff[i] >= 'a' && buff[i] <='z')
                {
                    buff[i] -= 'a';
                    buff[i] += 'A';
                }
            }
            close(potok2[ODCZYT]);
            write(potok2[ZAPIS], buff, buff_size);
            close(potok2[ZAPIS]);
        }
        else // jest to proces 3
        {
            close(potok2[ZAPIS]);
            read(potok2[ODCZYT], buff, buff_size);
            puts("P3 odczytal:");
            printf("%s\n", buff);
            close(potok2[ZAPIS]);
        }
    }
        
 }