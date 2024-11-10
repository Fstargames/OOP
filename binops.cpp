#include <iostream>
#include <iomanip>
#include <fstream>
// updated
struct binop {
    double operand1;
    double operand2;
    char operation;
    };

void displayBinop(const binop& b){
    std::cout << std::fixed << std::setprecision(2) << b.operand1 << " " << b.operation << " " << b.operand2 << std::endl; 
};


double evaluateBinop(const binop& b){
        switch (b.operation){
            case '+': return b.operand1 + b.operand2;
            case '-': return b.operand1 - b.operand2;
            case '*': return b.operand1 * b.operand2;
            case '/': 
                if(b.operand2 != 0.0) return b.operand1 / b.operand2;
                std::cerr << "Error: Division by zero!" << std::endl;
                return 0.0;
            default:
                std::cerr << "Error: Invalid operation!" << std::endl;
                return 0.0;
        } 
    };

int main() {
    const int ARRAY_SIZE = 10;
    int count = 0;


    binop* binopsArray = new binop[ARRAY_SIZE];

    std::cout << "Enter expressions in the form: opnd1 op opnd2 (e.g., 2.5 + 3.0)" << std::endl;
    std::cout << "Enter 'q' to quit." << std::endl;

    while (count < ARRAY_SIZE){
        std::cout << "Expression " << (count + 1) << ": ";
        double opnd1, opnd2;
        char op;

        std::cin >> opnd1 >> op >> opnd2;

        if (std::cin.fail()){
            std::cin.clear();
            std::string input;
            std::cin >> input;

            if(input == "q"){
                break;
            }
            else{
                std::cerr << "Invalid niggy" << std::endl;
                continue;

            }

            
        }

            binopsArray[count].operand1 = opnd1;
            binopsArray[count].operation = op;
            binopsArray[count].operand2 = opnd2;
            count++;

    }

    std::cout << "\nStored expressions:" << std::endl;
    for(int i =0; i < count; ++i){
        displayBinop(binopsArray[i]);
    }


    // Files

    std::ofstream outfile("results.txt");

    if(!outfile){
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;

    }

    // Storing expressions and results
    for(int i=0; i< count;++i){

        

        double result = evaluateBinop(binopsArray[i]);

        outfile << std::fixed << std::setprecision(2)
                << binopsArray[i].operand1 << " "
                << binopsArray[i].operation << " "
                << binopsArray[i].operand2 << "-> "
                << result << std::endl;

    }

    outfile.close();

    delete[] binopsArray;

    return 0;

};