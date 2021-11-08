#include <stdio.h>
#include <stdlib.h>

void printarray(int a[], int boyut)
{
    int i;
    for(i=0; i<boyut; i++)
        printf("%d ", a[i]);
    printf("\n");
}

void main()
{
    int a[10] = {4, 10, 6, 3, 8, 22, 7, 14, 9, 16};
    printarray(a, 10);

    hizli_sirala(a, 0, 9);

    printarray(a, 10);
}


void hizli_sirala(int a[], int sol, int sag)
{
    int k, j, sayac, pivot, temp;
    k=sol;
    j=sag;
    pivot = a[(sol+sag)/2];

    do
    {
        while(pivot > a[k] && k<sag)
            k++;
        while(pivot<a[j] && j>sol)
            j--;
        if(k <= j)
        {
            temp = a[k];
            a[k] = a[j];
            a[j] = temp;
            k++;
            j--;
        }
        printarray(a, 10);
        printf("Sol : %d - j : %d - k : %d - Sag : %d - Pivot : %d \n", sol, j, k, sag, pivot);

    }
    while(k <= j);
    if(sol < j) hizli_sirala(a, sol, j);
    if(k < sag) hizli_sirala(a, k, sag);
}
