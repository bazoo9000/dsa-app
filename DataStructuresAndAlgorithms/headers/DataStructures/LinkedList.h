#pragma once

#include "DataStructure.h"

namespace ds
{
    template <typename T>
    class LinkedList : public DataStructure<T>
    {
    private:
        template <typename U>
        struct Node
        {
            U data;
            Node* next = nullptr;

            Node(U data, Node* next = nullptr)
            {
                this->data = data;
                this->next = next;
            }
        };

    public:
        LinkedList();
        LinkedList(const LinkedList<T>& list);
        LinkedList(LinkedList<T>&& list);
        ~LinkedList();

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
        LinkedList& operator=(const LinkedList& list);
        LinkedList& operator=(LinkedList&& list);

    private:
        Node<T>* m_Head;
        Node<T>* m_Tail;
    };

    template <typename T>
    LinkedList<T>::LinkedList()
        : m_Head(nullptr), m_Tail(nullptr)
    {
        LOG_INFO("LinkedList CREATED succesfully");
    }

    template <typename T>
    LinkedList<T>::LinkedList(const LinkedList<T>& list)
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

        LOG_INFO("LinkedList COPIED succesfully");
    }

    template <typename T>
    LinkedList<T>::LinkedList(LinkedList<T>&& list)
        : m_Head(list.m_Head), m_Tail(list.m_Tail)
    {
        this->m_Size = list.m_Size;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("LinkedList MOVED succesfully");
    }

    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        Clear();
        LOG_INFO("LinkedList DESTROYED successfully");
    }

    template <typename T>
    void LinkedList<T>::Append(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);

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
    void LinkedList<T>::Prepend(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);

        if (this->m_Tail == nullptr)
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
    void LinkedList<T>::InsertAt(T elem, uint32_t index)
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
    void* LinkedList<T>::Find(T elem)
    {
        Node<T>* curNode = this->m_Head;
        while (curNode != nullptr)
        {
            if (curNode->data == elem)
            {
                LOG_DEBUG("Element found");
                return curNode;
            }

            curNode = curNode->next;
        }

        LOG_DEBUG("Element NOT found");
        return nullptr;
    }


    template <typename T>
    T LinkedList<T>::GetFirst()
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
    T LinkedList<T>::GetLast()
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
    T LinkedList<T>::GetElementAt(uint32_t index)
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
    void LinkedList<T>::DeleteFirst()
    {
        if (this->m_Head == nullptr)
        {
            LOG_ERROR("Can't delete, list is empty.");
            return;
        }

        Node<T>* delNode = this->m_Head;
        this->m_Head = this->m_Head->next;

        delete delNode;

        if (this->m_Head == nullptr) // in case i delete the only element in the list
        {
            this->m_Tail = nullptr;
        }

        --this->m_Size;

        LOG_DEBUG("First element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    void LinkedList<T>::Delete(T elem)
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
    void LinkedList<T>::DeleteAt(uint32_t index)
    {
        if (this->m_Size == 0)
        {
            LOG_ERROR("Can't delete. List is empty.");
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
    void LinkedList<T>::DebugDetails()
    {
        std::ostringstream oss;

        oss << "[ ";

        Node<T>* curNode = this->m_Head;
        for (uint32_t i = 0; i < std::min<uint32_t>(this->m_Size, MAX_OUTPUT_SIZE); i++)
        {
            oss << "(";
            if constexpr (IS_STREAMABLE(T)) { oss << curNode->data; }
            else                            { oss << typeid(curNode->data).name(); }
            
            if (curNode->next) { oss << ", " << curNode->next; }
            else               { oss << ", NULL"; }
            oss << ") -> ";

            curNode = curNode->next;
        }

        oss << "]";

        LOG_DEBUG("This is a LinkedList\nSize: %u\nBytes: %u\nData: %s\n",
            this->m_Size,
            this->m_Size * sizeof(Node<T>),
            oss.str().c_str()
        );
    }

    template<typename T>
    void LinkedList<T>::Clear()
    {
        Node<T>* curNode = this->m_Head;
        Node<T>* nextNode;

        while (curNode != nullptr) 
        {
            nextNode = curNode->next;
            delete curNode;
            curNode = nextNode;
        }

        this->m_Head = this->m_Tail = nullptr;
        this->m_Size = 0;

        LOG_DEBUG("LinkedList has been cleared");
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list)
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

        LOG_INFO("LinkedList COPIED succesfully");
        return *this;
    }

    template <typename T>
    LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& list)
    {
        Clear();

        this->m_Size = list.m_Size;
        this->m_Head = list.m_Head;
        this->m_Tail = list.m_Tail;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("LinkedList MOVED succesfully");
        return *this;
    }
}