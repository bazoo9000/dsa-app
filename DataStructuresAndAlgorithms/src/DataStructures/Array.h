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
		~Array();

	public:
		void Add(T elem);
		void Insert(T elem, uint32_t index);
		T& GetElementAt(uint32_t index);
		void DeleteAt(int index);
		virtual void Print() override;

	public:
		T* GetData() { return this->m_Data; }
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
					LOG_WARN("Given array is larger than this Array");
					break;
				}

				this->m_Data[size] = arr[size];
				size++;
			}

			this->m_Size = size;

			LOG_INFO("Array COPIED succesfully");
			return *this;
		}
		Array<T, maxSize>& operator=(const Array<T, maxSize>& arr)
		{
			this->m_Size = arr.m_Size;

			for (uint32_t i = 0; i < this->m_Size; ++i)
			{
				this->m_Data[i] = arr.m_Data[i];
			}

			LOG_INFO("Array COPIED succesfully");
			return *this;
		}
		Array<T, maxSize>& operator=(Array<T, maxSize>&& arr)
		{
			this->m_Size = arr.m_Size;

			for (uint32_t i = 0; i < this->m_Size; ++i)
			{
				m_Data[i] = std::move(arr.m_Data[i]);
			}

			arr.m_Size = 0;
			
			LOG_INFO("Array MOVED succesfully");
			return *this;
		}

	private:
		T m_Data[maxSize]; // the data itself
	};

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array()
	{
		LOG_INFO("Array CREATED succesfully");

		if(maxSize == 0)
		{
			LOG_WARN("The size of the created Array is 0");
		}
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(const T* arr)
	{
		uint32_t size = 0;

		while (arr[size]) 
		{
			if(size > maxSize)
			{
				LOG_WARN("Given array is larger than this Array");
				break;
			}

			this->m_Data[size] = arr[size];
			++size;
		}

		this->m_Size = size;
		LOG_INFO("Array COPIED succesfully");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(const Array<T, maxSize>& arr)
	{
		this->m_Size = arr.m_Size;

		for (uint32_t i = 0; i < this->m_Size; ++i) 
		{
			this->m_Data[i] = arr.m_Data[i];
		}

		LOG_INFO("Array COPIED succesfully");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array(Array<T, maxSize>&& arr)
	{
		this->m_Size = arr.m_Size;

		for (uint32_t i = 0; i < arr.m_Size; ++i)
		{
			this->m_Data[i] = std::move(arr.m_Data[i]);
		}

		arr.m_Size = 0;

		LOG_INFO("Array MOVED succesfully");
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::~Array<T, maxSize>()
	{
		LOG_INFO("Array DELETED succesfully");
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Add(T elem)
	{
		if (this->m_Size == maxSize)
		{
			LOG_ERROR("Can't insert, Array is full");
			return;
		}

		this->m_Data[this->m_Size++] = elem;
		
		LOG_INFO("Adding succesful");
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Insert(T elem, uint32_t index)
	{
		if (index >= maxSize)
		{
			LOG_ERROR("Can't insert, index is out of range");
			return;
		}

		if (this->m_Size == maxSize)
		{
			LOG_ERROR("Can't insert, Array is full");
			return;
		}

		for (uint32_t i = this->m_Size; i > index; --i)
		{
			this->m_Data[i] = this->m_Data[i - 1];
		}

		this->m_Data[index] = elem;
		++this->m_Size;

		LOG_INFO("Insert succesful");
	}

	template <typename T, uint32_t maxSize>
	T& Array<T, maxSize>::GetElementAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't get element, index is out of range");
			exit(1);
		}

		if (this->m_Size == 0)
		{
			LOG_FATAL("Can't get element, Array is empty");
			exit(1);
		}

		return this->m_Data[index];
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::DeleteAt(int index)
	{
		if (index >= this->m_Size)
		{
			LOG_ERROR("Can't delete, index is out of range");
			return;
		}

		if (this->m_Size == 0)
		{
			LOG_ERROR("Can't delete, Array is empty");
			return;
		}

		for (uint32_t i = index; i < this->m_Size - 1; ++i)
		{
			this->m_Data[i] = this->m_Data[i + 1];
		}

		--this->m_Size;

		LOG_INFO("Element deleted succesfully");
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Print()
	{
		LOG_DEBUG("This is an Array");

		if(this->m_Size == 0)
		{
			LOG_DEBUG("Array is empty");
		}
		
		for (uint32_t i = 0; i < this->m_Size; i++)
		{
			std::cout << this->m_Data[i] << " ";
		}
		std::cout << "\n";
	}
}