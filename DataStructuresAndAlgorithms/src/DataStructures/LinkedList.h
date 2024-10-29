#pragma once

#include <iostream>
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
		};

	public:
		LinkedList();
		~LinkedList();

	public:
		void Append(T elem);
		void Prepend(T elem);
		void InsertAt(T elem, uint32_t index);
		bool Find(T elem);
		void Delete(T elem);
		void DeleteAt(uint32_t index);
		void Print();

	public:
		// TO BE IMPLEMENTED!!!!
		// T GetElement(const T& elem);
		// T GetElementAt(uint32_t index);
		// T GetFirst();
		// T GetLast();
		// TO BE IMPLEMENTED

	private:
		Node<T>* m_Head = nullptr;
		Node<T>* m_Tail = nullptr;
	};

	template <typename T>
	LinkedList<T>::LinkedList()
	{
		// nimic
	}

	template <typename T>
	LinkedList<T>::~LinkedList()
	{
		Node<T>* curNode = m_Head;
		Node<T>* nextNode;

		while (curNode != nullptr) 
		{
			nextNode = curNode->next;
			delete curNode;
			curNode = nextNode;
		}
	}

	template <typename T>
	void LinkedList<T>::Append(T elem)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = elem;

		if (m_Tail == nullptr) 
		{
			m_Head = m_Tail = newNode; // in case there was no element in the list
		}
		else 
		{
			m_Tail->next = newNode;
			m_Tail = newNode;
		}

		++this->m_Size;
	}

	template <typename T>
	void LinkedList<T>::Prepend(T elem)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = elem;

		if (m_Tail == nullptr)
		{
			m_Head = m_Tail = newNode; // in case there was no element in the list
		}
		else
		{
			newNode->next = m_Head;
			m_Head = newNode;
		}

		++this->m_Size;
	}

	template <typename T>
	void LinkedList<T>::InsertAt(T elem, uint32_t index)
	{
		if (index >= this->m_Size)
		{
			std::cout << "Can't insert. Index out of range.\n";
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

		Node<T>* prevNode = m_Head;

		for (uint32_t i = 0; i < index - 1 && prevNode != nullptr; ++i)
		{
			prevNode = prevNode->next;
		}
		
		Node<T>* newNode = new Node<T>;
		newNode->data = elem;

		newNode->next = prevNode->next;
		prevNode->next = newNode;

		++this->m_Size;
	}

	template <typename T>
	bool LinkedList<T>::Find(T elem)
	{
		Node<T>* curNode = m_Head;
		while (curNode != nullptr)
		{
			if (curNode->data == elem)
			{
				return true;
			}

			curNode = curNode->next;
		}

		return false;
	}

	template <typename T>
	void LinkedList<T>::Delete(T elem)
	{ 
		if (m_Head == nullptr)
		{
			std::cout << "Can't delete. List is empty.\n";
			return;
		}

		if (!Find(elem))
		{
			std::cout << "Can't delete. Element doesn't exist.\n";
			return;
		}

		if (m_Head->data == elem)
		{
			Node<T>* tempNode = m_Head;
			m_Head = m_Head->next;

			delete tempNode;
			tempNode = nullptr;

			if (m_Head == nullptr) // in case i delete the only element in the list
			{
				m_Tail = nullptr;
			}

			--this->m_Size;

			return;
		}

		Node<T>* curNode = m_Head;
		while (curNode->next != nullptr && curNode->next->data != elem) 
		{
			curNode = curNode->next;
		}

		if (curNode->next != nullptr) {
			Node<T>* tempNode = curNode->next;
			curNode->next = curNode->next->next;

			if (tempNode == m_Tail)
			{
				m_Tail = curNode;
			}

			delete tempNode;
			tempNode = nullptr;

			--this->m_Size;
		}
	}

	template <typename T>
	void LinkedList<T>::DeleteAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			std::cout << "Can't delete. Index out of range.\n";
			return;
		}

		if (index == 0)
		{
			Node<T>* tempNode = m_Head;
			m_Head = m_Head->next;

			delete tempNode;
			tempNode = nullptr;

			if (m_Head == nullptr) // in case i delete the only element in the list
			{
				m_Tail = nullptr;
			}

			--this->m_Size;

			return;
		}

		Node<T>* curNode = m_Head;
		for(uint32_t i = 0; i < index - 1; ++i)
		{
			curNode = curNode->next;
		}

		Node<T>* tempNode = curNode->next;
		curNode->next = curNode->next->next;

		if (tempNode == m_Tail)
		{
			m_Tail = curNode;
		}

		delete tempNode;
		tempNode = nullptr;

		--this->m_Size;
	}

	template <typename T>
	void LinkedList<T>::Print()
	{
		Node<T>* aux = m_Head;
		while (aux != nullptr)
		{
			std::cout << aux->data << " ";
			aux = aux->next;
		}
		std::cout << "\n";
	}
}