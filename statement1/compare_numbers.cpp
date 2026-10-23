#include <iostream>

size_t my_strlen(const char* str) {
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void print_reverse_state(bool reverse_state) {
    if (reverse_state) {
        std::cout << "greater" << std::endl;
        return;
    }
    std::cout << "less" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "error" << std::endl;
        return 1;
    }
    char* x = argv[1];
    char* y = argv[2];
    // char *x = "0";
    // char *y = "-0.1";

    if (x[0] == '+') {
        x++;
    }
    if (y[0] == '+') {
        y++;
    }
    if (x[0] == '-' and y[0] != '-') {
        std::cout << "less" << std::endl;
        return 0;
    }
    if (x[0] != '-' and y[0] == '-') {
        std::cout << "greater" << std::endl;
        return 0;
    }
    bool reverse_state = x[0] == '-';
    if (reverse_state) {
        x++;
        y++;
    }
    size_t len_x = my_strlen(x);
    size_t len_y = my_strlen(y);
    size_t position_dot_x = 0;
    size_t position_dot_y = 0;
    for (size_t i = 0; i < len_x; i++) {
        if (x[i] == '.') {
            position_dot_x = i;
            break;
        }
    }
    for (size_t i = 0; i < len_y; i++) {
        if (y[i] == '.') {
            position_dot_y = i;
            break;
        }
    }
    if (position_dot_x > position_dot_y) {
        print_reverse_state(not reverse_state);
        return 0;
    }
    if (position_dot_x < position_dot_y) {
        print_reverse_state(reverse_state);
        return 0;
    }
    if (position_dot_x == 0) {
        if (len_x > len_y) {
            print_reverse_state(not reverse_state);
            return 0;
        }
        if (len_y > len_x) {
            print_reverse_state(reverse_state);
            return 0;
        }
        for (size_t i = 0; i < len_y; i++) {
            if (x[i] < y[i]) {
                print_reverse_state(reverse_state);
                return 0;
            }
            if (x[i] > y[i]) {
                print_reverse_state(not reverse_state);
                return 0;
            }
        }
        std::cout << "equal" << std::endl;
        return 0;
    }

    x += position_dot_x + 1;
    y += position_dot_y + 1;
    len_x = my_strlen(x);
    len_y = my_strlen(y);
    size_t len_min = len_x < len_y ? len_x : len_y;
    for (size_t i = 0; i < len_min; i++) {
        if (x[i] < y[i]) {
            print_reverse_state(reverse_state);
            return 0;
        }
        if (x[i] > y[i]) {
            print_reverse_state(not reverse_state);
            return 0;
        }
    }
    if (len_x > len_y) {
        print_reverse_state(not reverse_state);
        return 0;
    }
    if (len_y > len_x) {
        print_reverse_state(reverse_state);
        return 0;
    }
    std::cout << "equal" << std::endl;
    return 0;
}