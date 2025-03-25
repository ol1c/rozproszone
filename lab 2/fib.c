unsigned long long fib(unsigned int n)
{
    unsigned long long wynik = 0;
    unsigned long long a = 1;
    unsigned long long b = 0;
    if (n == 1)
    {
        return 1;
    }
    for (int i = 2; i <= n; i++)
    {
        wynik = a + b;
        b = a;
        a = wynik;
    }
    return wynik;
}