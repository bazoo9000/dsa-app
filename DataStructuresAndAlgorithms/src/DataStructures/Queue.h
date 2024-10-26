#pragma once

#include <iostream>
#include "DataStructure.h"

namespace ds
{
	template <typename T>
	class Queue : DataStructure<T>
	{
	private:
		template <typename U>
		struct Node
		{
			U data;
			Node* next;
		};

	public:
		Queue();
		~Queue();

	public:
		void Enqueue(T elem);
		void Dequeue();
		bool IsEmpty();
		void Print();

	public:
		T GetFirst() { return m_Head->data; }
		uint32_t GetSize() { return m_Size; }

	private:
		Node<T>* m_Head;
		Node<T>* m_Tail;
		uint32_t m_Size;
	};

	template <typename T>
	Queue<T>::Queue()
		: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
	{
		// nimic
	}

	template <typename T>
	Queue<T>::~Queue()
	{
		while (!IsEmpty())
		{
			Dequeue();
		}
	}

	template <typename T>
	void Queue<T>::Enqueue(T elem)
	{
		Node<T>* newNode = new Node<T>();
		newNode->data = elem;
		newNode->next = nullptr;

		if (m_Head == nullptr) // if Queue is empty
		{
			m_Head = newNode;
			m_Tail = newNode;

			++m_Size;

			return;
		}

		m_Tail->next = newNode;
		m_Tail = newNode;

		++m_Size;
	}

	template <typename T>
	void Queue<T>::Dequeue()
	{
		if (IsEmpty()) 
		{
			std::cout << "Can't Pop. Queue is empty.\n";
			return;
		}

		Node<T>* curNode = m_Head;
		m_Head = m_Head->next;

		delete curNode;
		curNode = nullptr;

		if (m_Head == nullptr) // if after deletion the Queue is empty make tail point to NULL
		{
			m_Tail = nullptr;
		}

		--m_Size;
	}

	template <typename T>
	bool Queue<T>::IsEmpty()
	{
		return m_Size == 0;
	}

	template <typename T>
	void Queue<T>::Print()
	{
		Node<T>* curNode = m_Head;
		while (curNode != nullptr)
		{
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << "\n";
	}
}