//
// Created by 86929 on 2022/8/31.
//
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>
#include "Calculator.h"

Calculator::Calculator() {
    //isp
    isp['(']=1;isp['*']=5;isp['/']=5;isp['%']=5;
    isp['+']=3;isp['-']=3;isp[')']=6;

    //icp
    icp['(']=6;icp['*']=4;icp['/']=4;icp['%']=4;
    icp['+']=2;icp['-']=2;icp[')']=1;
}

bool Calculator::calculate(string fileName) {
    fstream file;
    file.open(fileName);
    if(!file.is_open()){
        cout<<"File open failed"<<endl;
        return false;
    }
    while(!file.eof()){
        string line;
        getline(file,line);
        cout<<calculateLine(line)<<endl;
    }
    file.close();
    return true;
}

double Calculator::calculateLine(string line) {
    stack<char> symbols;
    string formula;
    for(int i=0;i<line.size();i++){
        if(line[i]>='0'&&line[i]<='9'){//is num
            while(i<line.size()&&line[i]>='0'&&line[i]<='9'){
                formula+=line[i];i++;
            }
            if(line[i]=='.'){
                formula+=line[i];i++;
                while(i<line.size()&&line[i]>='0'&&line[i]<='9'){
                    formula+=line[i];i++;
                }
            }
            i--;
            formula+=' ';
        }
        else if(line[i]=='-'&&(i==0||line[i-1]<'0'||line[i-1]>'9')){
            formula+='-';
        }
        else{//is symbol
            while(!symbols.empty()&&icp[line[i]]<=isp[symbols.top()]){
                if(symbols.top()=='('){
                    symbols.pop();
                    break;
                }
                else{
                    formula+=symbols.top();
                    formula+=' ';
                    symbols.pop();
                }
            }
            if(line[i]!=')')
                symbols.push(line[i]);
        }
    }
    while(!symbols.empty()){
        if(symbols.top()!='('&&symbols.top()!=')'){
            formula+=symbols.top();formula+=' ';
        }
        symbols.pop();
    }

    stack<double> calculation;
    bool isNegative=false;
    for(int i=0;i<formula.size();i++){
        if(formula[i]>='0'&&formula[i]<='9'){
            double integral=0,fractional=0;
            while(i<formula.size()&&formula[i]>='0'&&formula[i]<='9'){
                integral*=10;
                integral+=formula[i]-'0';
                i++;
            }
            if(formula[i]=='.'){
                i++;
                while(i<formula.size()&&formula[i]>='0'&&formula[i]<='9'){
                    fractional*=10;
                    fractional+=formula[i]-'0';
                    i++;
                }
            }
            while(fractional>=1) fractional/=10;
            if(isNegative){
                calculation.push(-integral-fractional);
                isNegative=false;
            }
            else
                calculation.push(integral+fractional);
        }
        else if(formula[i]=='-'&&formula[i+1]>='0'&&formula[i+1]<='9'){
            isNegative=true;
        }
        else if(formula[i]!=' '){
            double num1= calculation.top();
            calculation.pop();
            double num2=calculation.top();
            calculation.pop();
            if(formula[i]=='+') calculation.push(num2+num1);
            else if(formula[i]=='-') calculation.push(num2-num1);
            else if(formula[i]=='*') calculation.push(num2*num1);
            else if(formula[i]=='/') calculation.push(num2/num1);
            else if(formula[i]=='%') calculation.push((double)((int)num2%(int)num1));
        }
    }
    return calculation.top();
}


