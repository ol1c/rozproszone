#include <stdio.h>
#include <pthread.h>
#include <math.h>

void is_prime(int x) // funkcja sprawdza czy liczba x jest liczbą pierwszą
{                    // jeśli tak to wypisuje ją na output
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
            return;
    }
    printf("%d\n", x);
}

void *f_thread(void *arg) // funkcja wątku
{
    int x = ((int *)arg)[0];
    int next[] = {x + 1,            // kolejna liczba do sprawdzenia
                  ((int *)arg)[1]}; // skopiowanie granicy
    pthread_t w;
    if (next[0] <= ((int *)arg)[1]) // sprawdzenie czy doszliśmy do granicy
    {
        pthread_create(&w, NULL, f_thread, &next); // tworzenie kolejnego wątklu z nowymi argumentami
    }
    is_prime(x); // funkcja sprawdzająca czy liczba jest pierwsza
    if (next[0] <= ((int *)arg)[1])
    {
        pthread_join(w, NULL); // czekanie na zamknięcie wątku potomnego
    }
}

int main()
{
    int a;
    scanf("%d", &a);
    if (a > 1)
    {
        int arg[] = {2, a}; // początkowe wartości argumewntów funkcji pierwszego nowego wątku
        pthread_t w;
        pthread_create(&w, NULL, f_thread, arg); // utworzenie nowego wątku
        pthread_join(w, NULL);                   // czekanie na zamknięcie wątku potomnego
    }
    return 0;
}