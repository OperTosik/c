#include <stdio.h>
#include <math.h>
#include <time.h>
//variaty of sorts
void WriteArray(FILE*fout,double *array, int len);
void InsertionSort(double *array, int len);
void HeapSort(double *array, int len);





int main(void) {
    time_t tim;
    tim = time(&tim);
    // FILE*fin = fopen("input.txt", "r");
    FILE*fout = fopen("output.txt", "w");
    int len = 0;
    double x;
    double *array;
    // if (fin == NULL) {
        // perror("Cannot open an input file");
        // fclose(fin);
        // return -1;
    // }
    // while (fscanf(fin, "%lf", &x) == 1) {
    //     ++len;
    //     if (fscanf(fin, "%lf", &x) != 1) {
    //         perror("Incorrect format");
    //         fclose(fin);
    //         return -1;
    //     }
    // }
    // rewind(fin);
    printf("Write lenth: ");
    scanf("%d", &len);
    array = (double*)malloc(len * sizeof(double));
    // for (int i = 0; i < len; ++i) 
    //     fscanf(fin, "%lf", array + i);
    // fclose(fin);
    if (fout == NULL) {
        perror("Cannot open an input file");
        free(array);
        return -1;
    }
    
    // InsertionSort(array, len);
    WriteArray(fout, array, len);
    printf("Time = %d sec\n", int(tim));
    // printf"%d\n", (int(tim % 9 + 1));

    fclose(fout);
    free(array);
    return 0;
}

void WriteArray(FILE*fout, double *array, int len) {
    for (int i = 0; i < len; ++i) {
        printf("%lf ", array[i]);
        fprintf(fout, "%lf ", array[i]);
    }
    printf("\n");
    fprintf(fout, "\n");
}

void InsertionSort(double *array, int len) {
    int temp;
    for (int i = 1; i < len; ++i) {
        for (int j = i; j > 0; --j) {
            if (array[j - 1] > array[j])  {
                temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
            }
        }
    }
}

void HeapSort(double *array, int len) {

}