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
		virtual void Print() override;

	private:
		Node<T>* m_Head = nullptr;
		Node<T>* m_Tail = nullptr;
	};

	template <typename T>
	inline DoublyLinkedList<T>::DoublyLinkedList()
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