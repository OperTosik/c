#include "stdio.h"
#include "stdlib.h"

int ReadFile(const char *filename, int *rows, int *cols, int ***arr);
void PrintArray(int rows, int cols, int **arr);
void WriteToFile(const char *filename, int rows, int cols, int **arr);
void RemoveRows(int N, int M, int **arr);

int ReadFile(const char *filename, int *rows, int *cols, int ***arr) {
    FILE *reader = fopen(filename, "r");
    if (reader == NULL) {
        printf("can not open reader-file\n");
        return -1;
    }

    fscanf(reader, "%d %d", rows, cols);
     
    if (*rows == 0 || *cols == 0 || *rows < 0 || *cols < 0) {
        printf(" invalid data\n");
        fclose(reader);
        return -1;
    }

    *arr = (int **)malloc(*rows * sizeof(int *));
    if(arr==NULL){
     printf("allocation memory fail");
     
fclose(reader);
return -1;
        
    }
    (*arr)[0] = (int *)malloc(*rows * *cols * sizeof(int));
     if(arr[0]==NULL){
     printf("allocation memory fail");
     free(arr);
fclose(reader);
return -1;
     }
    for (int p = 1; p < *rows; p++) {
        (*arr)[p] = (*arr)[0] +p* *cols;
    }

    for (int s = 0; s < *rows; s++) {
        for (int c = 0; c < *cols; c++) {
            fscanf(reader, "%d", &(*arr)[s][c]);
        }
    }

    fclose(reader);
    return 0;
}

void PrintArray(int rows, int cols, int **arr) {

    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < cols; c++) {
            if (c == cols - 1) {
                printf("%d\n", arr[s][c]);
            } else {
                printf("%d ", arr[s][c]);
            }
        }
    }
}

void WriteToFile(const char *filename, int rows, int cols, int **arr) {
    FILE *writer = fopen(filename, "w");
    if (writer == NULL) {
        printf("can not open writer-file\n");
        return;
    }

    for (int s = 0; s < rows; s++) {
        for (int c = 0; c < cols; c++) {
            fprintf(writer, "%d ", arr[s][c]);
        }
        fprintf(writer, "\n");
    }

    fclose(writer);
}

void RemoveRows(int N, int M, int **arr) {
    int *max = (int *)malloc(M * sizeof(int));
	int *maxIndex = (int *)malloc(M * sizeof(int));
    //find max element in colomn and his index, wtire in arrays
    for(int j = 0; j < M; j++){
        for(int i = 0; i < N; i++){
            if(arr[i][j] > max[j]){
                max[j] = arr[i][j];
                maxIndex[j] = i;
            } else if (arr[i][j] == max[j]) {
                //check to double placed max element
                maxIndex[j] = -1;
            }
        }
    }
    
    for(int i = 0; i < N; i++){
        int isMax = 1;
        for(int j = 0; j < M; j++){
            if(i != maxIndex[j]){
                isMax = 0;
                break;
            }
        }
        if(isMax)
            for(int j = 0; j < M; j++)
                arr[i][j] = -1;
		
    }
	free(max);
	free(maxIndex);
}

int main(void) {
    int rows = 0, cols = 0;
    int **arr;

    ReadFile("data.txt", &rows, &cols, &arr);
    if (rows == 0 || cols == 0 || rows < 0 || cols < 0) {
        return -1;
    }
printf("given: \n");
    PrintArray(rows, cols, arr);
    RemoveRows(rows, cols, arr);
printf("new: \n");
    PrintArray(rows, cols, arr);
    WriteToFile("res.txt", rows, cols, arr);
	printf("\nArray in a row: ");
	for (int m=0; m < rows* cols; m++) printf("|%d|", arr[0][m]);

    free(arr[0]);
    free(arr);
 
    return 0;
}

