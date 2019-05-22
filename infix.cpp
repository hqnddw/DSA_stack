//
// Created by hqnddw on 2019/5/21.
//
#include "Stack.h"
#include <iostream>
#include <math.h>
#include <cstring>

using namespace std;
#define N_OPTR 9  //运算符总数

//运算符优先级表
const char pri[N_OPTR][N_OPTR] = { // [栈顶][当前]
        /*           | --------------当前运算符---------- */
        /*           +    -    *    /    ^    !    (    )   \0  */
        /* -- + */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /*  | - */  '>', '>', '<', '<', '<', '<', '<', '>', '>',
        /* 栈 * */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 顶 / */  '>', '>', '>', '>', '<', '<', '<', '>', '>',
        /* 运 ^ */  '>', '>', '>', '>', '>', '<', '<', '>', '>',
        /* 算 ! */  '>', '>', '>', '>', '>', '>', ' ', '>', '>',
        /* 符 ( */  '<', '<', '<', '<', '<', '<', '<', '=', ' ',
        /*  | ) */  ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /*-- \0 */  '<', '<', '<', '<', '<', '<', '<', ' ', '='
};


const float calcu(float num2, char i, float num1) {
    switch (i) {
        case '+':
            return num2 + num1;
        case '-':
            return num2 - num1;
        case '*':
            return num2 * num1;
        case '/':
            return num2 / num1;
        case '^':
            return pow(num2, num1);
        default:
            break;
    }
    return -1;
}


const float calcu(char op, float f) {
    int re = 1;
    if (op == '!') {
        for (int i = (int) f; i > 1; i--) {
            re *= i;
        }
    }
    return re;
}


void readNumber(char *&p, Stack<float> &stack) {
    stack.push((float) (*p - '0'));
    while (isdigit(*(++p)))
        stack.push(stack.pop() * 10 + (*p - '0'));
    if (*p != '.') return; //此后非小数点，则说明当前操作数解析完成
    float fraction = 1;
    while (isdigit(*(++p)))
        stack.push(stack.pop() + (*p - '0') * (fraction /= 10)); //小数部分
}

int optr2rank(char op) {
    switch (op) {
        case '+':
            return 0;
        case '-':
            return 1;
        case '*':
            return 2;
        case '/':
            return 3;
        case '^':
            return 4;
        case '!':
            return 5;
        case '(':
            return 6;
        case ')':
            return 7;
        case '\0':
            return 8;
        default:
            exit(-1);
    }
}

char orderBetween(char op1, char op2) {
    return pri[optr2rank(op1)][optr2rank(op2)];
}

void append(char *&rpn, float opnd) { //将操作数接至RPN末尾
    int n = static_cast<int>(strlen(rpn)); //RPN当前长度（以'\0'结尾，长度n + 1）
    char buf[64];
    if (opnd != (float) (int) opnd) sprintf(buf, "%.2f \0", opnd); //浮点格式，或
    else sprintf(buf, "%d \0", (int) opnd); //整数格式
    rpn = (char *) realloc(rpn, sizeof(char) * (n + strlen(buf) + 1)); //扩展空间
    strcat(rpn, buf); //RPN加长
}

void append(char *&rpn, char optr) { //将运算符接至RPN末尾
    int n = static_cast<int>(strlen(rpn)); //RPN当前长度（以'\0'结尾，长度n + 1）
    rpn = (char *) realloc(rpn, sizeof(char) * (n + 3)); //扩展空间
    sprintf(rpn + n, "%c ", optr);
    rpn[n + 2] = '\0'; //接入指定的运算符
}

float evaluate(char *s, char *&RPN) {
    Stack<float> opnd;
    Stack<char> optr;
    optr.push('\0');
    while (!optr.isEmpty()) {
        if (isdigit(*s)) {
            readNumber(s, opnd); //读入操作数
            append(RPN, opnd.top());
        } else
            switch (orderBetween(optr.top(), *s)) {
                case '<': //栈顶运算符优先级更低时
                    optr.push(*s); //脱括号
                    s++;
                    break;
                case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                    optr.pop();
                    s++;
                    break;
                case '>': {//栈顶运算符优先级更高时，实施相应的计算，并将计算结果入栈
                    char op = optr.pop();
                    append(RPN, op);
                    if (op == '!')
                        opnd.push(calcu(op, opnd.pop()));
                    else {
                        float num1 = opnd.pop();
                        float num2 = opnd.pop();
                        opnd.push(calcu(num2, op, num1));
                    }
                    break;
                }
                default:
                    exit(-1); //语法错误直接退出
            } //switch
    } //while
    return opnd.pop();
}


int main() {
    char *RPN = (char *) malloc(sizeof(char) * 1);
    RPN[0] = '\0';
    char exp1[] = {'(', '1', '+', '2', '0', ')', '*', '3', '^', '4', '+', '5', '!', '\0'};
    cout << evaluate(exp1, RPN) << endl;
    cout << "RPN is: " << RPN << endl;
    return 0;
}