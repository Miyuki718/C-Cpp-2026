#include <iostream>
#include <string>
#include "SafeArray.hpp"

int main() {
    SafeArray<int> numbers(3);
    numbers.set(0, 10);
    numbers[1] = 20;
    numbers[2] = 30;
    const SafeArray<int>& readOnly = numbers;
    std::cout << "Integer array:";
    for (std::ptrdiff_t i = 0; i < 3; i++) {
        std::cout << ' ' << readOnly[i];
    }
    std::cout << "\nget(0): " << numbers.get(0) << '\n';

    SafeArray<double> prices(2);
    prices[0] = 3.5;
    SafeArray<std::string> names(2);
    names[0] = "Mimi";
    std::cout << "Other types: " << prices[0] << ' ' << names[0] << '\n';

    for (int index : {-1, 3}) {
        try {
            std::cout << numbers[index] << '\n';
        } catch (const std::out_of_range& error) {
            std::cout << "Rejected index " << index << ": " << error.what() << '\n';
        }
    }
    return 0;
}
