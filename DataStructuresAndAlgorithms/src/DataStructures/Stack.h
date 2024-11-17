#pragma once

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
		Stack(const Stack& s);
		Stack(Stack&& s);
		~Stack();

	public:
		void Push(T elem);
		void Pop();
		bool IsEmpty();
		void Clear();
		virtual void Print() override;

	public:
		T GetTop() { return this->m_Head->data; }

	public:
		Stack& operator=(const Stack& q);
		Stack& operator=(Stack&& q);

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
	Stack<T>::Stack(const Stack& s)
	{
		Clear();

		Node<T>* head = s.m_Head;
		Stack<T> stack;
		while(head)
		{
			stack.Push(head->data);
			head = head->next;
		}
		
		while(!stack.IsEmpty())
		{
			Push(stack.GetTop());
			stack.Pop();
		}

		this->m_Size = s.m_Size;
	}

	template <typename T>
	Stack<T>::Stack(Stack&& s)
		: m_Head(s.m_Head)
	{
		this->m_Size = s.m_Size;

		s.m_Head = nullptr;
		s.m_Size = 0;
	}

	template <typename T>
	Stack<T>::~Stack()
	{
		Clear();
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

	template <typename T>
	void Stack<T>::Clear()
	{
		while (!IsEmpty())
		{
			Pop();
		}

		this->m_Size = 0;
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(const Stack<T>& s)
	{
		Clear();

		Node<T>* head = s.m_Head;
		Stack<T> stack;
		while(head)
		{
			stack.Push(head->data);
			head = head->next;
		}
		
		while(!stack.IsEmpty())
		{
			Push(stack.GetTop());
			stack.Pop();
		}

		this->m_Size = s.m_Size;
		
		return *this;
	}

	template <typename T>
	Stack<T>& Stack<T>::operator=(Stack<T>&& s)
	{
		Clear();

		this->m_Size = s.m_Size;
		this->m_Head = s.m_Head;

		s.m_Size = 0;
		s.m_Head = nullptr;

		return *this;
	}
}