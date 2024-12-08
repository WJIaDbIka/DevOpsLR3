#include "FuncA.h"  // Підключення заголовного файлу FuncA.h
#include <cmath>    // Підключення бібліотеки cmath для математичних функцій
#include <chrono>
#include <algorithm>
#include <cassert>
#include <string>
#include <iostream>
// Конструктор класу FuncA
FuncA::FuncA(){
}

// Метод Calculate для обчислення значення функції
double FuncA::Calculate(double x, int terms){
    double sum = 0.0; // Ініціалізуємо змінну для зберігання суми

    // Цикл для обчислення термінів ряду
    for (int n = 0; n < terms; ++n) {
        // Обчислюємо (-1)^n для зміни знака
        double sign = pow(-1, n);
        
        // Обчислюємо (2n)! за допомогою функції tgamma
        double numerator = tgamma(2 * n + 1); // tgamma(n+1) = n!

        // Обчислюємо (n!)^2
        double denominator = pow(tgamma(n + 1), 2); // tgamma(n+1) = n!

        // Обчислюємо член ряду
        double term = (sign * numerator * pow(x, n)) / (pow(4, n) * denominator);

        // Додаємо обчислений термін до загальної суми
        sum += term;
    }

    // Повертаємо результат обчислень
    return sum;
}

void FuncA::simulateServerTest() {
    FuncA calculator;
    const int elements = 10; // Кількість обчислень
    const double value = 1.0;

    std::vector<double> computations;

    auto start = std::chrono::high_resolution_clock::now();

    // Заповнення вектора результатами обчислень
    for (size_t i = 0; i < 100000; ++i) {
        computations.emplace_back(calculator.Calculate(elements, value));
    }

    // Виконання сортування
    for (size_t iteration = 0; iteration < 10000; ++iteration) {
        std::stable_sort(computations.begin(), computations.end(), [](const double &lhs, const double &rhs) {
            return std::abs(lhs) < std::abs(rhs);
        });
    }

    auto finish = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(finish - start);

    // Вивід результату в консоль
    std::cout << "Processing time (milliseconds): " << duration.count() << std::endl;

    // Валідація часу виконання
    if (duration.count() < 5000 || duration.count() > 20000) {
        throw std::runtime_error("Error: Execution time is out of acceptable range!");
    }
}
