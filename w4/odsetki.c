//
// Created by pszwed on 20.03.2021.
//
#include <stdio.h>

double odsetki(double kwota, int liczbaDni, double oproc)
{
    printf("kwota=%f\n",kwota);
    return kwota * (double) liczbaDni * oproc /36500;
}

int main()
{
    double k = 1000;
    k=k+odsetki(
            k+odsetki(
                    k+odsetki(k,30,5)
                    ,30,5)
            ,30,5);
    printf("Miesiac %d %.2f\n",3,k);

    return 0;
}
