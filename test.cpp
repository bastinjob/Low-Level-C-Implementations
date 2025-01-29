#include <iostream>
#include <stdexcept>

double add(double a, double b){
    return a+b;
}

double subtract(double a, double b) {
    return a - b;
}

double multiply(double a, double b) {
    return a * b;
}

double divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Error: Division by zero");
    }
    return a / b;
}

//struct to hold funtion pointers

struct Operation{
    char op;
    double (*funcptr)(double, double);
};

Operation operations[] = {
    {'+', add},
    {'-', subtract},
    {'*', multiply},
    {'/', divide}
};

double performOperation(char op, double a, double b){
    for(const auto& operation: operations){
        if(operation.op==op){
            return operation.funcptr(a,b);
        }
    }
    throw std::invalid_argument("Error: Unsupported Operation");
}


//---------------------------------------------------------------------

int main() {
    char op;
    double num1, num2;

    // Prompt user for operation and numbers
    std::cout << "Enter operation (+, -, *, /): ";
    std::cin >> op;

    std::cout << "Enter two numbers: ";
    std::cin >> num1 >> num2;

    try {
        double result = performOperation(op, num1, num2);  // Perform the operation
        std::cout << "Result: " << result << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;  // Handle errors (e.g., division by zero or unsupported operation)
    }

    return 0;
}