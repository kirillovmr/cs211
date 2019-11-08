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

inline bool isParanthesis(char ch) {
    return ( ('(' == ch) || (')' == ch) );
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

Evaluator::Evaluator(bool debug): m_debug(debug) {}

void Evaluator::printCommands() {
    cout << "The commands for this program are:\n\n";
    cout << "q - to quit the program\n";
    cout << "? - to list the accepted commands\n";
    cout << "or any infix mathematical expression using operators of (), *, /, +, -\n";
}

void Evaluator::popAndEval() {
    m_valueStack.push( eval(m_valueStack.popTop(), m_operatorStack.popTop(), m_valueStack.popTop()) );
}

void Evaluator::operator()(std::istream &stream) {
    while(!false) {
        m_valueStack.reset();
        m_operatorStack.reset();
        
        cout << "Your input: ";
        stream.getline(m_input, m_inputSize);
        
        if (m_input[0] == 'q')
            return;
        
        if (m_input[0] == '?') {
            printCommands();
            continue;
        }
        
        for (int i=0; i<m_inputSize; i++) {
            
            // Parsing next subbsequent digits if present
            if (isValue(m_input[i])) {
                int val = m_input[i]-'0';
                while(isValue(m_input[i+1]))
                    val = val * 10 + (m_input[++i]-'0');
                if (m_debug)
                    cout << "Encountered value '" << val << "'" << endl;
                m_valueStack.push(val);
            }
            
            else if (isOperator(m_input[i])) {
                if (m_debug)
                    cout << "Encountered operator '" << m_input[i] << "'" << endl;
                
                if (m_input[i] == '(')
                    m_operatorStack.push(m_input[i]);
                
                if (m_input[i] == '+' || m_input[i] == '-') {
                    while (!m_operatorStack.isEmpty() && !isParanthesis(m_operatorStack.top()))
                        popAndEval();
                    m_operatorStack.push(m_input[i]);
                }
                
                if (m_input[i] == '*' || m_input[i] == '/') {
                    while (!m_operatorStack.isEmpty() && (m_operatorStack.top() == '*' || m_operatorStack.top() == '/'))
                        popAndEval();
                    m_operatorStack.push(m_input[i]);
                }
                
                if (m_input[i] == ')') {
                    while (!m_operatorStack.isEmpty() && m_operatorStack.top() != '(')
                        popAndEval();
                    if (m_operatorStack.isEmpty())
                        cout << "Error message\n";
                    else
                        m_operatorStack.pop();
                }
            }
            
            else if ((int)m_input[i] == EOLN) {
                while (!m_operatorStack.isEmpty())
                    popAndEval();
                break;
            }
        
        }
        cout << "Result: " << m_valueStack.top() << endl << endl;
    }
}
