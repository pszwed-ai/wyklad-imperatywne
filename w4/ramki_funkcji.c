//
//

#include <stdio.h>

double odsetki(double kwota, int liczbaDni, double oproc)
{
    // w modelu 64-bitowym liczbaDni wyrównywana jest na granicy 8B
    printf("oproc %p\n",&oproc);
    printf("liczbaDni %p\n",&liczbaDni);
    printf("kwota %p\n",&kwota);
    long long*ra = (long long*)&kwota;
    ra--;
    printf("ra %p\n",*ra);
    return kwota * (double) liczbaDni * oproc /36500;
}

int main()
{
    double k = 1000;
    int m=3;
    printf("main() %p\n",main);
    printf("odsetki() %p\n\n",odsetki);
    k=k+odsetki(k, m*30 ,5);
   return 0;
}
