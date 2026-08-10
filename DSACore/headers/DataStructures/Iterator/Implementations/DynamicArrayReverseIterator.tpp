template <typename T>
DynamicArrayReverseIterator<T>::DynamicArrayReverseIterator(DynamicArray<T>* arr)
    : m_Array(arr)
{
    m_Index = arr->GetSize() - 1;
}

template <typename T>
void DynamicArrayReverseIterator<T>::Reset()
{
    this->m_Index = m_Array->GetSize() - 1;
}

template <typename T>
const T& DynamicArrayReverseIterator<T>::GetCurrent()
{
    return this->m_Array->GetElementAt(m_Index);
}

template <typename T>
void DynamicArrayReverseIterator<T>::Prev()
{
    if (this->m_Index == 0)
    {
        this->m_Index = UINT32_MAX;
        return;
    }
    this->m_Index--;
}

template <typename T>
bool DynamicArrayReverseIterator<T>::IsAtBegin()
{
    return this->m_Index == UINT32_MAX;
}

template <typename T>
std::unique_ptr<ReverseIterator<T>> DynamicArrayReverseIterator<T>::Clone()
{
    auto it = std::make_unique<DynamicArrayReverseIterator<T>>(this->m_Array);
    it->m_Index = this->m_Index;
    return it;
}

template <typename T>
T& DynamicArrayReverseIterator<T>::operator*()
{
    return this->m_Array->GetElementAt(m_Index);
}

template <typename T>
std::unique_ptr<ReverseIterator<T>> DynamicArrayReverseIterator<T>::operator++()
{
    Prev();
    return Clone();
}

template <typename T>
std::unique_ptr<ReverseIterator<T>> DynamicArrayReverseIterator<T>::operator++(int)
{
    auto old = Clone();
    Prev();
    return old;
}

template <typename T>
std::unique_ptr<ReverseIterator<T>> DynamicArrayReverseIterator<T>::operator+(uint32_t idx)
{
    auto it = std::make_unique<DynamicArrayReverseIterator<T>>(this->m_Array);
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

template <typename T>
std::unique_ptr<ReverseIterator<T>> DynamicArrayReverseIterator<T>::operator=(std::unique_ptr<ReverseIterator<T>> it)
{
    return it->Clone();
}
