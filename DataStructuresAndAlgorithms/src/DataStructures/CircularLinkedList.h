#pragma once

#include "DataStructure.h"

namespace ds
{
    template <typename T>
    class CircularLinkedList : public DataStructure<T>
    {
    private:
        template <typename U>
        struct Node
        {
            U data;
            Node* next = nullptr;

            Node(U data, Node* next)
            {
                this->data = data;
                this->next = next;
            }
        };

    public:
        CircularLinkedList();
        CircularLinkedList(const CircularLinkedList<T>& list);
        CircularLinkedList(CircularLinkedList<T>&& list);
        ~CircularLinkedList();

    public:
        void Append(T elem);
        void Prepend(T elem);
        void InsertAt(T elem, uint32_t index);
        void* Find(T elem);
		T GetFirst();
        T GetLast();
        T GetElementAt(uint32_t index);
        void DeleteFirst();
        void Delete(T elem);
        void DeleteAt(uint32_t index);
        void Clear();
        virtual void DebugDetails() override;

    public:
        T& operator[](uint32_t index) { return GetElementAt(index); }
        CircularLinkedList& operator=(const CircularLinkedList& list);
        CircularLinkedList& operator=(CircularLinkedList&& list);

    private:
        Node<T>* m_Head;
        Node<T>* m_Tail;
    };

    template <typename T>
    CircularLinkedList<T>::CircularLinkedList()
        : m_Head(nullptr), m_Tail(nullptr)
    {
        LOG_INFO("CircularLinkedList CREATED successfully");
    }

    template <typename T>
    CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& list)
    {
        this->m_Size = list.m_Size;
        
        if(!list.m_Head)
        {
            this->m_Head = this->m_Tail = nullptr;
            return;
        }

        this->m_Head = new Node<T>(list.m_Head->data);

        Node<T>* head = this->m_Head;
        Node<T>* nextOther = list.m_Head->next;

        while (nextOther) 
        {
            head->next = new Node<T>(nextOther->data);
            head = head->next;
            nextOther = nextOther->next;
        }

        this->m_Tail = head;
        this->m_Tail->next = this->m_Head;

        LOG_INFO("CircularLinkedList COPIED successfully");
    }

    template <typename T>
    CircularLinkedList<T>::CircularLinkedList(CircularLinkedList<T>&& list)
        : m_Head(list.m_Head), m_Tail(list.m_Tail)
    {
        this->m_Size = list.m_Size;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("CircularLinkedList MOVED successfully");
    }

    template <typename T>
    CircularLinkedList<T>::~CircularLinkedList()
    {
        Clear();
        LOG_INFO("CircularLinkedList DESTROYED successfully");
    }

    template <typename T>
    void CircularLinkedList<T>::Append(T elem)
    {
        Node<T>* newNode = new Node<T>(elem, this->m_Head);

        if (this->m_Tail == nullptr) 
        {
            this->m_Head = this->m_Tail = newNode; // in case there was no element in the list
        }
        else 
        {
            this->m_Tail->next = newNode;
            this->m_Tail = newNode;
        }

        ++this->m_Size;

        LOG_DEBUG("Append successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void CircularLinkedList<T>::Prepend(T elem)
    {
        Node<T>* newNode = new Node<T>(elem, this->m_Head);

        if (this->m_Head == nullptr)
        {
            this->m_Head = this->m_Tail = newNode; // in case there was no element in the list
        }
        else
        {
            newNode->next = this->m_Head;
            this->m_Head = newNode;
        }

        ++this->m_Size;

        LOG_DEBUG("Prepend successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void CircularLinkedList<T>::InsertAt(T elem, uint32_t index)
    {
        if (index > this->m_Size)
        {
            LOG_ERROR("Can't insert, index %u is out of range", index);
            return;
        }

        if (index == 0)
        {
            Prepend(elem);
            return;
        }

        if (index == this->m_Size)
        {
            Append(elem);
            return;
        }

        Node<T>* prevNode = this->m_Head;

        for (uint32_t i = 0; i < index - 1 && prevNode != nullptr; ++i)
        {
            prevNode = prevNode->next;
        }
        
        Node<T>* newNode = new Node<T>(elem);

        newNode->next = prevNode->next;
        prevNode->next = newNode;

        ++this->m_Size;

        LOG_DEBUG("Inserting at index %u succesful, new size is %u", index, this->m_Size);
    }

    template <typename T>
    void* CircularLinkedList<T>::Find(T elem)
    {
        Node<T>* curNode = this->m_Head;
        do
        {
            if (curNode->data == elem)
            {
                LOG_DEBUG("Element found");
                return curNode;
            }

            curNode = curNode->next;
        }
        while (curNode != this->m_Head);

        LOG_DEBUG("Element NOT found");
        return nullptr;
    }

	template <typename T>
    T CircularLinkedList<T>::GetFirst()
	{
		if(!this->m_Head) 
		{ 
			LOG_FATAL("List is empty"); 
			exit(1);
		} 
		
		LOG_DEBUG("Got first element succesfully");
		return this->m_Head->data;
	}

	template <typename T>
    T CircularLinkedList<T>::GetLast()
	{
		if(!this->m_Tail) 
		{ 
			LOG_FATAL("List is empty"); 
			exit(1);
		} 
		
		LOG_DEBUG("Got last element succesfully");
		return this->m_Tail->data;
	}

    template <typename T>
    T CircularLinkedList<T>::GetElementAt(uint32_t index)
    {
        if(index >= this->m_Size)
        {
            LOG_FATAL("Can't get element, index %u is out of range", index);
            exit(1);
        }

        if(index == this->m_Size - 1)
        {
            return GetLast();
        }

        if(index == 0)
        {
            return GetFirst();
        }

        Node<T>* node = m_Head;
        for(int i = 0; i < index; i++)
        {
            node = node->next;
        }

		LOG_DEBUG("Got element at index %u succesfully", index);
        return node->data;
    }

    template <typename T>
    void CircularLinkedList<T>::DeleteFirst()
    {
        if (this->m_Head == nullptr)
        {
            LOG_ERROR("Can't delete, list is empty.");
            return;
        }

        Node<T>* delNode = this->m_Head;
        this->m_Head = this->m_Head->next;
        delete delNode;

        if (this->m_Head == nullptr) // in case I delete the only element in the list
        {
            this->m_Tail = nullptr;
        }

        this->m_Tail->next = this->m_Head;
        --this->m_Size;

        LOG_DEBUG("First element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    void CircularLinkedList<T>::Delete(T elem)
    { 
        if (this->m_Head == nullptr)
        {
            LOG_ERROR("Can't delete, list is empty.");
            return;
        }

        Node<T>* delNode = (Node<T>*)Find(elem);

        if (!delNode)
        {
            LOG_ERROR("Can't delete, element doesn't exist.");
            return;
        }

        if (this->m_Head == delNode)
        {
            DeleteFirst();
            return;
        }

        Node<T>* curNode = this->m_Head;
        while (curNode->next != delNode) 
        {
            curNode = curNode->next;
        }

        curNode->next = delNode->next;
        delete delNode;

        this->m_Size--;

        LOG_DEBUG("Delete successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void CircularLinkedList<T>::DeleteAt(uint32_t index)
    {
        if (this->m_Size == 0)
        {
            LOG_ERROR("Can't delete, list is empty.");
            return;
        }
        
        if(index >= this->m_Size)
        {
            LOG_ERROR("Can't delete, index %u is out of range", index);
            return;
        }

        if(index == 0)
        {
            DeleteFirst();
            return;
        }

        Node<T>* delNode = this->m_Head->next;
        Node<T>* prevNode = this->m_Head;
        for(uint32_t i = 1; i < index; i++)
        {
            prevNode = delNode;
            delNode = delNode->next;
        }

        prevNode->next = delNode->next;
        delete delNode;

        --this->m_Size;

        LOG_DEBUG("Element at index %u was deleted succesfully, new size %u", index, this->m_Size);
    }

    template <typename T>
    void CircularLinkedList<T>::DebugDetails()
    {
        LOG_DEBUG("This is a CircularLinkedList\nSize: %u\nBytes: %u", this->m_Size, this->m_Size * sizeof(Node<T>));
    }

    template<typename T>
    void CircularLinkedList<T>::Clear()
    {
        Node<T>* curNode = this->m_Head;
        Node<T>* nextNode;

        while (this->m_Size > 0) 
        {
            nextNode = curNode->next;
            delete curNode;
            curNode = nextNode;
            --this->m_Size;
        }

        this->m_Head = this->m_Tail = nullptr;

        LOG_DEBUG("CircularLinkedList has been cleared");
    }

    template <typename T>
    CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& list)
    {
        Clear();

        this->m_Size = list.m_Size;
    
        if(!list.m_Head)
        {
            this->m_Head = this->m_Tail = nullptr;
            return *this;
        }

        this->m_Head = new Node<T>(list.m_Head->data);

        Node<T>* head = this->m_Head;
        Node<T>* nextOther = list.m_Head->next;

        while (nextOther) 
        {
            head->next = new Node<T>(nextOther->data);
            head = head->next;
            nextOther = nextOther->next;
        }

        this->m_Tail = head;

        LOG_INFO("CircularLinkedList COPIED successfully");
        return *this;
    }

    template <typename T>
    CircularLinkedList<T>& CircularLinkedList<T>::operator=(CircularLinkedList<T>&& list)
    {
        Clear();

        this->m_Size = list.m_Size;
        this->m_Head = list.m_Head;
        this->m_Tail = list.m_Tail;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("CircularLinkedList MOVED successfully");
        return *this;
    }
}