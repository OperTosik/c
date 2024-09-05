#include <stdio.h>
#include <math.h>

void piApprox(int m[2], double eps = 1e-6);

int main(void) {
    while(true) {
        double eps;
        printf("eps: ");
        if (scanf("%lf", &eps) < 1) break;
        int m[2];
        piApprox(m, eps);
        printf("pi - %d/%d = %.12f\n", m[0], m[1], double(m[0])/double(m[1]));
    }
    return 0;
}

void piApprox(int m[2], double eps) {
    int x = 3, y = 0;
    int dir = 1;
    while (!(fabs(double(y)/double(x) - M_PI) <= 1./(double(x)*double(x)) && fabs(double(y)/double(x) - M_PI))) {
        if (dir > 0) {
            if (x > 1 && double(y)/double(x) < M_PI) {
                x -= 1;
                y += 1;
            }
            else {
                y += 1;
                dir = (-dir);
            }
        }
        else {
            if (y > 1 && double(y)/double(x) > M_PI) {
                x += 1;
                y -= 1;
            }
            else {
                x += 1;
                dir = (-dir);
            }
        }
    }
    m[0] = y; m[1] = x;
}