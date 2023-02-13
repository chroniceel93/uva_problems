// This is a more typical example of the problem *without* an acceleration
// structure.

#include <iostream>
#include <string>

int recurse(int num);

int test(int low, int high);

int main() {
    bool cont = true;
    int first, second, temp, max = 0;
    std::size_t space = 0;

    while (cont == true) {
        std::string input = "";
        std::getline(std::cin, input);

        if (input.size() != 0) {
            space = 0;
            first = std::stoi(input, &space);
            second = std::stoi(input.substr(space));
            temp = 0;
            max = test(first, second);
            std::cout << first << " " << second << " " << max << "\n";
        } else {
            cont = false;
        }
    }
    return 0;
}

int recurse(int num) {
    int res = 0;
    int tick = 0;

    if (num % 2) {
        res = (3 * num) + 1;
    } else {
        res = num / 2;
    }

    if (res == 1) {
        tick = 1;
    } else {
        tick = recurse(res);
    }
    return tick + 1;
}

int test(int low, int high) {
    int test, max = 0;
    if (low > high) {
        test = low;
        low = high;
        high = test;
    }

    for (int i = low; i <= high; i++) {
        if (i == 1) {
            test = 1;
        } else {
            test = recurse(i);
        }
        if (test > max) {
            max = test;
        }
    }
    return max;
}