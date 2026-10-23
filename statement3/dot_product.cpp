#include <iostream>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Error: missing argument n\n";
        return 1;
    }

    int n = 0;
    int i = 0;
    while (argv[i][1] != '\0') {
        n = n * 10 + (argv[1][i] - '0');
        ++i;
    }
    float* a = new float[n];
    float* b = new float[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> b[i];
    }
    float result = 0;
    for (int i = 0; i < n; ++i) {
        result += a[i] * b[i];
    }
    std::cout << result;
    delete[] a;
    delete[] b;
}