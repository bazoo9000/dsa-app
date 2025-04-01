#pragma once

#include "DataStructure.h"
#include "BinaryTree.h"

namespace ds
{
	template <typename T> class BinaryTreeIterator;

	////////////////////////
	// BINARY SEARCH TREE //
	////////////////////////
    template <typename T>
    class BinarySearchTree : public BinaryTree<T>
    {
    public:
        BinarySearchTree();
        BinarySearchTree(const BinarySearchTree& tree);
        BinarySearchTree(BinarySearchTree&& tree);
        ~BinarySearchTree();

    public:
        virtual void Insert(T elem) override;
        virtual void Print() override;

    public:
        BinarySearchTree& operator=(const BinarySearchTree& tree);
        BinarySearchTree& operator=(BinarySearchTree&& tree);
    };

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree()
    {
        BinaryTree<T>::BinaryTree();
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        // deletion is handled in the parent class
    }

    template <typename T>
    void BinarySearchTree<T>::Insert(T elem)
    {
        // c++ be like :(
        typename BinaryTree<T>::template Node<T>* newNode = new typename BinaryTree<T>::template Node<T>(elem);

        if (this->m_Root == nullptr)
        {
            this->m_Root = newNode;
            ++this->m_Size;
            return;
        }

        Queue<typename BinaryTree<T>::template Node<T>*> q;
        q.Enqueue(this->m_Root);

        while (!q.IsEmpty())
        {
            typename BinaryTree<T>::template Node<T>* node = q.GetFirst();
            q.Dequeue();

            if (node->left == nullptr && elem < node->data)
            {
                node->left = newNode;
                ++this->m_Size;
                return;
            }
            else
            {
                q.Enqueue(node->left);
            }

            if (node->right == nullptr && elem > node->data)
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
    void BinarySearchTree<T>::Print()
    {
        LOG_DEBUG("This is a BinarySearchTree");
        LOG_WARN("You can't print a BinarySearchTree, you have to choose an order and create an iterator for it, there are 4 methods inside this class, and default iterator creation is Preorder");
        if (this->m_Root == nullptr)
        {
            LOG_DEBUG("BinarySearchTree is empty");
            return;
        }
    }
	////////////////////////
	// BINARY SEARCH TREE //
	////////////////////////

	//////////////
	// ITERATOR //
	//////////////
    
    // already defined in BinaryTree.h

	//////////////
	// ITERATOR //
	//////////////
}
