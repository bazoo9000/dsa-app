#pragma once

#include <cstdint>
#include <cstdio>
#include <iostream>
#include "DataStructure.h"

namespace ds
{
	template <typename T>
	class DynamicArray : public DataStructure<T>
	{
	public:
		DynamicArray(uint32_t startSize = 1);
		DynamicArray(const T* arr);
		DynamicArray(const DynamicArray& arr);
		DynamicArray(DynamicArray&& arr);
		~DynamicArray();

	public:
		void Add(T elem);
		void Insert(T elem, uint32_t index);
		T& GetElementAt(uint32_t index);
		void DeleteAt(int index);
		void Print();

	public:
		T* GetData() { return m_Data; }
		uint32_t GetSize() { return this->m_Size; }
		uint32_t GetCapacity() { return m_Capacity; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		DynamicArray<T>& operator=(const T* arr) { return DynamicArray<T>(arr); }
		DynamicArray<T>& operator=(const DynamicArray& arr) { return DynamicArray<T>(arr); }
		DynamicArray<T>& operator=(DynamicArray&& arr) { return DynamicArray<T>(arr); }

	private:
		void resize(size_t newCap);

	private:
		T* m_Data; // the data itself
		uint32_t m_Capacity; // how many elements can an Array hold
	};

	template <typename T>
	DynamicArray<T>::DynamicArray(uint32_t startSize)
		: m_Capacity(startSize)
	{
		this->m_Size = 0;
		m_Data = new T[m_Capacity];

		LOG_DEBUG("DynamicArray CREATED succesfully!");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const T* arr)
	{
		uint32_t size = 0;

		while (arr[size]) 
		{
			++size;
		}

		m_Data = new T[size];

		for (uint32_t i = 0; i < size; ++i) 
		{
			m_Data[i] = arr[i];
		}

		this->m_Size = size;

		LOG_DEBUG("DynamicArray COPIED succesfully!");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray<T>& arr)
		: m_Capacity(arr.m_Capacity)
	{
		this->m_Size = arr.m_Size;
		m_Data = new T[m_Capacity];

		for (uint32_t i = 0; i < this->m_Size; ++i) 
		{
			m_Data[i] = arr.m_Data[i];
		}

		LOG_DEBUG("DynamicArray COPIED succesfully!");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(DynamicArray<T>&& arr)
		: m_Capacity(arr.m_Capacity), m_Data(arr.m_Data)
	{
		this->m_Size = arr.m_Size;
		arr.m_Data = nullptr;
		arr.m_Size = 0;
		arr.m_Capacity = 0;

		LOG_DEBUG("DynamicArray MOVED succesfully!");
	}

	template <typename T>
	DynamicArray<T>::~DynamicArray()
	{
		delete[] m_Data;
		m_Data = nullptr;
		m_Capacity = 0;
		this->m_Size = 0;

		LOG_DEBUG("DynamicArray DELETED succesfully!");
	}

	template <typename T>
	void DynamicArray<T>::Add(T elem)
	{
		if (this->m_Size == m_Capacity)
		{
			resize(m_Capacity * 2);
		}

		m_Data[this->m_Size++] = elem;
	}

	template <typename T>
	void DynamicArray<T>::Insert(T elem, uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't insert. Index is out of range!");
			exit(1);
		}

		if (this->m_Size == m_Capacity)
		{
			resize(m_Capacity * 2);
		}

		for (uint32_t i = this->m_Size; i > index; --i)
		{
			m_Data[i] = m_Data[i - 1];
		}

		m_Data[index] = elem;
		++this->m_Size;
	}

	template <typename T>
	T& DynamicArray<T>::GetElementAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			std::cout << "Can't get element. Index is out of range!";
			exit(1);
		}

		return m_Data[index];
	}

	template <typename T>
	void DynamicArray<T>::DeleteAt(int index)
	{
		if (index >= this->m_Size)
		{
			std::cout << "Can't delete. Index is out of range!\n";
			exit(1);
		}

		for (size_t i = index; i < this->m_Size - 1; ++i)
		{
			m_Data[i] = m_Data[i + 1];
		}

		--this->m_Size;
	}

	template <typename T>
	void DynamicArray<T>::Print()
	{
		using std::cout;
		for (uint32_t i = 0; i < this->m_Size; i++)
		{
			cout << m_Data[i] << " ";
		}
		cout << "\n";
	}

	template <typename T>
	void DynamicArray<T>::resize(size_t newCap)
	{
		T* newData = new T[newCap];
		for (uint32_t i = 0; i < this->m_Size; ++i) {
			newData[i] = m_Data[i];
		}

		delete[] m_Data;
		m_Data = newData;
		m_Capacity = newCap;
	}
}