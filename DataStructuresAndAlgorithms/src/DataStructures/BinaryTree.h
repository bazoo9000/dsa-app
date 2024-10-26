#pragma once

#include <iostream>
#include "DataStructure.h"
#include "Queue.h"

namespace ds
{
    template <typename T>
    class BinaryTree : public DataStructure<T>
    {
    private:
        template<typename U>
        struct Node
        {
            U data;
            Node* left;
            Node* right;
        };

    public:
        BinaryTree();
        ~BinaryTree();

    public:
        enum class PrintOrderType
        {
            NONE = 0,
            PREORDER, INORDER, POSTORDER, // DFS
            LEVELORDER                    // BFS
        };

    public:
        void Insert(T elem);
        virtual void Print() override { Print(PrintOrderType::NONE); }
        void Print(PrintOrderType type = PrintOrderType::NONE);

    public:
        uint32_t GetSize() { return m_Size; }

    private:
        void printPRE(Node<T>* node);
        void printIN(Node<T>* node);
        void printPOST(Node<T>* node);
        void printLEVEL();
        void deleteTree(Node<T>* node);

    private:
        Node<T>* m_Root;
        uint32_t m_Size; // amount of elements in tree
    };

    template <typename T>
    BinaryTree<T>::BinaryTree()
        : m_Root(nullptr), m_Size(0)
    {
        // nimic
    }

    template <typename T>
    BinaryTree<T>::~BinaryTree()
    {
        deleteTree(m_Root);
    }

    template <typename T>
    void BinaryTree<T>::Insert(T elem)
    {
        Node<T>* newNode = new Node<T>;
        newNode->data = elem;
        newNode->left = nullptr;
        newNode->right = nullptr;

        if (m_Root == nullptr)
        {
            m_Root = newNode;
            ++m_Size;
            return;
        }

        Queue<Node<T>*> q;
        q.Enqueue(m_Root);

        while (!q.IsEmpty())
        {
            Node<T>* node = q.GetFirst();
            q.Dequeue();

            if (node->left == nullptr)
            {
                node->left = newNode;
                ++m_Size;
                return;
            }
            else
            {
                q.Enqueue(node->left);
            }

            if (node->right == nullptr)
            {
                node->right = newNode;
                ++m_Size;
                return;
            }
            else
            {
                q.Enqueue(node->right);
            }
        }
    }

    template <typename T>
    void BinaryTree<T>::Print(PrintOrderType type)
    {
        switch (type)
        {
        case PrintOrderType::NONE:
            std::cout << "Please provide a print type.\n";
            break;

        case PrintOrderType::PREORDER:
            printPRE(m_Root);
            break;

        case PrintOrderType::INORDER:
            printIN(m_Root);
            break;

        case PrintOrderType::POSTORDER:
            printPOST(m_Root);
            break;

        case PrintOrderType::LEVELORDER:
            printLEVEL();
            break;

        default: std::cout << "Invalid print type.\n";
        }

        std::cout << "\n";
    }

    template <typename T>
    void BinaryTree<T>::printPRE(Node<T>* node)
    {
        if (node == nullptr) return;

        std::cout << node->data << " ";
        printPRE(node->left);
        printPRE(node->right);
    }

    template <typename T>
    void BinaryTree<T>::printIN(Node<T>* node)
    {
        if (node == nullptr) return;

        printIN(node->left);
        std::cout << node->data << " ";
        printIN(node->right);
    }

    template <typename T>
    void BinaryTree<T>::printPOST(Node<T>* node)
    {
        if (node == nullptr) return;

        printPOST(node->left);
        printPOST(node->right);
        std::cout << node->data << " ";
    }

    template <typename T>
    void BinaryTree<T>::printLEVEL()
    {
        Queue<Node<T>*> q;
        q.Enqueue(m_Root);

        while (!q.IsEmpty()) 
        {
            Node<T>* node = q.GetFirst();
            q.Dequeue();
            std::cout << node->data << " ";

            if (node->left != nullptr)
            {
                q.Enqueue(node->left);
            }

            if (node->right != nullptr) 
            {
                q.Enqueue(node->right);
            }
        }
    }

    template <typename T>
    void BinaryTree<T>::deleteTree(Node<T>* node)
    {
        if(node != nullptr)
        {
            deleteTree(node->left);
            deleteTree(node->right);
            
            delete node;
            node = nullptr;

            --m_Size;
        }
    }
}
