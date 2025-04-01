#pragma once

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
		Queue(const Queue& q);
		Queue(Queue&& q);
		~Queue();

	public:
		void Enqueue(T elem);
		void Dequeue();
		bool IsEmpty();
		void Clear();
		virtual void Print() override;

	public:
		T GetFirst() { return m_Head->data; }

	public:
		Queue& operator=(const Queue& q);
		Queue& operator=(Queue&& q);

	private:
		Node<T>* m_Head;
		Node<T>* m_Tail;
	};

	template <typename T>
	Queue<T>::Queue()
		: m_Head(nullptr), m_Tail(nullptr)
	{
		LOG_INFO("Queue CREATED successfully");
	}

	template <typename T>
	Queue<T>::Queue(const Queue<T>& q)
	{
		Node<T>* head = q.m_Head;
		while(head)
		{
			Enqueue(head->data);
			head = head->next;
		}

		this->m_Size = q.m_Size;

		LOG_INFO("Queue COPIED successfully");
	}

	template <typename T>
	Queue<T>::Queue(Queue<T>&& q)
		: m_Head(q.m_Head), m_Tail(q.m_Tail)
	{
		this->m_Size = q.m_Size;

		q.m_Head = nullptr;
		q.m_Tail = nullptr;
		q.m_Size = 0;

		LOG_INFO("Queue MOVED successfully");
	}

	template <typename T>
	Queue<T>::~Queue()
	{
		Clear();

		LOG_INFO("Queue DESTROYED successfully");
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

			LOG_DEBUG("Enqueue successful, new size is %u", this->m_Size);
			return;
		}

		this->m_Tail->next = newNode;
		this->m_Tail = newNode;

		++this->m_Size;

		LOG_DEBUG("Enqueue successful, new size is %u", this->m_Size);
	}

	template <typename T>
	void Queue<T>::Dequeue()
	{
		if (IsEmpty()) 
		{
			LOG_ERROR("Can't dequeue, Queue is empty.");
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

		LOG_DEBUG("Dequeue successful, new size is %u", this->m_Size);
	}

	template <typename T>
	bool Queue<T>::IsEmpty()
	{
		return this->m_Size == 0;
	}

	template <typename T>
	void Queue<T>::Clear()
	{
		while (!IsEmpty())
		{
			Dequeue();
		}

		this->m_Size = 0;

		LOG_DEBUG("Queue has been cleared");
	}

	template <typename T>
	void Queue<T>::Print()
	{
		LOG_DEBUG("This is a Queue");

		if(IsEmpty())
		{
			LOG_DEBUG("Queue is empty");
		}

		Node<T>* curNode = this->m_Head;
		while (curNode != nullptr)
		{
			std::cout << curNode->data << " ";
			curNode = curNode->next;
		}
		std::cout << "\n";
	}

	template <typename T>
	Queue<T>& Queue<T>::operator=(const Queue<T>& q)
	{
		Clear();

		Node<T>* head = q.m_Head;
		while(head)
		{
			Enqueue(head->data);
			head = head->next;
		}

		this->m_Size = q.m_Size;

		LOG_INFO("Queue COPIED successfully");
		return *this;
	}

	template <typename T>
	Queue<T>& Queue<T>::operator=(Queue<T>&& q)
	{
		Clear();

		this->m_Size = q.m_Size;
		this->m_Head = q.m_Head;
		this->m_Tail = q.m_Tail;

		q.m_Size = 0;
		q.m_Head = nullptr;
		q.m_Tail = nullptr;

		LOG_INFO("Queue MOVED successfully");
		return *this;
	}
}