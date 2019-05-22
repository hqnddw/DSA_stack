//
// Created by hqnddw on 2019/5/21.
//
#include <iostream>
#include "Stack.h"

using namespace std;

bool parentheses(char const exp[], int lo, int hi) {
    Stack<char> s(10000);
    for (int i = lo; i < hi; ++i) {
        if (exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
            s.push(exp[i]);
        else if (!s.isEmpty()) {
            if (exp[i] == ']' && s.pop() != '[')
                return false;
            if (exp[i] == ')' && s.pop() != '(')
                return false;
            if (exp[i] == '}' && s.pop() != '{')
                return false;
        }
    }
    return s.isEmpty();
}

//int main() {
//    char exp[] = {'{', '[', ']', '(', ')', '}'};
//    bool flag = parentheses(exp, 0, 6);
//    cout << flag << endl;
//}