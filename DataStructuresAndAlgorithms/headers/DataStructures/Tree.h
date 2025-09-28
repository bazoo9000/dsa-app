#pragma once

#include "DataStructure.h"
#include "DynamicArray.h"

// remains to be implemented
namespace ds 
{
    template <typename T>
    class Tree : public DataStructure<T>
    {
    private:
        template <typename U>
        struct Node
        {
            U data;
            DynamicArray<Node*> node; 
        };
        
    public:
        Tree();
        Tree(const Tree& tree);
        Tree(Tree&& tree);
        ~Tree();

    public:
        void Insert(T elem);
        void Clear();
        virtual void DebugDetails() override;

    public:
        Tree& operator=(const Tree& tree);
        Tree& operator=(Tree&& tree);

    private:
        Node<T>* m_Root;
    };

    template <typename T>
    Tree<T>::Tree()
    {
    }

    template <typename T>
    Tree<T>::~Tree()
    {
    }
}
