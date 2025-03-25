#include <stdio.h>
 int main()
 {
    int n = 0;
    printf("Szukaj n wyraz ciagu fibonacciego\nn = ");
    scanf("%d", &n);

    printf("Twoja liczba to: %llu\n", fib(n));
    return 0;
 }