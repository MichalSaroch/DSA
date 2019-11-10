#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int const nasobok = 43;
unsigned long long int velkost = 101;
unsigned long long int pocet;
unsigned int *pole;

void uvolni()
{
    free(pole);
}

void vypis()
{
    for(unsigned long long int i = 0; i < velkost; i++)
        printf("%llu: %d\n",i,pole[i]);
    printf("----\n");
}

void init()
{
    pole = (unsigned int*)malloc(velkost*sizeof(unsigned int));
}

unsigned long long int hash(unsigned int cislo)
{
    unsigned long long int temp = (nasobok * cislo) % velkost;
    return temp;
}

void zvacsiPole()
{
    printf("----------------------\n%llu\n",pocet);
    unsigned int *temp = pole;
    int velkTemp = velkost;
    velkost = (velkost * 2) + 1;
    pole = (unsigned int*)malloc(velkost*sizeof(unsigned int));

    printf("Rehashing\n");
    pocet = 0;
    for(unsigned long long int i = 0; i < velkTemp; i++)
        if(temp[i] != 0)
            pridaj(temp[i]);
    printf("----------------------\n%llu\n",pocet);
}

void pridaj(unsigned int cislo)
{
    unsigned long long int temp = hash(cislo);
    while(pole[temp] != 0)
    {
        if(pole[temp] == cislo)
        {
            printf("Duplikat\n");
            return;
        }
        else if(temp + 1 >= velkost)
            temp = 0;
        else
            temp++;
    }
    pole[temp] = cislo;
    printf("Cislo %d na poziciu %llu\n",cislo,temp);
    pocet++;
    if(pocet >= velkost/2)
        zvacsiPole();
}

void najdi(unsigned int cislo)
{
    unsigned long long int temp = hash(cislo);
    while(pole[temp] != 0)
    {
        if(pole[temp] == cislo)
        {
            printf("Cislo %d sa nachadza na pozicii %llu\n",cislo,temp);
            return;
        }
        else if(temp + 1 >= velkost)
            temp = 0;
        else
            temp++;
    }
    printf("Cislo %d sa nenaslo\n",cislo);
    return;
}