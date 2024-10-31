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

			Node(U data, Node* next = nullptr)
			{
				this->data = data;
				this->next = next;
			}
		};

	public:
		Stack();
		~Stack();

	public:
		void Push(T elem);
		void Pop();
		bool IsEmpty();
		virtual void Print() override;

	public:
		T GetTop() { return this->m_Head->data; }

	private:
		Node<T>* m_Head = nullptr;
	};

	template <typename T>
	Stack<T>::Stack()
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
		Node<T>* newNode = new Node<T>(elem, this->m_Head);

		this->m_Head = newNode;

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

		Node<T>* curNode = this->m_Head;
		this->m_Head = this->m_Head->next;

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
		Node<T>* curNode = this->m_Head;
		while(curNode != nullptr)
		{
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << "\n";
	}
}