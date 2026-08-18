#pragma once

#include "DataStructure.h"

namespace ds
{
    template <typename T>
    class DoublyLinkedList : public DataStructure<T>
    {
    private:
        template <typename U>
        struct Node
        {
            U data;
            Node* next = nullptr;
            Node* prev = nullptr;

            Node(U data, Node* next = nullptr, Node* prev = nullptr)
            {
                this->data = data;
                this->next = next;
                this->prev = prev;
            }
        };

    public:
        DoublyLinkedList();
        DoublyLinkedList(const DoublyLinkedList& list);
        DoublyLinkedList(DoublyLinkedList&& list);
        ~DoublyLinkedList();

    public:
        void Append(T elem);
        void Prepend(T elem);
        void InsertAt(T elem, uint32_t index);
        void* Find(T elem);
        T GetFirst();
        T GetLast();
        T GetElementAt(uint32_t index);
        void DeleteFirst();
        void DeleteLast();
        void Delete(T elem);
        void DeleteAt(uint32_t index);
        void Clear();
        virtual void DebugDetails() override;

    public:
        T& operator[](uint32_t index) { return GetElementAt(index); }
        DoublyLinkedList& operator=(const DoublyLinkedList& list);
        DoublyLinkedList& operator=(DoublyLinkedList&& list);

    private:
        Node<T>* m_Head = nullptr;
        Node<T>* m_Tail = nullptr;
    };

    template <typename T>
    DoublyLinkedList<T>::DoublyLinkedList()
        : m_Head(nullptr), m_Tail(nullptr)
    {
        LOG_INFO("DoublyLinkedList CREATED succesfully");
    }

    template <typename T>
    DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& list)
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
        Node<T>* prevOther;

        while (nextOther)
        {
            prevOther = head;
            head->next = new Node<T>(nextOther->data, nullptr, prevOther);
            head = head->next;
            nextOther = nextOther->next;
        }

        this->m_Tail = head;

        LOG_INFO("DoublyLinkedList COPIED succesfully");
    }

    template <typename T>
    DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& list)
        : m_Head(list.m_Head), m_Tail(list.m_Tail)
    {
        this->m_Size = list.m_Size;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("DoublyLinkedList MOVED succesfully");
    }

    template <typename T>
    DoublyLinkedList<T>::~DoublyLinkedList()
    {
        Clear();
        LOG_INFO("DoublyLinkedList DESTROYED successfully");
    }

    template <typename T>
    void DoublyLinkedList<T>::Append(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);

        if(this->m_Tail == nullptr)
        {
            this->m_Head = this->m_Tail = newNode; // in case there was no element in the list
        }
        else
        {
            this->m_Tail->next = newNode;
            newNode->prev = this->m_Tail;
            this->m_Tail = newNode;
        }

        ++this->m_Size;

        LOG_DEBUG("Append successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void DoublyLinkedList<T>::Prepend(T elem)
    {
        Node<T>* newNode = new Node<T>(elem);

        if (this->m_Tail == nullptr)
        {
            this->m_Head = this->m_Tail = newNode; // in case there was no element in the list
        }
        else
        {
            newNode->next = this->m_Head;
            this->m_Head->prev = newNode;
            this->m_Head = newNode;
        }

        ++this->m_Size;
    
        LOG_DEBUG("Prepend successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void DoublyLinkedList<T>::InsertAt(T elem, uint32_t index)
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

        Node<T>* newNode = new Node<T>(elem);
        Node<T>* prevNode;
        
        if(index < this->m_Size / 2)
        {
            prevNode = this->m_Head;

            for (uint32_t i = 0; i < index - 1 && prevNode != nullptr; ++i)
            {
                prevNode = prevNode->next;
            }
        }
        else
        {
            prevNode = this->m_Tail;

            for (uint32_t i = this->m_Size; i > index && prevNode != nullptr; --i)
            {
                prevNode = prevNode->prev;
            }
        }

        newNode->next = prevNode->next;
        prevNode->next->prev = newNode;
        newNode->prev = prevNode;
        prevNode->next = newNode;

        ++this->m_Size;

        LOG_DEBUG("Inserting at index %u succesful, new size is %u", index, this->m_Size);
    }

    template <typename T>
    void* DoublyLinkedList<T>::Find(T elem)
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
    T DoublyLinkedList<T>::GetFirst()
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
    T DoublyLinkedList<T>::GetLast()
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
    T DoublyLinkedList<T>::GetElementAt(uint32_t index)
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

        Node<T>* node;

        if(index < this->m_Size / 2)
        {
            node = m_Head;
            for(int i = 0; i < index; i++)
            {
                node = node->next;
            }
        }
        else
        {
            node = m_Tail;
            for(int i = this->m_Size - 1; i > index; i--)
            {
                node = node->prev;
            }
        }

        LOG_DEBUG("Got element at index %u succesfully", index);
        return node->data;
    }

    template <typename T>
    void DoublyLinkedList<T>::DeleteFirst()
    {
        Node<T>* delNode = this->m_Head;
        this->m_Head = this->m_Head->next;

        delete delNode;

        if (this->m_Head == nullptr)
        {
            this->m_Tail = nullptr;
        }
        else
        {
            this->m_Head->prev = nullptr;
        }

        --this->m_Size;

        LOG_DEBUG("First element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    void DoublyLinkedList<T>::DeleteLast()
    {
        Node<T>* delNode = this->m_Tail;
        this->m_Tail = this->m_Tail->prev;

        delete delNode;

        if (this->m_Tail == nullptr)
        {
            this->m_Head = nullptr;
        }
        else
        {
            this->m_Tail->next = nullptr;
        }

        --this->m_Size;

        LOG_DEBUG("Last element deleted successfully, new size is %u", this->m_Size);
    }

    template <typename T>
    void DoublyLinkedList<T>::Delete(T elem)
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

        if (this->m_Tail == delNode)
        {
            DeleteLast();
            return;
        }

        delNode->prev->next = delNode->next;
        delNode->next->prev = delNode->prev;

        delete delNode;

        --this->m_Size;

        LOG_DEBUG("Delete successful, new size is %u", this->m_Size);
    }

    template <typename T>
    void DoublyLinkedList<T>::DeleteAt(uint32_t index)
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

        if(index == this->m_Size - 1)
        {
            DeleteLast();
            return;
        }

        Node<T>* delNode = this->m_Head->next;
        for(uint32_t i = 1; i < index; i++)
        {
            delNode = delNode->next;
        }

        delNode->prev->next = delNode->next;
        delNode->next->prev = delNode->prev;

        delete delNode;

        --this->m_Size;

        LOG_DEBUG("Element at index %u was deleted succesfully, new size %u", index, this->m_Size);
    }

    template<typename T>
    void DoublyLinkedList<T>::Clear()
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

        LOG_DEBUG("DoublyLinkedList has been cleared");
    }

    template <typename T>
    void DoublyLinkedList<T>::DebugDetails()
    {
        std::ostringstream oss;

        oss << "[ ";

        Node<T>* curNode = this->m_Head;
        for (uint32_t i = 0; i < std::min<uint32_t>(this->m_Size, MAX_OUTPUT_SIZE); i++)
        {
            oss << "(";
            if (curNode->prev) { oss << curNode->prev << ", "; }
            else               { oss << "NULL, "; }

            if constexpr (IS_STREAMABLE(T)) { oss << curNode->data; }
            else                            { oss << typeid(curNode->data).name(); }
            
            if (curNode->next) { oss << ", " << curNode->next; }
            else 			   { oss << ", NULL"; }
            oss << ") <-> ";

            curNode = curNode->next;
        }

        oss << "]";

        LOG_DEBUG("This is a DoublyLinkedList\nSize: %u\nBytes: %u\nData: %s\n",
            this->m_Size,
            this->m_Size * sizeof(Node<T>),
            oss.str().c_str()
        );
    }

    template <typename T>
    DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& list)
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
        Node<T>* prevOther;

        while (nextOther)
        {
            prevOther = head;
            head->next = new Node<T>(nextOther->data, nullptr, prevOther);
            head = head->next;
            nextOther = nextOther->next;
        }

        this->m_Tail = head;

        LOG_INFO("DoublyLinkedList COPIED succesfully");
        return *this;
    }

    template <typename T>
    DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList&& list)
    {
        Clear();

        this->m_Size = list.m_Size;
        this->m_Head = list.m_Head;
        this->m_Tail = list.m_Tail;

        list.m_Size = 0;
        list.m_Head = nullptr;
        list.m_Tail = nullptr;

        LOG_INFO("DoublyLinkedList MOVED succesfully");
        return *this;
    }
}