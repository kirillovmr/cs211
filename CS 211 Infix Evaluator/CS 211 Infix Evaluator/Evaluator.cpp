//
//  Evaluator.cpp
//  CS 211 Infix Evaluator
//
//  Created by Viktor Kirillov on 11/8/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#include "Evaluator.hpp"

#define EOLN 0

using std::cout;
using std::endl;

inline bool isOperator(char ch) {
    return ( ('+' == ch) || ('-' == ch) || ('*' == ch) || ('/' == ch) || ('(' == ch) || (')' == ch) );
}

inline bool isValue(char ch) {
    return ( (ch >= 48) && (ch <= 57) );
}

inline int eval(int b, char op, int a) {
    if (op == '+')
        return (a + b);
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
    if (op == '/')
        return a / b;
    
    return -1;
}

void Evaluator::operator()(std::istream &stream) {
    m_valueStack.reset();
    m_operatorStack.reset();
    
    cout << "Your input: ";
    stream.getline(m_input, m_inputSize);
    
    for (int i=0; i<m_inputSize; i++) {
        
        if (isValue(m_input[i]))
            m_valueStack.push(m_input[i]-'0');
        
        else if (isOperator(m_input[i])) {
            if (!m_operatorStack.isEmpty())
                m_valueStack.push( eval(m_valueStack.popTop(), m_operatorStack.popTop(), m_valueStack.popTop()) );
            m_operatorStack.push(m_input[i]);
        }
        
        else if ((int)m_input[i] == EOLN) {
            while (!m_operatorStack.isEmpty()) {
                m_valueStack.push( eval(m_valueStack.popTop(), m_operatorStack.popTop(), m_valueStack.popTop()) );
            }
            break;
        }
    
    }
    cout << "Res: " << m_valueStack.top() << endl;
}
