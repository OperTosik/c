#include "head.h"
#include <cstdlib>
#include <ctime>

void getArray(double* arr) {
	double x;
	for (int i = 0; i < N; ++i) {
		x = ((double)rand()/RAND_MAX) * 200 - 100;
		arr[i] = x;
		printf("%f ", arr[i]);
	}
	printf("\n");
}

int interface(void) {
	char act;
	cout << "Do you want randon generation?" << endl;
	cout << "Enter: y/n" << endl; 
	cin >> act;
	if (act == 'y' || act == 'Y') {
		srand(time(NULL));

		double x[N];
		printf("x[N] = ");
		getArray(x);

	    double y[N];
	    printf("y[N] = ");
	    getArray(y);
	    printf("\n");

	    CVect v1(x, y);

	    double x2[N];
	    printf("x2[N] = ");
	    getArray(x2);

	    double y2[N];
	    printf("y2[N] = ");
	    getArray(y2);
	    printf("\n");

	    CVect v2(x2, y2);

	    double angle[N];
	    printf("angle = ");
	    getArray(angle);
	    CAngl a1(angle);
	    printf("\n");

	    // Тестирование операций
	    
	    CVect v3 = v1 + v2;
	    CVect v4 = v1 + a1;
	    CAngl a2 = v1 - v2;

	    printf("v3 = v1 + v2\n");
	    std::cout << "v1 + v2 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << "(" << v3.x[i] << ", " << v3.y[i] << ") ";
	    }
	    std::cout << "\n" <<  std::endl;

	    printf("v4 = v1 + a1\n");
	    std::cout << "v1 + a1 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << "(" << v4.x[i] << ", " << v4.y[i] << ") ";
	    }
	    std::cout << "\n" << std::endl;

	    printf("a2 = v1 - v2\n");
	    std::cout << "v1 - v2 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << a2.angle[i] << " ";
	    }
	    std::cout << std::endl;
		return 1;
	}
	else if(act == 'n' || act == 'N') {

		// Создание векторов
	    double x[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	    double y[N] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
	    CVect v1(x, y);

	    double x2[N] = {10.0, 9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
	    double y2[N] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
	    CVect v2(x2, y2);

	    double angle[N] = {M_PI/4, M_PI/3, M_PI/2, 2*M_PI/3, 3*M_PI/4, 5*M_PI/6, 7*M_PI/6, 4*M_PI/3, 5*M_PI/3, 11*M_PI/6};
	    CAngl a1(angle);

	    // Тестирование операций
	    CVect v3 = v1 + v2;
	    CVect v4 = v1 + a1;
	    CAngl a2 = v1 - v2;

	    std::cout << "v1 + v2 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << "(" << v3.x[i] << ", " << v3.y[i] << ") ";
	    }
	    std::cout << std::endl;

	    std::cout << "v1 + a1 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << "(" << v4.x[i] << ", " << v4.y[i] << ") ";
	    }
	    std::cout << std::endl;

	    std::cout << "v1 - v2 = ";
	    for (int i = 0; i < N; i++) {
	        std::cout << a2.angle[i] << " ";
	    }
	    std::cout << std::endl;
	    return 1;
	}
	else {
		cout << "You choose incorrect format" << endl;
		return 0;

	}

	return 0;
}