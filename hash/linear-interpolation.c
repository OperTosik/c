#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "linear-interpolation.h"

int readfile(double* array_x, double* array_y,int* Err)
{
    int len = 0;
    int i;
    double x;
    char myfilename[120];

    FILE*fin;

    printf("Enter the name of the file from which the coordinates of the piecewise linear interpolation points will be taken: ");
    scanf("%s", myfilename);
    printf("\n");

    fin = fopen(myfilename,"r");
    if (!fin){
        printf("Err = -1: The file could not be opened %s\n", myfilename);
        *Err = -1;
        return 0;
    }

    while(fscanf(fin,"%lf",&x) == 1){++len;}
    if(len % 2 == 1 || len == 0){*Err = 1;fclose(fin); return 0;}

    array_x = (double*)malloc((len/2) *sizeof(double));
    array_y = (double*)malloc((len/2) *sizeof(double));

    rewind(fin);

    for(i = 0;i < len/2;++i)
    {
        fscanf(fin,"%lf",&x);
        array_x[i] = x;
        fscanf(fin,"%lf",&x);    
        array_y[i] = x;

    }
    return len/2;
}

void sortirovka(double* array_x,double* array_y,int len)// Сортировка координат по возростанию(сортирую по x)
{
    int i,j;
    double a;// для swap

  for(i = 0;i<len;i++){printf("%lf \n", array_x[i]);}    

    for(i = 0;i < len;++i)
    {
        for(j = 0;j < len - 1;++j)
        {
            if(array_x[j] > array_x[i])
            {
                a = array_x[j];
                array_x[j] = array_x[i];
                array_x[i] = a;

                a = array_y[j];
                array_y[j] = array_y[i];
                array_y[i] = a;

            }
        }
    }

    for(i = 0;i<len;i++){printf("%lf \n", array_x[i]);}
}

void proverka_z(double* array_x,double z,int len,int* Err)// Проверка корректности введённого числа
{
    int i;
    if(z < array_x[0] || z > array_x[len - 1]){*Err = 3; return ;}
}


double interpolation(double* array_x,double* array_y,int len, double z,int*Err)// Нахождение координат введёной точки
{
    int i = 0;
    int i0;// номера xi между которыми z
    int i1;
    double alpha;

    proverka_z(array_x,z,len,Err);
    if(*Err == 3){printf("Err = 3: The point was entered incorrectly \n"); return 0;}

    if(fabs(array_x[0] - z) < e){return array_y[0];}
    for(i = 1;i < len;++i)
    {   
        if(fabs(array_x[i] - array_x[i - 1]) < e){*Err = 2;printf("Err = 2: Point data entered incorrectly");return 0;}
        if(fabs(z - array_x[i]) < e){return array_y[i];}
        if(z < array_x[i] && z > array_x[i - 1]){i0 = i - 1;i1 = i;}
    }

    alpha = (z - array_x[i0]) / (array_x[i1] - array_x[i0]);

    return array_y[i0] + alpha * (array_y[i1] - array_y[i0]);


}