#pragma once

#include "DataStructure.h"
#include "Iterator/Iterable.h"

namespace ds
{
	template <typename T, uint32_t maxSize> class ArrayIterator;
	template <typename T, uint32_t maxSize> class ArrayReverseIterator;

	///////////
	// ARRAY //
	///////////
	template <typename T, uint32_t maxSize>
	class Array : public DataStructure<T>, public Iterable<T>, public ReverseIterable<T>
	{
	public:
		Array();
		Array(const Array& arr);
		Array(Array&& arr);
		~Array();

	public:
		void Add(T elem);
		void Insert(T elem, uint32_t index);
		void Fill(T elem);
		T& GetElementAt(uint32_t index);
		const T& GetElementAt(uint32_t index) const;
		void DeleteAt(int index);
		virtual void DebugDetails() override;
		virtual std::unique_ptr<Iterator<T>> CreateIterator() override { return std::make_unique<ArrayIterator<T, maxSize>>(this); }
		virtual std::unique_ptr<ReverseIterator<T>> CreateReverseIterator() override { return std::make_unique<ArrayReverseIterator<T, maxSize>>(this); }

	public:
		T* GetData() { return this->m_Data; }
		uint32_t GetMaxSize() { return maxSize; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		const T& operator[](uint32_t index) const { return GetElementAt(index); }
		Array& operator=(const Array& arr);
		Array& operator=(Array&& arr);

	private:
		T m_Data[maxSize]; // the data itself
	};

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>::Array()
	{
		if(maxSize == 0)
		{
			LOG_WARN("The size of the created Array is 0");
		}

		LOG_INFO("Array CREATED succesfully");
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
		
		LOG_DEBUG("Adding succesful, new size is %u", this->m_Size);
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

		LOG_DEBUG("Inserting at index %u succesful, new size is %u", index, this->m_Size);
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::Fill(T elem)
	{
		for (uint32_t i = 0; i < maxSize; i++)
		{
			this->m_Data[i] = elem;
		}

		this->m_Size = maxSize;

		LOG_DEBUG("Array filled succesfully");
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

		LOG_DEBUG("Got element at index %u succesfully", index);

		return this->m_Data[index];
	}

	template <typename T, uint32_t maxSize>
	const T& Array<T, maxSize>::GetElementAt(uint32_t index) const
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

		LOG_DEBUG("Got element at index %u succesfully", index);

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

		LOG_DEBUG("Element at index %u was deleted succesfully, new size %u", index, this->m_Size);
	}

	template <typename T, uint32_t maxSize>
	void Array<T, maxSize>::DebugDetails()
	{
		std::ostringstream oss;

		oss << "[ ";
		
		for (uint32_t i = 0; i < std::min<uint32_t>(this->m_Size, MAX_OUTPUT_SIZE); i++)
		{
			if constexpr (IS_STREAMABLE(T)) { oss << this->m_Data[i] << " "; }
			else 							{ oss << typeid(this->m_Data[0]).name() << " "; }
		}

		if (this->m_Size > MAX_OUTPUT_SIZE) { oss << "... "; }
		else
		{
			for (uint32_t i = this->m_Size; i < std::min<uint32_t>(maxSize, MAX_OUTPUT_SIZE); i++)
			{
				oss << "NULL ";
			}
		}

		oss << "]";

		LOG_DEBUG("This is an Array\nSize: %u\nMax size: %u\nBytes: %u\nData: %s\n",
			this->m_Size, maxSize,
			sizeof(this->m_Data),
			oss.str().c_str()
		);
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>& Array<T, maxSize>::operator=(const Array<T, maxSize>& arr)
	{
		this->m_Size = arr.m_Size;

		for (uint32_t i = 0; i < this->m_Size; ++i)
		{
			this->m_Data[i] = arr.m_Data[i];
		}

		LOG_INFO("Array COPIED succesfully");
		return *this;
	}

	template <typename T, uint32_t maxSize>
	Array<T, maxSize>& Array<T, maxSize>::operator=(Array<T, maxSize>&& arr)
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
	///////////
	// ARRAY //
	///////////

	//////////////
	// ITERATOR //
	//////////////
	template <typename T, uint32_t maxSize>
	class ArrayIterator : public Iterator<T>
	{
	public:
		ArrayIterator(Array<T, maxSize>* arr) : m_Array(arr) {}
		~ArrayIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = 0; }
		virtual const T& GetCurrent() override { return this->m_Array->GetElementAt(m_Index); }
		virtual void Next() override { this->m_Index++; }
		virtual bool IsAtEnd() override { return this->m_Index >= this->m_Array->GetSize(); }
		virtual std::unique_ptr<Iterator<T>> Clone() override
		{
			auto it = std::make_unique<ArrayIterator<T, maxSize>>(this->m_Array);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return this->m_Array->GetElementAt(m_Index); }
		virtual std::unique_ptr<Iterator<T>> operator++() override
		{
			Next();
			return Clone();
		}
		virtual std::unique_ptr<Iterator<T>> operator++(int) override
		{
			auto old = Clone();
			Next();
			return old;
		}
		virtual std::unique_ptr<Iterator<T>> operator+(uint32_t idx) override
		{
			auto it = std::make_unique<ArrayIterator<T, maxSize>>(this->m_Array);
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
			return Clone();
		}

	private:
		Array<T, maxSize>* m_Array;
		uint32_t m_Index = 0;
	};

	template <typename T, uint32_t maxSize>
	class ArrayReverseIterator : public ReverseIterator<T>
	{
	public:
		ArrayReverseIterator(Array<T, maxSize>* arr) : m_Array(arr) { m_Index = arr->GetSize() - 1; }
		~ArrayReverseIterator() = default;

	public:
		virtual void Reset() override { this->m_Index = m_Array->GetSize() - 1; }
		virtual const T& GetCurrent() override { return this->m_Array->GetElementAt(m_Index); }
		virtual void Prev() override { this->m_Index--; }
		virtual bool IsAtBegin() override { return this->m_Index == UINT32_MAX; }
		virtual std::unique_ptr<ReverseIterator<T>> Clone() override
		{
			auto it = std::make_unique<ArrayReverseIterator<T, maxSize>>(this->m_Array);
			it->m_Index = this->m_Index;
			return it;
		}

	public:
		virtual T& operator*() override { return this->m_Array->GetElementAt(m_Index); }
		virtual std::unique_ptr<ReverseIterator<T>> operator++() override
		{
			Prev();
			return Clone();
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator++(int) override
		{
			auto old = Clone();
			Prev();
			return old;
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator+(uint32_t idx) override
		{
			auto it = std::make_unique<ArrayReverseIterator<T, maxSize>>(this->m_Array);
			it->m_Index = this->m_Index;

			if (it->m_Index < idx)
			{
				it->m_Index = it->m_Array->GetSize();
			}
			else
			{
				it->m_Index -= idx;
			}

			return it;
		}
		virtual std::unique_ptr<ReverseIterator<T>> operator=(std::unique_ptr<ReverseIterator<T>> it) override
		{
			return Clone();
		}

	private:
		Array<T, maxSize>* m_Array;
		uint32_t m_Index = 0;
	};
	//////////////
	// ITERATOR //
	//////////////
}