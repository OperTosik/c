#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
// #include "func.h"

int checkFile(FILE *file);
int readFile(FILE *file, int **arr, int i, int j);
void printArray(int **arr, int i, int j);
void findMaxInColumns(int **arr, int *max, int i, int j, int *numberMaxString);
int removeDuplicateString(int **arr, int *numberMaxString, int i, int j);
void writeToFile(FILE *file, int **arr, int i, int j);

int main() {
  int i = 0, j = 0, cur, equals, flag = 0, delete = -2, numberMaxString = 0;
  int **arr, *max;
  FILE *reader, *writer;

  reader = fopen("datadat.txt", "r");
  if (checkFile(reader) == -1) {
    return -1;
  }

  writer = fopen("datares.txt", "w");
  if (checkFile(writer) == -1) {
    fclose(reader);
    return -1;
  }

  fscanf(reader, "%d", &i);
  fscanf(reader, "%d", &j);

  if (i == 0) {
    printf("error length of columns\n");
    fclose(reader);
    fclose(writer);
    return -1;
  }

  if (j == 0) {
    printf("error length of strings\n");
    fclose(reader);
    fclose(writer);
    return -1;
  }
  
  if (readFile(reader, arr, i, j) == -1) {
    fclose(reader);
    fclose(writer);
    return -1;
  }

  printf("given \n");
  printArray(arr, i, j);

  equals = 0;
  for (int s = 0; s < i; s++) {
    for (int c = 0; c < j; c++) {
      if (arr[s][c] == arr[0][0]) {
        equals++;
      }
    }
  }

  if (equals == i * j - 2) {
    printf("new: \n");
    printArray(arr, i, j);
  } else {
    findMaxInColumns(arr, max, i, j, &numberMaxString);
    i = removeDuplicateString(arr, &numberMaxString, i, j);

    printf("new: \n");
    printArray(arr, i, j);
  }

  writeToFile(writer, arr, i, j);
}

int checkFile(FILE *file) {
  if (file == NULL) {
    printf("Can not open file\n");
    return -1;
  }
  return 0;
}

int readFile(FILE *file, int **arr, int i, int j) {
  int counter = 0, cur;

  while (fscanf(file, "%d", &cur) == 1) {
    counter++;
  }
  
  rewind(file);
  
  if (counter != i * j && counter != 0) { // -2
    printf("error data\n");
    return -1;
  }
  
  arr = (int**)malloc(i * sizeof(int*) + i * j * sizeof(int));
  if (arr == NULL) {
    printf("Memory allocation failed\n");
    return -1;
  }

  arr[0] = (int *)(*arr + i);

  for (int p = 0; p < i; ++p) {
    *arr = *arr + i;
  }

  fscanf(file, "%d", &cur);
  fscanf(file, "%d", &cur);
  
  for (int s = 0; s < i; s++) {
    for (int c = 0; c < j; c++) {
      fscanf(file, "%d", &arr[s][c]); //?
    }
  }

  return 0;
}

void printArray(int **arr, int i, int j) {
  for (int s = 0; s < i; s++) {
    for (int c = 0; c < j; c++) {
      if (c == j - 1) {
        printf(" %d \n", arr[s][c]);
      } else if (c == 0) {
        printf(" %d ", arr[s][c]);
      } else {
        printf(" %d ", arr[s][c]);
      }
    }
  }
}

void findMaxInColumns(int **arr, int *max, int i, int j, int *numberMaxString) {
  int maxString = 0;

  for (int s = 0; s < j; s++) {
    max[s] = arr[0][s];

    for (int c = 0; c < i; c++) {
      if (arr[c][s] > max[s]) {
        max[s] = arr[c][s];
        maxString = c;
      }
    }

    if (s == 0) {
      *numberMaxString = maxString;
    }
  }
}

int removeDuplicateString(int **arr, int *numberMaxString, int i, int j) {
  int delete = -2;

  for (int s = 0; s < j; s++) {
    int flag = 0;

    for (int c = 0; c < i; c++) {
      if (arr[c][s] == arr[*numberMaxString][s] && *numberMaxString != c) {
        flag = 1;
        break;
      }
    }

    if (flag == 1) {
      break;
    }
  }

  if (delete != -2) {
    for (int f = delete; f < i - 1; f++) {
      arr[f] = arr[f + 1];
    }
    return i - 1; 
  }

  return i; 
}

void writeToFile(FILE *file, int **arr, int i, int j) {
  for (int s = 0; s < i; s++) {
    for (int c = 0; c < j; c++) {
      if (c == j - 1) {
        fprintf(file, " %d \n", arr[s][c]);
      } else if (c == 0) {
        fprintf(file, " %d ", arr[s][c]);
      } else {
        fprintf(file, " %d ", arr[s][c]);
      }
    }
  }
}