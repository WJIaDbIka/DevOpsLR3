#include <iostream>
#include <cmath> 
#include "../FuncA.h" 

int main(int argc, char* argv[]) {
    FuncA seriesCalculator;


    double x = 1.0;
    int terms = 1; 
    double result = seriesCalculator.Calculate(x, terms);


    if (std::abs(result - 1.0) < 1e-6) { 
	  return 0; 
    }

    return 1; 
}
