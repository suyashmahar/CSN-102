// 
// * Author : Suyash Mahar
// * Note   : Code currently works with simple expressions which have 
//            variables of single character and round brackets
// * Example:
//    ------------------------------------------------
//    $ ./inToPost
//    Enter an expression: (4+8)*(6-5)/((3-2)*(2+2))
//    Result: 48+65-*32-22+*/
//    ------------------------------------------------


#include<iostream>
#include<stack>
#include<string>

#define TESTING 0

using namespace std;

const int OPERATORS_COUNT = 5;
char operators[] = {'+', '-', '*', '/', '$'};

bool isOperator(char inputChar){
    for (int i = 0; i < OPERATORS_COUNT; i++){
        if (inputChar == operators[i]){
            return true;
        }
    }
    return false;
}

bool isRightParenthesis(char inputChar){
    return (inputChar == ')');
}

bool isLeftParenthesis(char inputChar){
    return (inputChar == '(');
}

bool isOperand(char inputChar){
    return (!(isOperator(inputChar) || isLeftParenthesis(inputChar) || isRightParenthesis(inputChar)));
}

int getPriority(char firstChar, char secondChar){
    if ((firstChar == '$') && (secondChar == '$')) return 0;

    else if (firstChar == '$') return 1;
    else if (secondChar == '$') return -1;
    
    else if (firstChar == '*' || firstChar == '/'){
        if (secondChar == '*' || secondChar == '/') return 0;
        else if (secondChar == '+' || secondChar == '-') return 1;
    } else if (firstChar == '+' || firstChar == '-') {
        if (secondChar == '*' || secondChar == '/') return -1;
        else if (secondChar == '+' || secondChar == '-') return 0;
    }
    return 0;
}

void testing(){
    for (int i = 0; i < OPERATORS_COUNT; i++){
        for (int j = 0; j < OPERATORS_COUNT; j++){
            cout << operators[i] << " " << operators[j] << " : " << getPriority(operators[i], operators[j]) << endl;
        }
    }
}

int main(){
    
    #if TESTING
        testing();
        return 0;
    #endif

    cout << "Enter an expression: ";
    string inputString; cin >> inputString;

    cout << "Result: ";

    stack<char> auxStack;

    for (int i = 0; i < inputString.length(); i++){
        char curChar = inputString[i];

        if (isOperand(curChar)){
            cout << curChar;
        } else if (isLeftParenthesis(curChar)) {
            auxStack.push(curChar);
        } else if (isOperator(curChar)){
            if (auxStack.size() == 0){
                auxStack.push(curChar);
            } else if (isLeftParenthesis(auxStack.top())) {
                auxStack.push(curChar);
            } else if (getPriority(curChar, auxStack.top()) > 0){
                auxStack.push(curChar);
            } else {
                cout << auxStack.top();
                auxStack.pop();
                i--;
            }
        } else if (isRightParenthesis(curChar)) {
            while (!isLeftParenthesis(auxStack.top())) {
                cout << auxStack.top();
                auxStack.pop();
            }
            auxStack.pop();
        }
    }

    for (int i = 0; i < auxStack.size(); i++){
        cout << auxStack.top();
        auxStack.pop();
    }
    cout << endl;
}