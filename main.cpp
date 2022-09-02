#include <iostream>
#include "Calculator.h"

int main() {
    while(1){
        cout<<"Please type in file name"<<endl;
        string fileName;
        cin>>fileName;
        Calculator calculator;
        calculator.calculate(fileName);
    }
    return 0;
}
