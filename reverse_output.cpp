//
// Created by hqnddw on 2019/5/21.
//
#include "Stack.h"
#include <iostream>

using namespace std;

void convert_recursive(Stack<char> &s, __int64 n, int base) {
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                           'A', 'B', 'C', 'D', 'E', 'F'};
    if (n > 0) {
        convert_recursive(s, n / base, base);
        s.push(digit[n % base]);
    }
}

void convert_loop(Stack<char> &s, __int64 n, int base){
    static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                           'A', 'B', 'C', 'D', 'E', 'F'};
    while (n>0){
        s.push(digit[n%base]);
        n /= base;
    }
}
//
//int main(){
//    Stack<char> s1(10000);
//    Stack<char> s2(10000);
//    __int64 n = 74589;
//    convert_recursive(s1, n, 8);
//    s1.traversal();
//    convert_loop(s2, n, 8);
//    s2.traversal();
//
//}
