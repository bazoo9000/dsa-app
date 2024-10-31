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

			Node(U data, Node* next = nullptr)
			{
				this->data = data;
				this->next = next;
			}
		};

	public:
		Queue();
		~Queue();

	public:
		void Enqueue(T elem);
		void Dequeue();
		bool IsEmpty();
		virtual void Print() override;

	public:
		T GetFirst() { return m_Head->data; }

	private:
		Node<T>* m_Head = nullptr;
		Node<T>* m_Tail = nullptr;
	};

	template <typename T>
	Queue<T>::Queue()
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
		Node<T>* newNode = new Node<T>(elem);

		if (this->m_Head == nullptr) // if Queue is empty
		{
			this->m_Head = newNode;
			this->m_Tail = newNode;

			++this->m_Size;

			return;
		}

		this->m_Tail->next = newNode;
		this->m_Tail = newNode;

		++this->m_Size;
	}

	template <typename T>
	void Queue<T>::Dequeue()
	{
		if (IsEmpty()) 
		{
			std::cout << "Can't Pop. Queue is empty.\n";
			return;
		}

		Node<T>* curNode = this->m_Head;
		this->m_Head = this->m_Head->next;

		delete curNode;
		curNode = nullptr;

		if (this->m_Head == nullptr) // if after deletion the Queue is empty make tail point to NULL
		{
			this->m_Tail = nullptr;
		}

		--this->m_Size;
	}

	template <typename T>
	bool Queue<T>::IsEmpty()
	{
		return this->m_Size == 0;
	}

	template <typename T>
	void Queue<T>::Print()
	{
		Node<T>* curNode = this->m_Head;
		while (curNode != nullptr)
		{
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << "\n";
	}
}