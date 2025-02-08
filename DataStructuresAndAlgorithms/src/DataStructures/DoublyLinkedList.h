#pragma once

#include <iostream>
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
		T GetElementAt(uint32_t index);
		void Delete(T elem);
		void DeleteAt(uint32_t index);
		void Clear();
		virtual void Print() override;

	public:
		T GetFirst() { if(!this->m_Head) { LOG_FATAL("List is empty"); } return this->m_Head->data; }
		T GetLast() { if(!this->m_Tail) { LOG_FATAL("List is empty"); } return this->m_Tail->data; }

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
	}

	template <typename T>
	void DoublyLinkedList<T>::InsertAt(T elem, uint32_t index)
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
	}

	template <typename T>
	void* DoublyLinkedList<T>::Find(T elem)
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
	T DoublyLinkedList<T>::GetElementAt(uint32_t index)
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

		return node->data;
	}

	template <typename T>
	void DoublyLinkedList<T>::Delete(T elem)
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

			return;
		}

		if (this->m_Tail == delNode)
		{
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

			return;
		}

		delNode->prev->next = delNode->next;
		delNode->next->prev = delNode->prev;

		delete delNode;

		--this->m_Size;
	}

	template <typename T>
	void DoublyLinkedList<T>::DeleteAt(uint32_t index)
	{
		Delete(GetElementAt(index));
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
	}

	template <typename T>
	void DoublyLinkedList<T>::Print()
	{
		LOG_DEBUG("This is a DoublyLinkedList");

		if(!m_Head)
		{
			LOG_DEBUG("DoublyLinkedList is empty");
		}

		Node<T>* aux = this->m_Head;
		while (aux != nullptr)
		{
			std::cout << aux->data << " ";
			aux = aux->next;
		}
		std::cout << "\n";
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