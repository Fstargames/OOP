#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

class Binop {
private:
    double operand1;
    double operand2;
    char operation;

public:
    Binop(double op1 = 0.0, char op = '+', double op2 = 0.0) : operand1(op1), operation(op), operand2(op2) {}

    void setOperand1(double op1) { operand1 = op1; }
    void setOperand2(double op2) { operand2 = op2; }
    void setOperation(char op) { operation = op; }

    double getOperand1() const { return operand1; }
    double getOperand2() const { return operand2; }
    char getOperation() const { return operation; }

    void display() const {
        std::cout << std::fixed << std::setprecision(2)
                  << operand1 << " " << operation << " " << operand2 << std::endl;
    }

    double evaluateBinop() const {
        switch (operation) {
            case '+': return operand1 + operand2;
            case '-': return operand1 - operand2;
            case '*': return operand1 * operand2;
            case '/':
                if (operand2 != 0.0) return operand1 / operand2;
                std::cerr << "Error: Division by zero!" << std::endl;
                return 0.0;
            default:
                std::cerr << "Error: Invalid operation!" << std::endl;
                return 0.0;
        }
    }
};

int main() {
    const int ARRAY_SIZE = 10;
    int count = 0;
    Binop* binopsArray = new Binop[ARRAY_SIZE];

    std::cout << "Enter expressions in the form: opnd1 op opnd2 (e.g., 2.5 + 3.0)" << std::endl;
    std::cout << "Enter 'q' to quit." << std::endl;

    while (count < ARRAY_SIZE) {
        std::cout << "Expression " << (count + 1) << ": ";

        // i) Approach 1: Using `std::istream` directly with `>>`
        double opnd1, opnd2;
        char op;
        if (std::cin >> opnd1 >> op >> opnd2) {
            binopsArray[count].setOperand1(opnd1);
            binopsArray[count].setOperation(op);
            binopsArray[count].setOperand2(opnd2);
            count++;
        } else {
            std::cin.clear();                 // Clear the error flag
            std::string input;
            std::cin >> input;                // Discard invalid input
            if (input == "q") break;          // Quit if "q" is entered
            std::cerr << "Invalid input, please enter a valid expression (e.g., 2.5 + 3.0)" << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Ignore the rest of the line
        }

        
    }

    std::cout << "\nStored expressions:" << std::endl;
    for (int i = 0; i < count; ++i) {
        binopsArray[i].display();
    }

    // Writing expressions and results to a file
    std::ofstream outfile("results.txt");

    if (!outfile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        delete[] binopsArray;
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        double result = binopsArray[i].evaluateBinop();
        outfile << std::fixed << std::setprecision(2)
                << binopsArray[i].getOperand1() << " "
                << binopsArray[i].getOperation() << " "
                << binopsArray[i].getOperand2() << " -> "
                << result << std::endl;
    }

    outfile.close();
    delete[] binopsArray;
    return 0;
}
