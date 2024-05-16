#define e 0.001

int readfile(double* array_x, double* array_y,int* Err);// Чтение файла, Возвращает длинну массивов

void sortirovka(double* array_x,double* array_y,int len);// Сортировка двух  массивов одновременно

void proverka_z(double* array_x,double z,int len,int* Err);// Проверка корректности введённого числа

double interpolation(double* array_x,double* array_y,int len, double z,int*Err);// Нахождение координат введёной точки
