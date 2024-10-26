#pragma once

#include <iostream>
#include "DataStructure.h"

namespace ds 
{
	template <typename T>
	class Stack : DataStructure<T>
	{
	private:
		template <typename U>
		struct Node 
		{
			U data;
			Node* next;
		};

	public:
		Stack();
		~Stack();

	public:
		void Push(T elem);
		void Pop();
		bool IsEmpty();
		void Print();

	public:
		T GetTop() { return m_Head->data; }
		uint32_t GetSize() { return this->m_Size; }

	private:
		Node<T>* m_Head;
	};

	template <typename T>
	Stack<T>::Stack()
		: m_Head(nullptr)
	{
		// nimic
	}

	template <typename T>
	Stack<T>::~Stack()
	{
		while (!IsEmpty())
		{
			Pop();
		}
	}

	template <typename T>
	void Stack<T>::Push(T elem)
	{
		Node<T>* newNode = new Node<T>;
		newNode->data = elem;
		newNode->next = m_Head;

		m_Head = newNode;

		++this->m_Size;
	}

	template <typename T>
	void Stack<T>::Pop()
	{
		if (IsEmpty())
		{
			LOG_ERROR("Can't Pop. Stack is empty.");
			return;
		}

		Node<T>* curNode = m_Head;
		m_Head = m_Head->next;

		delete curNode;
		curNode = nullptr;

		--this->m_Size;
	}

	template <typename T>
	bool Stack<T>::IsEmpty()
	{
		return this->m_Size == 0;
	}

	template <typename T>
	void Stack<T>::Print() 
	{
		Node<T>* curNode = m_Head;
		while(curNode != nullptr)
		{
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << "\n";
	}
}