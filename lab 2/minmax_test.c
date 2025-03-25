 #include <stdio.h>
 int main()
 {
    int a = 0, b = 0;
    printf("Podaj 2 liczby:\n");
    scanf("%d", &a);
    scanf("%d", &b);

    printf("\nMniejsza: %d\nWieksza: %d\n", min(a, b), max(a, b));
    return 0;
 }