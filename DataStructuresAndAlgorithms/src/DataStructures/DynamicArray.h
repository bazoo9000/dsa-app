#pragma once

#include "DataStructure.h"

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
		void Fill(T elem);
		T& GetElementAt(uint32_t index);
		const T& GetElementAt(uint32_t index) const;
		void DeleteAt(int index);
		void Clear();
		virtual void Print() override;
		virtual std::unique_ptr<Iterator<T>> CreateIterator() override { return std::make_unique<DynamicArrayIterator<T>>(this); }
		virtual std::unique_ptr<ReverseIterator<T>> CreateReverseIterator() override { return std::make_unique<DynamicArrayReverseIterator<T>>(this); }

	public:
		T* GetData() { return this->m_Data; }
		uint32_t GetSize() { return this->m_Size; }
		uint32_t GetCapacity() { return this->m_Capacity; }

	public:
		T& operator[](uint32_t index) { return GetElementAt(index); }
		const T& operator[](uint32_t index) const { return GetElementAt(index); }
		DynamicArray& operator=(const DynamicArray& arr);
		DynamicArray& operator=(DynamicArray&& arr);

	private:
		void resize(uint32_t newCap);

	private:
		T* m_Data; // the data itself
		uint32_t m_Capacity; // how many elements can an Array hold
	};

	#include "DynamicArray.tpp"
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
		DynamicArrayIterator(DynamicArray<T>* arr);
		~DynamicArrayIterator() = default;

	public:
		virtual void Reset() override;
		virtual const T& GetCurrent() override;
		virtual void Next() override;
		virtual bool IsAtEnd() override;
		virtual std::unique_ptr<Iterator<T>> Clone() override;

	public:
		virtual T& operator*() override;
		virtual std::unique_ptr<Iterator<T>> operator++() override;
		virtual std::unique_ptr<Iterator<T>> operator++(int) override;
		virtual std::unique_ptr<Iterator<T>> operator+(uint32_t idx) override;
		virtual std::unique_ptr<Iterator<T>> operator=(std::unique_ptr<Iterator<T>> it) override;

	private:
		DynamicArray<T>* m_Array;
		uint32_t m_Index = 0;
	};

	#include "Iterator/Implementations/DynamicArrayIterator.tpp"
	//////////////
	// ITERATOR //
	//////////////



	//////////////////////
	// REVERSE ITERATOR //
	//////////////////////
	template <typename T>
	class DynamicArrayReverseIterator : public ReverseIterator<T>
	{
	public:
		DynamicArrayReverseIterator(DynamicArray<T>* arr);
		~DynamicArrayReverseIterator() = default;

	public:
		virtual void Reset() override;
		virtual const T& GetCurrent() override;
		virtual void Prev() override;
		virtual bool IsAtBegin() override;
		virtual std::unique_ptr<ReverseIterator<T>> Clone() override;

	public:
		virtual T& operator*() override;
		virtual std::unique_ptr<ReverseIterator<T>> operator++() override;
		virtual std::unique_ptr<ReverseIterator<T>> operator++(int) override;
		virtual std::unique_ptr<ReverseIterator<T>> operator+(uint32_t idx) override;
		virtual std::unique_ptr<ReverseIterator<T>> operator=(std::unique_ptr<ReverseIterator<T>> it) override;

	private:
		DynamicArray<T>* m_Array;
		uint32_t m_Index = 0;
	};

	#include "Iterator/Implementations/DynamicArrayReverseIterator.tpp"
	//////////////////////
	// REVERSE ITERATOR //
	//////////////////////
}