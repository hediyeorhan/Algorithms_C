#include <stdio.h>
#include <stdlib.h>


// Selection //

void Selection(int *gelendizi, int diziboyut)
{
    int i, j, temp;

    for(i=0; i<diziboyut-1; i++)
    {
        for(j=i+1; j<diziboyut; j++)
        {
            if(gelendizi[i] > gelendizi[j])
            {
                temp = gelendizi[j];
                gelendizi[j] = gelendizi[i];
                gelendizi[i] = temp;
            }
        }
        diziYazdir(gelendizi, diziboyut);
    }
}

// Insertion //

void Insertion(int *gelendizi, int diziboyut)
{
    int i, index, temp;
    for(i=1; i<diziboyut; i++)
    {
        index = i;
        while(index > 0 && gelendizi[index] < gelendizi[index-1])
        {
            temp = gelendizi[index];
            gelendizi[index] = gelendizi[index-1];
            gelendizi[index-1] = temp;
            index--;
        }
        diziYazdir(gelendizi, diziboyut);
    }
}

// Bubble Sort //

void BubbleSort(int *gelendizi, int diziboyut)
{
    int i, j, temp;
    for(i=1; i<diziboyut; i++)
    {
        int sirali = 1;
        for(j=0; j<diziboyut-i; j++)
        {
            if(gelendizi[j] > gelendizi[j+1])
            {
                sirali = 0;
                temp = gelendizi[j];
                gelendizi[j] = gelendizi[j+1];
                gelendizi[j+1] = temp;
            }
            diziYazdir(gelendizi, diziboyut);
        }
        if(sirali)
            break;
    }
}


// ShellSort //

void ShellSort(int *gelendizi, int diziboyut)
{
    int temp, artim, i, j, sayac;
    artim = diziboyut/2;
    while(artim != 0)
    {
        for(i=artim; i<diziboyut; i++)
        {
            temp = gelendizi[i];
            j = i-artim;
            while(j>=0 && temp<gelendizi[j])
            {
                gelendizi[j+artim] = gelendizi[j];
                gelendizi[j] = temp;
                j -= artim;
            }
            printf("Artirma : %d Index : %d\n", artim, i);
            for(sayac=0; sayac<diziboyut; sayac++)
            {
                printf("%d, ", gelendizi[sayac]);
            }
            printf("\n");
            artim = artim/2;
        }
    }
}

void diziYazdir(int *gelendizi, int diziboyut)
{
    for(int i=0; i<diziboyut; i++)
    {
        printf("%d, ", *gelendizi); // gelendizi[i]; -- bu sekilde de olabilir.
        gelendizi++;
    }
    printf("\n");
}
int main()
{
    int diziS[] = {20, 11, 28, 14, 17, 22};
    int diziI[] = {20, 11, 28, 14, 17, 22};
    int diziB[] = {20, 11, 28, 14, 17, 22};
    int diziSH[] = {20, 11, 28, 14, 17, 22};
    int diziboyut = 6;
    printf("\n ---------- SELECTION ---------- \n");
    diziYazdir(diziS, diziboyut);
    Selection(diziS, diziboyut);
    diziYazdir(diziS, diziboyut);

    printf("\n ---------- INSERTION ---------- \n");
    diziYazdir(diziI, diziboyut);
    Insertion(diziI, diziboyut);
    diziYazdir(diziI, diziboyut);

    printf("\n ---------- BUBBLE SORT ---------- \n");
    diziYazdir(diziB, diziboyut);
    BubbleSort(diziB, diziboyut);
    diziYazdir(diziB, diziboyut);

    printf("\n ---------- SHELL SORT ---------- \n");
    diziYazdir(diziSH, diziboyut);
    ShellSort(diziSH, diziboyut);
    diziYazdir(diziSH, diziboyut);
    return 0;
}
