#pragma once

#include <iostream>
#include "LinkedList.h"

namespace ds 
{
    template <typename T>
    class Tree
    {
    private:
        template <typename U>
        struct Node
        {
            U data;
            LinkedList<Node*> node; 
        };
        
    public:
        Tree(/* args */);
        ~Tree();
    };

    template <typename T>
    Tree<T>::Tree(/* args */)
    {
    }

    template <typename T>
    Tree<T>::~Tree()
    {
    }
}
