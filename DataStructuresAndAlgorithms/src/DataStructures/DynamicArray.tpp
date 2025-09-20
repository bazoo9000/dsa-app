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
void DynamicArray<T>::Fill(T elem)
{
    for (uint32_t i = 0; i < this->m_Capacity; i++)
    {
        this->m_Data[i] = elem;
    }

    this->m_Size = m_Capacity;

    LOG_DEBUG("DynamicArray filled succesfully");
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
const T& DynamicArray<T>::GetElementAt(uint32_t index) const
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
void DynamicArray<T>::DebugDetails()
{
    std::ostringstream oss;

    oss << "[ ";

    for (uint32_t i = 0; i < std::min<uint32_t>(this->m_Size, MAX_OUTPUT_SIZE); i++)
    {
        if constexpr (IS_STREAMABLE(T)) { oss << this->m_Data[i] << " "; }
        else                            { oss << typeid(this->m_Data[0]).name() << " "; }
    }

    if (this->m_Size > MAX_OUTPUT_SIZE) { oss << "... "; }
    else
    {
        for (uint32_t i = this->m_Size; i < std::min<uint32_t>(this->m_Capacity, MAX_OUTPUT_SIZE); i++)
        {
            oss << "NULL ";
        }
    }

    oss << "]";

    LOG_DEBUG("This is an DynamicArray\nSize: %u\nCapacity: %u\nBytes: %u\nData: %s\n",
        this->m_Size,
        this->m_Capacity,
        this->m_Capacity * sizeof(T),
        oss.str().c_str()
    );
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