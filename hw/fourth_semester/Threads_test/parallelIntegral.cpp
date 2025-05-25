#include <iostream>
#include <thread>
#include <vector>
#include <cmath>
#include <chrono>

class Params {  // Parameters of thread
public:
    double (*f)(double);  // Function to integrate
    double a;             // Integral limits
    double b;
    double dx;            // Integration step
    double res;           // Result: Integral of function on [a, b]

    Params(
        double (*func)(double) = nullptr,
        double a0 = 0.,
        double b0 = 0.,
        double ddx = 0.001
    ):
        f(func),
        a(a0),
        b(b0),
        dx(ddx),
        res(0.)
    {}
};

void threadFunction(Params* params);
double integralSimpson(
    double (*f)(double),
    double a,
    double b,
    double dx = 0.001
);
double f(double);   // Function to integrate

int main() {
    int numThreads;
    std::cout << "Enter the number of threads: ";
    if (!(std::cin >> numThreads) || numThreads <= 0) {
        std::cerr << "Incorrect number of threads" << std::endl;
        return (-1);
    }
    std::vector<std::thread> threads;
    threads.reserve(numThreads);
    std::vector<Params> threadParams(numThreads);
    std::cout << "Enter integral limits a, b: ";
    double a, b;
    if (!(std::cin >> a >> b)) {
        std::cerr << "Incorrect integral limits" << std::endl;
        return (-1);
    }
    std::cout << "Enter integration step dx: ";
    double dx;
    if (!(std::cin >> dx)) {
        std::cerr << "Incorrect integration step" << std::endl;
        return (-1);
    }

    // Measure the duration
    // Start time:
    auto t0 = std::chrono::high_resolution_clock::now();

    double segmentLength = (b - a)/numThreads;
    for (int i = 0; i < numThreads; ++i) {
        threadParams[i] = Params(
            f, 
            a + i*segmentLength,
            a + (i + 1)*segmentLength,
            dx
        );
        threads.push_back(
            std::thread(threadFunction, &threadParams[i])
        );
    }
    double sum = 0.;
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
        sum += threadParams[i].res;
    }

    // Finish time:
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t1 - t0;

    std::cout << "Integral = " << sum << std::endl;
    std::cout << "Duration " << ms_double.count()
              << " milliseconds." << std::endl;

    return 0;
}

double f(double x) {    // Function to integrate
    return sin(x);
}

void threadFunction(Params* params) {
    double sum = integralSimpson(
        params->f,
        params->a,
        params->b,
        params->dx
    );
    params->res = sum;
}

double integralSimpson(
    double (*f)(double),
    double a,
    double b,
    double dx /* = 0.001 */
) {
    double factor = 1.;
    if (b < a) {
        // Swap the integral limits
        factor = (-1.);
        double tmp = a;
        a = b; b = tmp;
    }
    int n = int((b - a)/dx);
    if (n <= 0) {
        n = 2;
    } else {
        if (n%2 != 0)
            ++n;        // n must be even
    }
    double h = (b - a)/n;   // Integration step
    double s0 = f(a) + f(b);
    double s1 = 0.;
    double s2 = 0.;
    double x = a;
    int k = n/2;
    for (int i = 0; i < k; ++i) {
        x += h;
        s1 += f(x);
        x += h;
        if (i < k - 1)
            s2 += f(x);
    }
    return factor*(s0 + 4.*s1 + 2.*s2)*h/3.;
}
