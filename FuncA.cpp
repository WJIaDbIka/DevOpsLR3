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

void FuncA::testServerSimulation() {
    FuncA func;
    int n = 10; // кількість елементів для обчислення
    double x = 1;

    std::vector<double> results;
    
    auto start_time = std::chrono::high_resolution_clock::now();

    // Генерація результатів
    for (int i = 0; i < 100000; ++i) {
        results.push_back(func.Calculate(n, x));
    }

    // Сортування
    for(int i=0; i<10000; i++){
    		std::sort(results.begin(), results.end(), [](const auto &a, const auto &b) {
        	return std::abs(a) < std::abs(b);
    	});
    }
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

   // Виведення часу на консоль (імітація відповіді сервера)
    std::cout << "Elapsed time (ms): " << elapsed.count() << std::endl;

    // Перевірка часу виконання
    assert(elapsed.count() >= 5000 && elapsed.count() <= 20000 && "Test failed: Elapsed time is out of bounds!");
}
