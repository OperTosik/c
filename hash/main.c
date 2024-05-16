#include "func.h"


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