//
//  Evaluator.hpp
//  CS 211 Infix Evaluator
//
//  Created by Viktor Kirillov on 11/8/19.
//  Copyright © 2019 Viktor Kirillov. All rights reserved.
//

#ifndef Evaluator_hpp
#define Evaluator_hpp

#include "Stack.hpp"
#include <iostream>
#include <string>

class Evaluator {
private:
    MyStack m_valueStack;
    MyStack m_operatorStack;
    static const int m_inputSize = 256;
    char m_input[m_inputSize];
    
public:
    Evaluator() = default;
    
    void operator()(std::istream &stream);
};

#endif /* Evaluator_hpp */
