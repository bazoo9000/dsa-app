#pragma once

#include "DataStructure.h"

namespace ds
{
	template <typename T, uint32_t maxSize>
	class Array : public DataStructure<T>
	{
	public:
		Array();
		Array(const T* arr);
		Array(const Array& arr);
		Array(Array&& arr);
		~Array() { LOG_DEBUG("Array DELETED succesfully!"); }

	public:
		void Add(T elem);
		void Insert(T elem, uint32_t index);
		T& GetElementAt(uint32_t index);
		void DeleteAt(int index);
		virtual void Print() override;

	public:
		T* GetData() { return m_Data; }
		//uint32_t GetSize() { return this->m_Size; }
		uint32_t GetMaxSize() { return maxSize; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		Array<T, maxSize>& operator=(const T* arr)
		{
			uint32_t size = 0;

			while (arr[size]) 
			{
				if (size >= maxSize)
				{
					LOG_FATAL("Array given is larger!");
					exit(1);
				}
				m_Data[size] = arr[size];
				++size;
			}
			this->m_Size = size;

			return *this;
		}
		Array<T, maxSize>& operator=(const Array<T, maxSize>& arr)
		{
			this->m_Size = arr.m_Size;

			for (uint32_t i = 0; i < arr.m_Size; ++i)
			{
				m_Data[i] = arr.m_Data[i];
			}

			return *this;
		}
		Array<T, maxSize>& operator=(Array<T, maxSize>&& arr)
		{
			this->m_Size = arr.m_Size;

			for (uint32_t i = 0; i < arr.m_Size; ++i)
			{
				m_Data[i] = std::move(arr.m_Data[i]);
			}

			arr.m_Size = 0;
			
			return *this;
		}

	private:
		T m_Data[maxSize]; // the data itself
	};

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array()
	{
		this->m_Size = 0;
		LOG_DEBUG("Array CREATED succesfully.");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(const T* arr)
	{
		uint32_t size = 0;

		while (arr[size]) 
		{
			m_Data[size] = arr[size];
			++size;
		}

		if(size > maxSize)
		{
			LOG_FATAL("Array given is larger!");
			exit(1);
		}

		this->m_Size = size;
		LOG_DEBUG("Array COPIED succesfully.");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(const Array<T, maxSize>& arr)
	{
		this->m_Size = arr.m_Size;

		for (uint32_t i = 0; i < this->m_Size; ++i) 
		{
			m_Data[i] = arr.m_Data[i];
		}

		LOG_DEBUG("Array COPIED succesfully.");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(Array<T, maxSize>&& arr)
	{
		this->m_Size = arr.m_Size;

		for (uint32_t i = 0; i < arr.m_Size; ++i)
		{
			m_Data[i] = std::move(arr.m_Data[i]);
		}

		arr.m_Size = 0;

		LOG_DEBUG("Array MOVED succesfully.");
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Add(T elem)
	{
		if (this->m_Size == maxSize)
		{
			LOG_FATAL("Can't insert. Array is full!");
			exit(1);
		}

		m_Data[this->m_Size++] = elem;
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Insert(T elem, uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't insert. Index is out of range!");
			exit(1);
		}

		if (this->m_Size == maxSize)
		{
			LOG_FATAL("Can't insert. Array is full!");
			exit(1);
		}

		for (uint32_t i = this->m_Size; i > index; --i)
		{
			m_Data[i] = m_Data[i - 1];
		}

		m_Data[index] = elem;
		++this->m_Size;
	}

	template <typename T, uint32_t maxSize>
	T& Array<T, maxSize>::GetElementAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't get element. Index is out of range!");
			exit(1);
		}

		return m_Data[index];
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::DeleteAt(int index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't delete. Index is out of range!");
			exit(1);
		}

		for (uint32_t i = index; i < this->m_Size - 1; ++i)
		{
			m_Data[i] = m_Data[i + 1];
		}

		--this->m_Size;
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Print()
	{
		using std::cout;
		for (uint32_t i = 0; i < this->m_Size; i++)
		{
			cout << m_Data[i] << " ";
		}
		cout << "\n";
	}
}