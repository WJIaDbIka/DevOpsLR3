#include "FuncA.h"  // Підключення заголовного файлу FuncA.h
#include <cmath>    // Підключення бібліотеки cmath для математичних функцій

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

