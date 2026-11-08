#include <iostream>

void print_array(int n, int* arr, bool print_multiline = false) {
    if (print_multiline) {
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << std::endl;
        }
        return;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i];
        if (i != n - 1) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Error: missing argument n\n";
        return 1;
    }

    int n = 0;
    int i = 0;
    while (argv[1][i] != '\0') {
        n = n * 10 + (argv[1][i] - '0');
        ++i;
    }
    int* arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }
    int k = 0;
    std::cin >> k;
    if (k < 0) {
        k = n + k % n;
    } else {
        k = k % n;
    }
    for (int i = 0; i < n / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
    for (int i = 0; i < k / 2; ++i) {
        int temp = arr[i];
        arr[i] = arr[k - i - 1];
        arr[k - i - 1] = temp;
    }
    for (int i = 0; i < (n - k) / 2; ++i) {
        int temp = arr[k + i];
        arr[k + i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
    print_array(n, arr, true);
    print_array(n, arr);
    delete[] arr;
}