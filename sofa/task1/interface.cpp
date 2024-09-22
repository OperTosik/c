#include "interface.h"

using namespace std;
int func(void) {
	int flag_action, flag_data1, flag_data2, sgn_data1, sgn_data2;
	bool flag_a, flag_d1, flag_d2, sgn_d1, sgn_d2;
	srand(time(NULL));

	while (true) {
		cout << "Choose action:\n1)Addition        2)Substraction\n" << endl;
		cin >> flag_action;
		if (flag_action == 1) {
			flag_a = true;
		} else if (flag_action == 2) {
			flag_a = false;
		} else {
			cout << "\nYou choose exit\n" << endl;
			return 0;
		}

		cout << "\nChoose way for input data (first number):\n1)Generation       2)Enter\n" << endl;
		cin >> flag_data1;
		if (flag_data1 == 1) {
			flag_d1 = true;
		} else if (flag_data1 == 2) {
			flag_d1 = false;
		} else {
			cout << "\nYou choose exit\n" << endl;
			return 0;
		}

		cout << "\nChoose way for input data (second number):\n1)Generation       2)Enter\n" << endl;
                cin >> flag_data2;
                if (flag_data2 == 1) {
                        flag_d2 = true;
                } else if (flag_data2 == 2) {
                        flag_d2 = false;
                } else {
                        cout << "\nYou choose exit\n" << endl;
                        return 0;
                }

		CIntN num1, num2;
		if (flag_d1) {
			cout << "\nChoose sign of number:1\n1)Positive      2)Negative\n" << endl;
			cin >> sgn_data1;
			if (sgn_data1 == 1) {
                sgn_d1 = false;
            } else if (sgn_data1 == 2) {
                sgn_d1 = true;
            } else {
		        cout << "\nYou choose exit\n" << endl;
                return 0;       
		    }

			cout << "\nEnter length of string:\n" << endl;
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "\nIncorrect data.\n" << endl;
				return 1;
			}

			num1.get(sgn_d1, n);
		} else {
			cout << "\nEnter first number:\n" << endl;
			char* array;
			int k = 0;
			char c;
			cin >> c;
			if (c != '\n') {
				k++;
				array = new char[k];
			}
			while (c != '\n') {
				k++;
				char *tmp = array;
				delete[] array;
				array = new char[k];
				for (int i = 0; i < k-1; i++) {
					array[i] = tmp[i];
				}
				array[k-1] = c;
				delete[] tmp;
				tmp = nullptr;
			}

			char *tmp = array;
			delete[] array;
			array = new char[k+1];
			for (int i = 0; i < k; i++) {
				array[i] =tmp[i];
			}
			array[k] = '\0';
			if (array[0] == '+' || array[0] == '-') {
				k--;
			}

			delete[] tmp;

			CIntN p(k, array);
			delete[] array;
			num1 = p;
		}

		if (flag_d2) {
			cout << "\nChoose sign of number:1\n1)Positive      2)Negative\n" << endl;
			cin >> sgn_data2;
			if (sgn_data2 == 1) {
                sgn_d2 = false;
            } else if (sgn_data2 == 2) {
                sgn_d2 = true;
            } else {
		        cout << "\nYou choose exit\n" << endl;
                return 0;       
		    }

			cout << "\nEnter length of string:\n" << endl;
			int n;
			cin >> n;
			if (n <= 0) {
				cout << "\nIncorrect data.\n" << endl;
				return 1;
			}

			num2.get(sgn_d2, n);
		} else {
			cout << "\nEnter second number:\n" << endl;
			char* array;
			int k = 0;
			char c;
			cin >> c;
			if (c != '\n') {
				k++;
				array = new char[k];
			}
			while (c != '\n') {
				k++;
				char *tmp = array;
				delete[] array;
				array = new char[k];
				for (int i = 0; i < k-1; i++) {
					array[i] =tmp[i];
				}
				array[k-1] = c;
				delete[] tmp;
				tmp = nullptr;
			}

			char *tmp = array;
			delete[] array;
			array = new char[k+1];
			for (int i = 0; i < k; i++) {
				array[i] =tmp[i];
			}
			array[k] = '\0';
			if (array[0] == '+' || array[0] == '-') {
				k--;
			}

			delete[] tmp;

			CIntN p(k, array);
			delete[] array;
			num1 = p;
		}

		char *tmp = num1.print();
		cout << tmp << (flag_a ? "+" : "-");
		delete[] tmp;
		tmp = num2.print();
		cout << tmp << "=";
	       	delete[] tmp;
		tmp = (flag_a ? num1+num2 : num1-num2).print();
		cout << tmp << endl;
		delete[] tmp;
	}
}
