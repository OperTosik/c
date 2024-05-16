#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "linear-interpolation.h"

int main(void)
{
    int Err;//Код ошибки
    double* array_x = NULL;
    double* array_y = NULL;
    int len;
    double rezult;
    int i;


    double z;
    printf("112-Verbin A \n");
    printf("This program finds the value of piecewise linear interpolation at a given point \n");

    len = readfile(array_x, array_y,&Err);
    if(Err != 0){return Err;}

    sortirovka(array_x,array_y,len);
    
    printf("Enter the point: ");
    scanf("%lf", &z);

    rezult = interpolation(array_x,array_y,len,z,&Err);
    if(Err != 0){return Err;}
    printf("%lf",rezult);
    

    return Err;
}