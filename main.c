#include <stdio.h>
#include <stdlib.h>

int main(void) {
	FILE*first_file, *second_file;
	size_t first_size = 0, second_size = 0;
	double cur;
	double*first_array;
	double*second_array;
	first_file = fopen("ina.txt", "r");
	if (!first_file) return -1;
	second_file = fopen("inb.txt", "r");
	if (!second_file) {
		fclose(first_file);
		return -1;
	}
	printf("Both files are open!\n");
	while (fscanf(first_file, "%lf", &cur) == 1) first_size++;
	while (fscanf(second_file, "%lf", &cur) == 1) second_size++;
	if (first_size == 0 || second_size == 0) {
		fclose(first_file);
		fclose(second_file);
		return -1;
	}
	rewind(first_file);
	rewind(second_file);
	printf("The data in both files is corrects!\n");
	first_array = (double*)malloc(first_size * sizeof(double));
	if (!first_array) {
		fclose(first_file);
		fclose(second_file);
		return -1;
	}
	second_array = (double*)malloc(second_size * sizeof(double));
	if (!second_array) {
		fclose(first_file);
		fclose(second_file);
		free(first_array);
		return -1;
	}
	printf("Memory allocation for both arrays comleted!\n");
	for (size_t i = 0; i < first_size; i++) {
		fscanf(first_file, "%lf", &first_array[i]);
	}
	for (size_t i = 0; i < second_size; i++) {
		fscanf(second_file, "%lf", &second_array[i]);
	}
	fclose(first_file);
	fclose(second_file);
	printf("Filling both arrays completed!\n");



	free(first_array);
	free(second_array);
	return 0;
}
