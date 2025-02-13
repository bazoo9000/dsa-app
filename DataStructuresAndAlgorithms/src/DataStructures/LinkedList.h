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
		T GetElementAt(uint32_t index);
		void DeleteFirst();
		void Delete(T elem);
		void DeleteAt(uint32_t index);
		void Clear();
		virtual void Print() override;

	public:
		T GetFirst() { if(!this->m_Head) { LOG_FATAL("List is empty"); } return this->m_Head->data; }
		T GetLast() { if(!this->m_Tail) { LOG_FATAL("List is empty"); } return this->m_Tail->data; }

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
		Clear();

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
	}

	template <typename T>
	void LinkedList<T>::InsertAt(T elem, uint32_t index)
	{
		if (index > this->m_Size)
		{
			LOG_ERROR("Can't insert. Index out of range.");
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
	}

	template <typename T>
	void* LinkedList<T>::Find(T elem)
	{
		Node<T>* curNode = this->m_Head;
		while (curNode != nullptr)
		{
			if (curNode->data == elem)
			{
				return curNode;
			}

			curNode = curNode->next;
		}

		return nullptr;
	}

	template <typename T>
	T LinkedList<T>::GetElementAt(uint32_t index)
	{
		if(index >= this->m_Size)
		{
			LOG_FATAL("Can't get element. Index out of range.");
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

		return node->data;
	}

	template <typename T>
	void LinkedList<T>::DeleteFirst()
	{
		if (this->m_Head == nullptr)
		{
			LOG_ERROR("Can't delete. List is empty.");
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
	}

	template <typename T>
	void LinkedList<T>::Delete(T elem)
	{ 
		if (this->m_Head == nullptr)
		{
			LOG_ERROR("Can't delete. List is empty.");
			return;
		}

		Node<T>* delNode = (Node<T>*)Find(elem);

		if (!delNode)
		{
			LOG_ERROR("Can't delete. Element doesn't exist.");
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
			LOG_ERROR("Can't delete. Index out of range.");
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
	}

	template <typename T>
	void LinkedList<T>::Print()
	{
		LOG_DEBUG("This is a LinkedList");

		if(!m_Head)
		{
			LOG_DEBUG("LinkedList is empty");
		}

		Node<T>* aux = this->m_Head;
		while (aux != nullptr)
		{
			std::cout << aux->data << " ";
			aux = aux->next;
		}
		std::cout << "\n";
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