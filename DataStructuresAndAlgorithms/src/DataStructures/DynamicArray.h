#pragma once

#include "DataStructure.h"
#include "Iterator/ReverseIterable.h"
#include <cstdint>
#include <memory>

namespace ds
{
	template <typename T> class DynamicArrayIterator;
	template <typename T> class DynamicArrayReverseIterator;

	///////////////////
	// DYNAMIC ARRAY //
	///////////////////
	template <typename T>
	class DynamicArray : public DataStructure<T>, public Iterable<T>, public ReverseIterable<T>
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
		virtual std::unique_ptr<Iterator<T>> CreateIterator() override { return std::make_unique<DynamicArrayIterator<T>>(this); }
		virtual std::shared_ptr<ReverseIterator<T>> CreateReverseIterator() override { return std::make_shared<DynamicArrayReverseIterator<T>>(this); }

	public:
		T* GetData() { return this->m_Data; }
		uint32_t GetSize() { return this->m_Size; }
		uint32_t GetCapacity() { return this->m_Capacity; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		DynamicArray& operator=(const DynamicArray& arr);
		DynamicArray& operator=(DynamicArray&& arr);

	private:
		void resize(uint32_t newCap);

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
			LOG_WARN("Max capacity of DynamicArray is 0");
		}

		this->m_Size = 0;
		this->m_Data = new T[this->m_Capacity];

		LOG_INFO("DynamicArray CREATED succesfully");
	}

	template <typename T>
	DynamicArray<T>::DynamicArray(const DynamicArray<T>& arr)
	{
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

		LOG_DEBUG("Adding succesful, new size is %u", this->m_Size);
	}

	template <typename T>
	void DynamicArray<T>::Insert(T elem, uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_ERROR("Can't insert, index %u is out of range", index);
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

		LOG_DEBUG("Inserting at index %u succesful, new size is %u", index, this->m_Size);
	}

	template <typename T>
	T& DynamicArray<T>::GetElementAt(uint32_t index)
	{
		if (index >= this->m_Size)
		{
			LOG_FATAL("Can't get element, index %u is out of range", index);
			exit(1);
		}

		LOG_DEBUG("Got element at index %u succesfully", index);

		return this->m_Data[index];
	}

	template <typename T>
	void DynamicArray<T>::DeleteAt(int index)
	{
		if (index >= this->m_Size)
		{
			LOG_ERROR("Can't delete, index %u is out of range", index);
			return;
		}

		for (uint32_t i = index; i < this->m_Size - 1; ++i)
		{
			this->m_Data[i] = this->m_Data[i + 1];
		}

		--this->m_Size;
		LOG_DEBUG("Element at index %u was deleted succesfully, new size %u", index, this->m_Size);
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

		LOG_DEBUG("DynamicArray has been cleared");
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
	void DynamicArray<T>::resize(uint32_t newCap)
	{
		T* newData = new T[newCap];
		for (uint32_t i = 0; i < this->m_Size; ++i) {
			newData[i] = this->m_Data[i];
		}

		delete[] this->m_Data;
		this->m_Data = newData;
		this->m_Capacity = newCap;

		LOG_DEBUG("DynamicArray has been resized to new capacity %u", newCap);
	}
	///////////////////
	// DYNAMIC ARRAY //
	///////////////////

	//////////////
	// ITERATOR //
	//////////////
	template <typename T>
	class DynamicArrayIterator : public Iterator<T>
	{
	public:
		DynamicArrayIterator(DynamicArray<T>* arr) : m_Array(arr) {}
		~DynamicArrayIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = 0; }
		virtual const T& GetCurrent() override { return this->m_Array->GetElementAt(m_Index); }
		virtual void Next() override { this->m_Index++; }
		virtual bool IsAtEnd() override { return this->m_Index >= this->m_Array->GetSize(); }
		virtual std::unique_ptr<Iterator<T>> Clone() override
		{
			auto it = std::make_unique<DynamicArrayIterator<T>>(this->m_Array);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return this->m_Array->GetElementAt(m_Index); }
		virtual std::unique_ptr<Iterator<T>> operator++() override
		{
			auto it = std::make_unique<DynamicArrayIterator<T>>(this->m_Array);
			it->m_Index = this->m_Index;
			Next();
			return it;
		}
		virtual std::unique_ptr<Iterator<T>> operator+(uint32_t idx) override
		{
			auto it = std::make_unique<DynamicArrayIterator<T>>(this->m_Array);
			it->m_Index = this->m_Index;

			if (it->m_Index + idx >= it->m_Array->GetSize())
			{
				it->m_Index = it->m_Array->GetSize();
			}
			else
			{
				it->m_Index += idx;
			}

			return it;
		}
        virtual std::unique_ptr<Iterator<T>> operator=(std::unique_ptr<Iterator<T>> it) override
		{
			return it->Clone();
		}

	private:
		DynamicArray<T>* m_Array;
		uint32_t m_Index = 0;
	};

	template <typename T>
	class DynamicArrayReverseIterator : public ReverseIterator<T>
	{
	public:
		DynamicArrayReverseIterator(DynamicArray<T>* arr) : m_Array(arr) { m_Index = arr->GetSize() - 1; }
		~DynamicArrayReverseIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = m_Array->GetSize() - 1; }
		virtual const T& GetCurrent() override { return this->m_Array->GetElementAt(m_Index); }
		virtual void Prev() override { this->m_Index--; }
		virtual bool IsAtBegin() override { return this->m_Index == UINT32_MAX; }
		virtual std::shared_ptr<ReverseIterator<T>> Clone() override
		{
			auto it = std::make_shared<DynamicArrayReverseIterator<T>>(this->m_Array);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return this->m_Array->GetElementAt(m_Index); }
		virtual ReverseIterator<T>& operator++() override
		{
			Prev();
			return *this;
		}

	private:
		DynamicArray<T>* m_Array;
		uint32_t m_Index = 0;
	};
	//////////////
	// ITERATOR //
	//////////////
}