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
		};

	public:
		DoublyLinkedList();
		~DoublyLinkedList();

	public:
		void Append(T elem);
		void Prepend(T elem);
		void InsertAt(T elem, uint32_t index);
		bool Find(T elem);
		void Delete(T elem);
		void DeleteAt(uint32_t index);
		void Print();

	private:
		Node<T>* m_Head;
		Node<T>* m_Tail;
		uint32_t m_Size;
	};

	template <typename T>
	inline DoublyLinkedList<T>::DoublyLinkedList()
		: m_Head(nullptr), m_Tail(nullptr), m_Size(0)
	{
		// nimic
	}

	template <typename T>
	inline DoublyLinkedList<T>::~DoublyLinkedList()
	{
		// nimic
	}

	template <typename T>
	inline void DoublyLinkedList<T>::Append(T elem)
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
			newNode->prev = m_Tail->prev;
		}

		++m_Size;
	}

	template <typename T>
	inline void DoublyLinkedList<T>::Prepend(T elem)
	{
	}

	template <typename T>
	inline void DoublyLinkedList<T>::InsertAt(T elem, uint32_t index)
	{
	}

	template <typename T>
	inline bool DoublyLinkedList<T>::Find(T elem)
	{
		return false;
	}

	template <typename T>
	inline void DoublyLinkedList<T>::Delete(T elem)
	{
	}

	template <typename T>
	inline void DoublyLinkedList<T>::DeleteAt(uint32_t index)
	{
	}

	template <typename T>
	inline void DoublyLinkedList<T>::Print()
	{
	}	
}