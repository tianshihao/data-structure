/**
 * @file stack.hpp
 * @author tianshihao
 * @brief Template class of stack.
 * @version 0.1
 * @date 2020-08-26
 * 
 * @copyright Copyright (c) 2020
 * 
 */
#ifndef STACK_HPP_
#define STACK_HPP_

#include <iostream>
using namespace std;

template <typename Type>
class Stack
{
private:
    enum constant
    {
        MAX_SIZE = 100
    };
    Type items[MAX_SIZE]; // store elements.
    int top;              // pointer to the top of the stack.

public:
    Stack() { this->top = 0; }

    /**
     * @brief Get the size of the stack.
     * @return int stack size.
     */
    inline int Size() const { return top; }

    /**
     * @brief Judge if stack is empty. 
     * @return true stack is empty.
     * @return false stack is not empty.
     */
    inline bool IsEmpty() const { return top == 0; }

    /**
     * @brief judge if stack is full.
     * @return true stack is full.
     * @return false stack is not full.
     */
    inline bool IsFull() const { return top == MAX_SIZE; }

    /**
     * @brief Add an item at the top of the stack.
     * @param item The item you want to add.
     * @return true Add successful.
     * @return false failed.
     */
    bool Push(const Type &item);

    /**
     * @brief Remove an item from the top of the stack, and returns the copy of
     * it.
     * @param item Be used to store the copy of the item of the stack top.
     * @return true Operation successful.
     * @return false Operation failed.
     */
    bool Pop(Type &item);
};

template <typename Type>
bool Stack<Type>::Push(const Type &item)
{
    if (top >= MAX_SIZE)
    {
        return false;
    }
    else
    {
        this->items[top++] = item;
        return true;
    }
}

template <typename Type>
bool Stack<Type>::Pop(Type &item)
{
    if (top <= 0)
    {
        return false;
    }
    else
    {
        item = this->items[--top];
        return true;
    }
}

#endif // STACK_HPP_
