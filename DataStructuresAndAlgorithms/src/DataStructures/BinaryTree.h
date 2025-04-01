#pragma once

#include "DataStructure.h"
#include "Stack.h"
#include "Queue.h"
#include "DynamicArray.h"
#include "Iterator/Iterator.h"
#include "Iterator/Iterable.h"

namespace ds
{
	template <typename T> class BinaryTreeIterator;

	/////////////////
	// BINARY TREE //
	/////////////////
    template <typename T>
    class BinaryTree : public DataStructure<T>, public Iterable<T>
    {
    protected:
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
        virtual void Insert(T elem); // this method differs based on the type of binary tree
        void Delete(T elem); // TODO: Implement this
        void Clear(Node<T>*& node);
        virtual void Print() override;
        virtual Iterator<T>* CreateIterator() override { return CreatePreorderIterator(); }
        Iterator<T>* CreatePreorderIterator();
        Iterator<T>* CreateInorderIterator();
        Iterator<T>* CreatePostorderIterator();
        Iterator<T>* CreateLevelorderIterator();

    public:
        BinaryTree& operator=(const BinaryTree& tree);
        BinaryTree& operator=(BinaryTree&& tree);

    protected:
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
        Clear(this->m_Root);
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
    void BinaryTree<T>::Delete(T elem)
    {
        // remain to be implemented
    }

    template <typename T>
    void BinaryTree<T>::Clear(Node<T>*& node)
    {
        if(node != nullptr)
        {
            Clear(node->left);
            Clear(node->right);
            
            delete node;
            node = nullptr;

            --this->m_Size;
        }
    }

    template <typename T>
    void BinaryTree<T>::Print()
    {
        LOG_DEBUG("This is a BinaryTree");
        LOG_WARN("You can't print a BinaryTree, you have to choose an order and create an iterator for it, there are 4 methods inside this class, and default iterator creation is Preorder");
        if (this->m_Root == nullptr)
        {
            LOG_DEBUG("BinaryTree is empty");
            return;
        }
    }

    template <typename T>
    Iterator<T>* BinaryTree<T>::CreatePreorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return nullptr;
        }

        DynamicArray<T*>* arr = new DynamicArray<T*>(this->m_Size);
        Stack<Node<T>*> s;
        s.Push(this->m_Root);

        while (!s.IsEmpty())
        {
            Node<T>* node = s.GetTop();
            s.Pop();

            arr->Add(&node->data);

            if (node->right != nullptr)
            {
                s.Push(node->right);
            }

            if (node->left != nullptr)
            {
                s.Push(node->left);
            }
        }

        return new BinaryTreeIterator<T>(arr);
    }

    template <typename T>
    Iterator<T>* BinaryTree<T>::CreateInorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return nullptr;
        }

        DynamicArray<T*>* arr = new DynamicArray<T*>(this->m_Size);
        Stack<Node<T>*> s;
        Node<T>* curNode = this->m_Root;

        while (curNode != nullptr || !s.IsEmpty())
        {
            while (curNode != nullptr)
            {
                s.Push(curNode);
                curNode = curNode->left;
            }

            Node<T>* node = s.GetTop();
            s.Pop();

            arr->Add(&node->data);

            curNode = node->right;
        }

        return new BinaryTreeIterator<T>(arr);
    }

    template <typename T>
    Iterator<T>* BinaryTree<T>::CreatePostorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return nullptr;
        }

        DynamicArray<T*>* arr = new DynamicArray<T*>(this->m_Size);
        Stack<Node<T>*> s1;
        Stack<Node<T>*> s2;

        s1.Push(this->m_Root);

        while (!s1.IsEmpty())
        {
            Node<T>* node = s1.GetTop();
            s1.Pop();
            s2.Push(node);

            if (node->left != nullptr)
            {
                s1.Push(node->left);
            }

            if (node->right != nullptr)
            {
                s1.Push(node->right);
            }
        }

        while (!s2.IsEmpty())
        {
            Node<T>* node = s2.GetTop();
            s2.Pop();
            arr->Add(&node->data);
        }

        return new BinaryTreeIterator<T>(arr);
    }

    template <typename T>
    Iterator<T>* BinaryTree<T>::CreateLevelorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return nullptr;
        }

        DynamicArray<T*>* arr = new DynamicArray<T*>(this->m_Size);
        Queue<Node<T>*> q;
        q.Enqueue(m_Root);

        while (!q.IsEmpty()) 
        {
            Node<T>* node = q.GetFirst();
            q.Dequeue();
        
            arr->Add(&node->data);

            if (node->left != nullptr)
            {
                q.Enqueue(node->left);
            }

            if (node->right != nullptr) 
            {
                q.Enqueue(node->right);
            }
        }

        return new BinaryTreeIterator<T>(arr);
    }
	/////////////////
	// BINARY TREE //
	/////////////////

	//////////////
	// ITERATOR //
	//////////////
    template <typename T>
    class BinaryTreeIterator : public Iterator<T>
    {
    public:
		BinaryTreeIterator(DynamicArray<T*>* data) : m_BinaryTreeData(data) {}
		~BinaryTreeIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = 0; }
		virtual const T& GetCurrent() override { return *this->m_BinaryTreeData->GetElementAt(m_Index); }
		virtual void Next() override { this->m_Index++; }
		virtual bool IsAtEnd() override { return this->m_Index >= this->m_BinaryTreeData->GetSize(); }

	public:
		virtual T& operator*() override { return *this->m_BinaryTreeData->GetElementAt(m_Index); }
		virtual Iterator<T>& operator++() override
		{
			Next();
			return *this;
		}

	private:
        DynamicArray<T*>* m_BinaryTreeData;
		uint32_t m_Index = 0;
    };
	//////////////
	// ITERATOR //
	//////////////
}
