#pragma once

#include "DataStructure.h"
#include "Iterator/ReverseIterator.h"
#include "Stack.h"
#include "Queue.h"
#include "DynamicArray.h"

namespace ds
{
	template <typename T> class BinaryTreeIterator;
	template <typename T> class BinaryTreeReverseIterator;

	/////////////////
	// BINARY TREE //
	/////////////////
    template <typename T>
    class BinaryTree : public DataStructure<T>, public Iterable<T>, public ReverseIterable<T>
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
        virtual void Delete(T elem); // different binary tree have different delete methods, this is default
        void Clear(Node<T>*& node);
        virtual void DebugDetails() override;
        virtual std::unique_ptr<Iterator<T>> CreateIterator() override { return CreatePreorderIterator(); }
        virtual std::unique_ptr<ReverseIterator<T>> CreateReverseIterator() override { return CreatePreorderReverseIterator(); }

    protected:
        Node<T>* getParent(Node<T>*& child);
        void prettyPrint(Node<T>* node, std::string prefix, bool isLeft, std::ostringstream& oss);

    public:
        std::unique_ptr<Iterator<T>> CreatePreorderIterator();
        std::unique_ptr<Iterator<T>> CreateInorderIterator();
        std::unique_ptr<Iterator<T>> CreatePostorderIterator();
        std::unique_ptr<Iterator<T>> CreateLevelorderIterator();
        std::unique_ptr<ReverseIterator<T>> CreatePreorderReverseIterator();
        std::unique_ptr<ReverseIterator<T>> CreateInorderReverseIterator();
        std::unique_ptr<ReverseIterator<T>> CreatePostorderReverseIterator();
        std::unique_ptr<ReverseIterator<T>> CreateLevelorderReverseIterator();

    public:
        BinaryTree& operator=(const BinaryTree& tree);
        BinaryTree& operator=(BinaryTree&& tree);

    protected:
        Node<T>* m_Root = nullptr;
    };

    template <typename T>
    BinaryTree<T>::BinaryTree()
    {
        LOG_INFO("BinaryTree CREATED successfully");
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(const BinaryTree& tree)
    {
        this->m_Size = tree.m_Size;

        if (tree.m_Root == nullptr)
        {
            return;
        }

        Queue<Node<T>*> q;
        q.Enqueue(tree.m_Root);

        while (!q.IsEmpty())
        {
            Node<T>* node = q.GetFirst();
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

        LOG_INFO("BinaryTree COPIED successfully");
    }

    template <typename T>
    BinaryTree<T>::BinaryTree(BinaryTree&& tree)
        : m_Root(tree.m_Root)
    {
        this->m_Size = tree.m_Size;

        tree.m_Root = nullptr;
        tree.m_Size = 0;
    
        LOG_INFO("BinaryTree MOVED successfully");
    }

    template <typename T>
    BinaryTree<T>::~BinaryTree()
    {
        Clear(this->m_Root);
        LOG_INFO("BinaryTree DESTROYED successfully");
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
                LOG_DEBUG("Inserting succesful, new size is %u", this->m_Size);
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
                LOG_DEBUG("Inserting succesful, new size is %u", this->m_Size);
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
        if (this->m_Root == nullptr)
        {
            LOG_ERROR("Can't delete, BinaryTree is empty");
            return;
        }

        Queue<Node<T>*> q;
        q.Enqueue(this->m_Root);

        Node<T>* delNode = nullptr;
        Node<T>* lastNode = nullptr;
        while (!q.IsEmpty()) 
        {
            lastNode = q.GetFirst();
            q.Dequeue();
        
            // delNode == nullptr is for assuring that we delete the first element found
            // for precise deletion, we need to use pointers, which sucks :(
            if (lastNode->data == elem && delNode == nullptr) 
            {
                delNode = lastNode;
            }

            if (lastNode->left != nullptr)
            {
                q.Enqueue(lastNode->left);
            }

            if (lastNode->right != nullptr) 
            {
                q.Enqueue(lastNode->right);
            }
        }

        if (delNode == nullptr)
        {
            LOG_ERROR("Can't delete, element doesn't exist");
            return;
        }

        if (lastNode == this->m_Root)
        {
            delete this->m_Root;
            this->m_Root = nullptr;
            this->m_Size = 0;
            LOG_DEBUG("Element deleted successfully, new size is %u", this->m_Size);
            return;
        }

        delNode->data = lastNode->data;
        Node<T>* parent = getParent(lastNode);
        if (parent == nullptr)
        {
            LOG_FATAL("Parent node not found, very bad!");
            exit(1);
        }

        if (parent->left == lastNode) 
        {
            delete parent->left;
            parent->left = nullptr;
        }

        if (parent->right == lastNode) 
        {
            delete parent->right;
            parent->right = nullptr;
        }
    
        this->m_Size--;
        LOG_DEBUG("Element deleted successfully, new size is %u", this->m_Size);
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

        if(this->m_Size == 0)
        {
            LOG_DEBUG("BinaryTree has been cleared");
        }
    }

    template <typename T>
    void BinaryTree<T>::DebugDetails()
    {
        std::ostringstream oss;

        this->prettyPrint(this->m_Root, "", true, oss);

        LOG_DEBUG("This is a BinaryTree\nSize: %u\nBytes: %u\nData: \n%s",
            this->m_Size,
            this->m_Size * sizeof(Node<T>),
            oss.str().c_str()
        );
    }

    template<typename T>
    typename BinaryTree<T>::template Node<T>* BinaryTree<T>::getParent(BinaryTree<T>::Node<T>*& child)
    {
        Queue<Node<T>*> q;
        q.Enqueue(this->m_Root);
        while (!q.IsEmpty()) 
        {
            Node<T>* node = q.GetFirst();
            q.Dequeue();
        
            if (node->left == child || node->right == child) 
            {
                return node;
            }

            if (node->left != nullptr)
            {
                q.Enqueue(node->left);
            }

            if (node->right != nullptr) 
            {
                q.Enqueue(node->right);
            }
        }

        return nullptr; // This should never happen, unless something EXTREMELY wrong happens
    }

    template<typename T>
    void BinaryTree<T>::prettyPrint(Node<T>* node, std::string prefix, bool isLeft, std::ostringstream& oss)
    {
        if (node == nullptr)
        {
            oss << prefix << (isLeft ? "\\-- " : "|-- ") << "NULL\n";
            return;
        }

        oss << prefix << (isLeft ? "\\-- " : "|-- ") << node->data << "\n";

        std::string childPrefix = prefix + (isLeft ? "    " : "|   ");
        prettyPrint(node->left, childPrefix, false, oss);
        prettyPrint(node->right, childPrefix, true, oss);
    }

    template <typename T>
    std::unique_ptr<Iterator<T>> BinaryTree<T>::CreatePreorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<Iterator<T>> BinaryTree<T>::CreateInorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<Iterator<T>> BinaryTree<T>::CreatePostorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<Iterator<T>> BinaryTree<T>::CreateLevelorderIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<ReverseIterator<T>> BinaryTree<T>::CreatePreorderReverseIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeReverseIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeReverseIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<ReverseIterator<T>> BinaryTree<T>::CreateInorderReverseIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeReverseIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeReverseIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<ReverseIterator<T>> BinaryTree<T>::CreatePostorderReverseIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeReverseIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeReverseIterator<T>>(arr);
    }

    template <typename T>
    std::unique_ptr<ReverseIterator<T>> BinaryTree<T>::CreateLevelorderReverseIterator()
    {
        if (this->m_Root == nullptr)
        {
            return std::make_unique<BinaryTreeReverseIterator<T>>(new DynamicArray<T*>(0));
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

        return std::make_unique<BinaryTreeReverseIterator<T>>(arr);
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree& tree)
    {
        Clear(this->m_Root);

        this->m_Size = tree.m_Size;

        if (tree.m_Root == nullptr)
        {
            return *this;
        }

        Queue<Node<T>*> q;
        q.Enqueue(tree.m_Root);

        while (!q.IsEmpty())
        {
            Node<T>* node = q.GetFirst();
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
        
        LOG_INFO("BinaryTree COPIED successfully");
        return *this;
    }

    template <typename T>
    BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree&& tree)
    {
        Clear(this->m_Root);

        this->m_Size = tree.m_Size;
        this->m_Root = tree.m_Root;

        tree.m_Root = nullptr;
        tree.m_Size = 0;

        LOG_INFO("BinaryTree MOVED successfully");
        return *this;
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
        virtual std::unique_ptr<Iterator<T>> Clone() override
		{
			auto it = std::make_unique<BinaryTreeIterator<T>>(this->m_BinaryTreeData);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return *this->m_BinaryTreeData->GetElementAt(m_Index); }
		virtual std::unique_ptr<Iterator<T>> operator++() override
		{
			Next();
			return Clone();
		}
		virtual std::unique_ptr<Iterator<T>> operator++(int) override
		{
			auto old = Clone();
            Next();
            return old;
		}
		virtual std::unique_ptr<Iterator<T>> operator+(uint32_t idx) override
		{
			auto it = std::make_unique<BinaryTreeIterator<T>>(this->m_BinaryTreeData);
            it->m_Index += idx;

            if (it->m_Index >= it->m_BinaryTreeData->GetSize())
            {
                it->m_Index = it->m_BinaryTreeData->GetSize();
            }

            return it;
		}
		virtual std::unique_ptr<Iterator<T>> operator=(std::unique_ptr<Iterator<T>> it) override
		{
			return it->Clone();
		}

	private:
        DynamicArray<T*>* m_BinaryTreeData;
		uint32_t m_Index = 0;
    };

    template <typename T>
    class BinaryTreeReverseIterator : public ReverseIterator<T>
    {
    public:
		BinaryTreeReverseIterator(DynamicArray<T*>* data) : m_BinaryTreeData(data), m_Index(data->GetSize() - 1) {}
		~BinaryTreeReverseIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = m_BinaryTreeData->GetSize() - 1; }
		virtual const T& GetCurrent() override { return *this->m_BinaryTreeData->GetElementAt(m_Index); }
		virtual void Prev() override { this->m_Index--; }
		virtual bool IsAtBegin() override { return this->m_Index == UINT32_MAX; }
        virtual std::unique_ptr<ReverseIterator<T>> Clone() override
		{
			auto it = std::make_unique<BinaryTreeReverseIterator<T>>(this->m_BinaryTreeData);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return *this->m_BinaryTreeData->GetElementAt(m_Index); }
		virtual std::unique_ptr<ReverseIterator<T>> operator++() override
		{
			Prev();
			return Clone();
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator++(int) override
		{
			auto old = Clone();
            Prev();
            return old;
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator+(uint32_t idx) override
		{
			auto it = std::make_unique<BinaryTreeReverseIterator<T>>(this->m_BinaryTreeData);

            if (it->m_Index < idx)
            {
                it->m_Index = UINT32_MAX;
            }
            else
            {
                it->m_Index -= idx;
            }

            return it;
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator=(std::unique_ptr<ReverseIterator<T>> it) override
		{
			return it->Clone();
		}

	private:
        DynamicArray<T*>* m_BinaryTreeData;
		uint32_t m_Index;
    };
	//////////////
	// ITERATOR //
	//////////////
}
