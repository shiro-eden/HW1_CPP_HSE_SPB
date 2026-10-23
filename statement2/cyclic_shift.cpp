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
    // int n = 2;
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int k = 0;
    std::cin >> k;
    if (k > 0) {
        k = n - (k % n);
    } else {
        k = -k;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << arr[(i + k) % n] << std::endl;
    }
    for (int i = 0; i < n; ++i) {
        std::cout << arr[(i + k) % n];
        if (i != n - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
    delete[] arr;
}