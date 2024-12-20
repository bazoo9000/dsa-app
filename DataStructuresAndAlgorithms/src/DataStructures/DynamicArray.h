#pragma once

#include "DataStructure.h"

namespace ds
{
	template <typename T>
	class DynamicArray : public DataStructure<T>
	{
	public:
		DynamicArray(uint32_t startSize = 1);
		DynamicArray(const DynamicArray& arr);
		DynamicArray(DynamicArray&& arr);
		~DynamicArray();

	public:
		void Add(T elem);
		void Insert(T elem, uint32_t index);
		T& GetElementAt(uint32_t index);
		void DeleteAt(int index);
		void Clear();
		virtual void Print() override;

	public:
		T* GetData() { return this->m_Data; }
		uint32_t GetSize() { return this->m_Size; }
		uint32_t GetCapacity() { return this->m_Capacity; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		DynamicArray& operator=(const DynamicArray& arr);
		DynamicArray& operator=(DynamicArray&& arr);

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
		if(this->m_Capacity == 0)
		{
			LOG_ERROR("Max capacity of DynamicArray is 0! Setting it back to 1");
			this->m_Capacity = 1;
		}

		this->m_Size = 0;
		this->m_Data = new T[this->m_Capacity];

		LOG_INFO("DynamicArray CREATED succesfully");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray<T>& arr)
	{
		Clear();

		this->m_Size = arr.m_Size;
		this->m_Capacity = arr.m_Capacity;
		this->m_Data = new T[this->m_Capacity];

		for (uint32_t i = 0; i < this->m_Size; ++i) 
		{
			this->m_Data[i] = arr.m_Data[i];
		}

		LOG_INFO("DynamicArray COPIED succesfully!");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(DynamicArray<T>&& arr)
		: m_Capacity(arr.m_Capacity), m_Data(arr.m_Data)
	{
		this->m_Size = arr.m_Size;
		arr.m_Data = nullptr;
		arr.m_Size = 0;
		arr.m_Capacity = 0;

		LOG_INFO("DynamicArray MOVED succesfully");
	}

	template <typename T>
	DynamicArray<T>::~DynamicArray()
	{
		Clear();
		LOG_INFO("DynamicArray DELETED succesfully");
	}

	template <typename T>
	void DynamicArray<T>::Add(T elem)
	{
		if (this->m_Size == this->m_Capacity)
		{
			resize(this->m_Capacity * 2);
		}

		this->m_Data[this->m_Size++] = elem;

		LOG_INFO("Adding succesful");
	}

	template <typename T>
	void DynamicArray<T>::Insert(T elem, uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_ERROR("Can't insert, index is out of range");
			return;
		}

		if (this->m_Size == this->m_Capacity)
		{
			resize(this->m_Capacity * 2);
		}

		for (uint32_t i = this->m_Size; i > index; --i)
		{
			this->m_Data[i] = this->m_Data[i - 1];
		}

		this->m_Data[index] = elem;
		++this->m_Size;

		LOG_INFO("Inserting succesful");
	}

	template <typename T>
	T& DynamicArray<T>::GetElementAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't get element, index is out of range");
			exit(1);
		}

		LOG_INFO("Got element succesfully");

		return this->m_Data[index];
	}

	template <typename T>
	void DynamicArray<T>::DeleteAt(int index)
	{
		if (index >= this->m_Size)
		{
			LOG_ERROR("Can't delete, index is out of range");
			return;
		}

		for (size_t i = index; i < this->m_Size - 1; ++i)
		{
			this->m_Data[i] = this->m_Data[i + 1];
		}

		--this->m_Size;
		LOG_INFO("Element deleted succesfully");
	}

	template <typename T>
	void DynamicArray<T>::Clear()
	{
		if(this->m_Data == nullptr)
		{
			LOG_DEBUG("m_Data is nullptr");
			return;
		}

		delete[] this->m_Data;
		this->m_Data = nullptr;
		this->m_Capacity = 0;
		this->m_Size = 0;
	}

	template <typename T>
	void DynamicArray<T>::Print()
	{
		LOG_DEBUG("This is an DynamicArray");

		if(this->m_Size == 0)
		{
			LOG_DEBUG("DynamicArray is empty");
		}

		for (uint32_t i = 0; i < this->m_Size; i++)
		{
			std::cout << this->m_Data[i] << " ";
		}
		std::cout << "\n";
	}

	template <typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(const DynamicArray<T>& arr) 
	{
		Clear();

		this->m_Size = arr.m_Size;
		this->m_Capacity = arr.m_Capacity;
		this->m_Data = new T[this->m_Capacity];

		for (uint32_t i = 0; i < arr.m_Size; ++i)
		{
			this->m_Data[i] = arr.m_Data[i];
		}

		LOG_INFO("DynamicArray COPIED succesfully");
		return *this;
	}
	
	template <typename T>
	DynamicArray<T>& DynamicArray<T>::operator=(DynamicArray<T>&& arr) 
	{
		this->m_Data = arr.m_Data;
		this->m_Size = arr.m_Size;
		this->m_Capacity = arr.m_Capacity;

		arr.m_Data = nullptr;
		arr.m_Size = 0;
		arr.m_Capacity = 0;

		LOG_INFO("DynamicArray MOVED succesfully");
		return *this;
	}

	template <typename T>
	void DynamicArray<T>::resize(size_t newCap)
	{
		T* newData = new T[newCap];
		for (uint32_t i = 0; i < this->m_Size; ++i) {
			newData[i] = this->m_Data[i];
		}

		delete[] this->m_Data;
		this->m_Data = newData;
		this->m_Capacity = newCap;

		LOG_DEBUG("DynamicArray has been resized");
	}
}