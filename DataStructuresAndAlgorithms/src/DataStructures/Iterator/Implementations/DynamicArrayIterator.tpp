template <typename T>
DynamicArrayIterator<T>::DynamicArrayIterator(DynamicArray<T>* arr)
    : m_Array(arr)
{
}

template <typename T>
void DynamicArrayIterator<T>::Reset()
{
    this->m_Index = 0;
}

template <typename T>
const T& DynamicArrayIterator<T>::GetCurrent()
{
    return this->m_Array->GetElementAt(m_Index);
}

template <typename T>
void DynamicArrayIterator<T>::Next()
{
    this->m_Index++;
}

template <typename T>
bool DynamicArrayIterator<T>::IsAtEnd()
{
    return this->m_Index >= this->m_Array->GetSize();
}

template <typename T>
std::unique_ptr<Iterator<T>> DynamicArrayIterator<T>::Clone()
{
    auto it = std::make_unique<DynamicArrayIterator<T>>(this->m_Array);
    it->m_Index = this->m_Index;
    return it;
}

template <typename T>
T& DynamicArrayIterator<T>::operator*()
{
    return this->m_Array->GetElementAt(m_Index);
}

template <typename T>
std::unique_ptr<Iterator<T>> DynamicArrayIterator<T>::operator++()
{
    Next();
    return Clone();
}

template <typename T>
std::unique_ptr<Iterator<T>> DynamicArrayIterator<T>::operator++(int)
{
    auto old = Clone();
    Next();
    return old;
}

template <typename T>
std::unique_ptr<Iterator<T>> DynamicArrayIterator<T>::operator+(uint32_t idx)
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

template <typename T>
std::unique_ptr<Iterator<T>> DynamicArrayIterator<T>::operator=(std::unique_ptr<Iterator<T>> it)
{
    return it->Clone();
}
