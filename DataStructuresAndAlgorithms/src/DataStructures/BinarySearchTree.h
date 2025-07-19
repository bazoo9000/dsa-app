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
        virtual void Delete(T elem) override;
        virtual void Print() override;

    private:
        uint32_t childCount(typename BinaryTree<T>::template Node<T>*& node);
        void deleteZeroChildren(typename BinaryTree<T>::template Node<T>*& node, typename BinaryTree<T>::template Node<T>*& parent);
        void deleteOneChild(typename BinaryTree<T>::template Node<T>*& node, typename BinaryTree<T>::template Node<T>*& parent);
        void deleteTwoChildren(typename BinaryTree<T>::template Node<T>*& node);

    public:
        BinarySearchTree& operator=(const BinarySearchTree& tree);
        BinarySearchTree& operator=(BinarySearchTree&& tree);
    };

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree()
        : BinaryTree<T>()
    {
        LOG_INFO("BinarySearchTree CREATED successfully");
    }

    template <typename T>
    BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& tree)
        : BinaryTree<T>(tree)
    {
        LOG_INFO("BinarySearchTree COPIED successfully");
    }

    template <typename T>
    BinarySearchTree<T>::~BinarySearchTree()
    {
        LOG_INFO("BinarySearchTree DESTROYED successfully");
    }

    template <typename T>
    void BinarySearchTree<T>::Insert(T elem)
    {
        typename BinaryTree<T>::template Node<T>* newNode = new typename BinaryTree<T>::template Node<T>(elem);

        if (this->m_Root == nullptr)
        {
            this->m_Root = newNode;
            ++this->m_Size;
            return;
        }

        typename BinaryTree<T>::template Node<T>* temp = this->m_Root;
        while (true)
        {
            if (temp->data == elem)
            {
                LOG_ERROR("Can't insert, element already exists");
                delete newNode;
                return;
            }

            if (elem < temp->data)
            {
                if (temp->left == nullptr)
                {
                    temp->left = newNode;
                    this->m_Size++;
                    LOG_DEBUG("Inserting succesful, new size is %u", this->m_Size);
                    return;
                }

                temp = temp->left;
            }

            if (elem > temp->data)
            {
                if (temp->right == nullptr)
                {
                    temp->right = newNode;
                    this->m_Size++;
                    LOG_DEBUG("Inserting succesful, new size is %u", this->m_Size);
                    return;
                }

                temp = temp->right;
            }
        }
    }

    template <typename T>
    void BinarySearchTree<T>::Delete(T elem)
    {
        if (this->m_Root == nullptr)
        {
            LOG_ERROR("Can't delete, BST is empty");
            return;
        }

        typename BinaryTree<T>::template Node<T>* delNode = this->m_Root;
        typename BinaryTree<T>::template Node<T>* parent = nullptr;

        while(delNode != nullptr)
        {
            if (delNode->data == elem)
            {
                break;
            }

            parent = delNode;

            if (elem < delNode->data)
            {
                delNode = delNode->left;
            }
            else
            {
                delNode = delNode->right;
            }
        }

        if (delNode == nullptr)
        {
            LOG_ERROR("Can't delete, element doesn't exist");
            return;
        }

        uint32_t count = childCount(delNode);
        switch (count)
        {
            case 0:
                deleteZeroChildren(delNode, parent);
                break;
            case 1:
                deleteOneChild(delNode, parent);
                break;
            case 2:
                deleteTwoChildren(delNode);
                break;
            default:
                LOG_FATAL("Node has more than 2 children, somehow"); exit(1);
        }

        LOG_DEBUG("Deleting succesful, new size is %u", this->m_Size);
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

    template <typename T>
    uint32_t BinarySearchTree<T>::childCount(typename BinaryTree<T>::template Node<T>*& node)
    {
        int count = 0;

        if (node->left != nullptr)  count++;
        if (node->right != nullptr) count++;

        return count;
    }

    template <typename T>
    void BinarySearchTree<T>::deleteZeroChildren(typename BinaryTree<T>::template Node<T>*& node, typename BinaryTree<T>::template Node<T>*& parent)
    {
        if (parent == nullptr)
        {
            delete this->m_Root;
            this->m_Root = nullptr;
            this->m_Size = 0;
            return;
        }

        if (parent->left == node)
        {
            delete parent->left;
            parent->left = nullptr;
        }
        else
        {
            delete parent->right;
            parent->right = nullptr;
        }

        this->m_Size--;
        LOG_DEBUG("Element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    void BinarySearchTree<T>::deleteOneChild(typename BinaryTree<T>::template Node<T>*& node, typename BinaryTree<T>::template Node<T>*& parent)
    {
        typename BinaryTree<T>::template Node<T>* child = (node->left != nullptr) ? node->left : node->right;

        if (parent == nullptr)
        {
            delete this->m_Root;
            this->m_Root = child;
        }
        else if (parent->left == node)
        {
            parent->left = child;
            delete node;
            node = nullptr;
        }
        else
        {
            parent->right = child;
            delete node;
            node = nullptr;
        }

        this->m_Size--;
        LOG_DEBUG("Element deleted successfully, new size is %u", this->m_Size);

    }

    template <typename T>
    void BinarySearchTree<T>::deleteTwoChildren(typename BinaryTree<T>::template Node<T>*& node)
    {
        typename BinaryTree<T>::template Node<T>* successorParent = node;
        typename BinaryTree<T>::template Node<T>* successor = node->right;
        while (successor->left != nullptr)
        {
            successorParent = successor;
            successor = successor->left;
        }

        node->data = successor->data;

        if (successorParent->left == successor)
        {
            if (successor->right)
            {
                successorParent->left = successor->right;
            }
            else
            {
                successorParent->left = nullptr;
            }
        }
        else
        {
            successorParent->right = successor->right;
        }

        delete successor;
        this->m_Size--;
        LOG_DEBUG("Element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    BinarySearchTree<T>& BinarySearchTree<T>::operator=(const BinarySearchTree<T>& tree)
    {
        Clear(this->m_Root);

        this->m_Size = tree.m_Size;

        if (tree.m_Root == nullptr)
        {
            return *this;
        }

        Queue<typename BinaryTree<T>::template Node<T>*> q;
        q.Enqueue(tree.m_Root);

        while (!q.IsEmpty())
        {
            typename BinaryTree<T>::template Node<T>* node = q.GetFirst();
            q.Dequeue();

            Insert(node->data);

            if (node->left != nullptr)
            {
                q.Enqueue(node->left);
            }

            if (node->right != nullptr)
            {
                q.Enqueue(node->right);
            }
        }

        LOG_INFO("BinarySearchTree COPIED successfully");
        return *this;
    }

    template <typename T>
    BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& tree)
    {
        Clear(this->m_Root);

        this->m_Size = tree.m_Size;
        this->m_Root = tree.m_Root;

        tree.m_Root = nullptr;
        tree.m_Size = 0;

        LOG_INFO("BinarySearchTree MOVED successfully");
        return *this;
    }
	////////////////////////
	// BINARY SEARCH TREE //
	////////////////////////
}
