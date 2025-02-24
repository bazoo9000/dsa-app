#pragma once

#include <iostream>
#include "DataStructure.h"
#include "Queue.h"

// !! This remains to be reimplemented !! // 
// TODO: Make Iterator and use strategy pattern for type of traversal

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

            Node(U data, Node* left = nullptr, Node* right = nullptr)
			{
				this->data = data;
				this->left = left;
				this->right = right;
			}
        };

    public:
        BinaryTree();
        BinaryTree(const BinaryTree& tree);
        BinaryTree(BinaryTree&& tree);
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
        void* Find(T elem);
        void Delete(T elem);
        virtual void Print() override { Print(PrintOrderType::NONE); }
        void Print(PrintOrderType type = PrintOrderType::NONE);

    public:
        BinaryTree& operator=(const BinaryTree& tree);
        BinaryTree& operator=(BinaryTree&& tree);

    private:
        void printPRE(Node<T>* node);
        void printIN(Node<T>* node);
        void printPOST(Node<T>* node);
        void printLEVEL();
        void deleteTree(Node<T>* node);

    private:
        Node<T>* m_Root = nullptr;
    };

    template <typename T>
    BinaryTree<T>::BinaryTree()
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
        Node<T>* newNode = new Node<T>(elem);

        if (m_Root == nullptr)
        {
            this->m_Root = newNode;
            ++this->m_Size;
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
                ++this->m_Size;
                return;
            }
            else
            {
                q.Enqueue(node->left);
            }

            if (node->right == nullptr)
            {
                node->right = newNode;
                ++this->m_Size;
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
            printPRE(this->m_Root);
            break;

        case PrintOrderType::INORDER:
            printIN(this->m_Root);
            break;

        case PrintOrderType::POSTORDER:
            printPOST(this->m_Root);
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

            --this->m_Size;
        }
    }
}
