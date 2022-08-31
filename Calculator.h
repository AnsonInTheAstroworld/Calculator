//
// Created by 86929 on 2022/8/31.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

#include <unordered_map>

using namespace std;

class Calculator {
public:
    Calculator();
    bool calculate(string fileName);

private:
    double calculateLine(string line);

    unordered_map<char,int> isp;//栈内优先级
    unordered_map<char,int> icp;//栈外优先级
};


#endif //CALCULATOR_CALCULATOR_H
