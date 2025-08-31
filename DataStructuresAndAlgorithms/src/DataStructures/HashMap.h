#pragma once

#include "DataStructure.h"
#include "DynamicArray.h"
#include "Iterator/ReverseIterable.h"
#include <cstdint>
#include <memory>
#include <utility>

namespace ds
{
    template <typename K> struct HashFunction;
    template <typename K, typename V> class HashMapIterator;
    template <typename K, typename V> class HashMapReverseIterator;

    //////////////
    // HASH MAP //
    //////////////
    template <typename K, typename V>
    class HashMap : public DataStructure<V>, public Iterable<std::pair<K*, V*>>, public ReverseIterable<std::pair<K*, V*>>
    {
        template <typename _K, typename _V>
        struct HashNode
        {
            _K key;
            _V value;
            HashNode<_K, _V>* next = nullptr; // the linked list part of the hash table

            HashNode(_K k, _V v) : key(k), value(v) {}
        };

    public:
        HashMap(uint32_t capacity = 1);
        HashMap(const HashMap& map);
        HashMap(HashMap&& map);
        virtual ~HashMap();

    public:
        void Insert(K key, V value);
        V& GetElement(const K& key);
        const V& GetElement(const K& key) const;
        void Delete(const K& key);
        virtual void Print() override;
        virtual std::unique_ptr<Iterator<std::pair<K*, V*>>> CreateIterator() override;
        virtual std::unique_ptr<ReverseIterator<std::pair<K*, V*>>> CreateReverseIterator() override;

    public:
        uint32_t GetCapacity() const { return m_Capacity; }
        DynamicArray<V> GetValues() const; // size = m_Size
        DynamicArray<K> GetKeys() const; // size = m_Capacity - nullptrs
        uint32_t GetKeyHash(const K& key) const { return m_Hasher(key) % m_Capacity; }

    public:
        HashMap& operator=(const HashMap& map);
        HashMap& operator=(HashMap&& map);
        V& operator[](const K& key) { return GetElement(key); }

    private:
        DynamicArray<HashNode<K, V>*> m_Data; // this is the hash table
        HashFunction<K> m_Hasher;
        uint32_t m_Capacity = 1;
    };

    template <typename K, typename V>
    HashMap<K, V>::HashMap(uint32_t capacity)
        : m_Capacity(capacity)
    {
        if (capacity == 0)
        {
            LOG_ERROR("Max capacity of HashMap can't be 0, setting to 1");
            this->m_Capacity = 1;
        }

        this->m_Data = DynamicArray<HashNode<K, V>*>(this->m_Capacity);
        this->m_Data.Fill(nullptr);

        LOG_INFO("HashMap CREATED successfully");
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(const HashMap<K, V>& map)
    {
        this->m_Capacity = map.m_Capacity;
        this->m_Size = map.m_Size;
        this->m_Data = DynamicArray<HashNode<K, V>*>(this->m_Capacity);
        this->m_Data.Fill(nullptr);

        for (uint32_t i = 0; i < this->m_Capacity; i++)
        {
            if (map.m_Data[i] == nullptr)
            {
                this->m_Data[i] = nullptr;
                continue;
            }

            this->m_Data[i] = new HashNode<K, V>(map.m_Data[i]->key, map.m_Data[i]->value);
            HashNode<K, V>* node = map.m_Data[i];
            HashNode<K, V>* next = node->next;

            while (next != nullptr)
            {
                node->next = new HashNode<K, V>(next->key, next->value);
                node = node->next;
                next = next->next;
            }
        }

        LOG_INFO("HashMap COPIED successfully");
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(HashMap<K, V>&& map)
    {
        this->m_Capacity = map.m_Capacity;
        this->m_Size = map.m_Size;
        this->m_Data = std::move(map.m_Data);
        map.m_Capacity = 0;
        map.m_Data.Clear();

        LOG_INFO("HashMap MOVED successfully");
    }

    template <typename K, typename V>
    HashMap<K, V>::~HashMap()
    {
        for (uint32_t i = 0; i < this->m_Capacity; i++)
        {
            HashNode<K, V>* node = this->m_Data[i];
            while (node != nullptr)
            {
                HashNode<K, V>* nextNode = node->next;
                delete node;
                node = nextNode;
            }
        }
        this->m_Capacity = 0;

        LOG_INFO("HashMap DESTROYED successfully");
    }

    template <typename K, typename V>
    void HashMap<K, V>::Insert(K key, V value)
    {
        uint32_t idx = GetKeyHash(key);
        HashNode<K, V>* newNode = new HashNode<K, V>(key, value);

        if (this->m_Data[idx] == nullptr)
        {
            this->m_Data[idx] = newNode;
        }
        else
        {
            LOG_TRACE("Collision detected at index %d for key '%s'", idx, typeid(key).name());

            HashNode<K, V>* curNode = this->m_Data[idx];
            HashNode<K, V>* prevNode = nullptr;
            while (curNode != nullptr)
            {
                // this is for the case when the key already exists
                if (curNode->key == key)
                {
                    curNode->value = value;
                    delete newNode;

                    this->m_Size++;
                    LOG_DEBUG("Inserting key '%s' was successful, key already exists, new size is %u", typeid(key).name(), this->m_Size);
                    return;
                }
                prevNode = curNode;
                curNode = curNode->next;
            }

            // if key doesn't exist, then insert at the end of the linked list
            prevNode->next = newNode;
        }

        this->m_Size++;
        LOG_DEBUG("Inserting was succesfull, new size is %u", this->m_Size);
    }

    template <typename K, typename V>
    V& HashMap<K, V>::GetElement(const K& key)
    {
        uint32_t idx = GetKeyHash(key);
        HashNode<K, V>* node = this->m_Data[idx];

        while (node != nullptr)
        {
            if (node->key == key)
            {
                LOG_DEBUG("Got element successfully");
                return node->value;
            }
            node = node->next;
        }

        LOG_ERROR("Can't get element, key not found");
    }

    template <typename K, typename V>
    const V& HashMap<K, V>::GetElement(const K& key) const
    {
        uint32_t idx = GetKeyHash(key);
        HashNode<K, V>* node = this->m_Data[idx];

        while (node != nullptr)
        {
            if (node->key == key)
            {
                LOG_DEBUG("Got element with key '%s' successfully", typeid(key).name());
                return node->value;
            }
            node = node->next;
        }

        LOG_ERROR("Can't get element, key not found");
    }

    template <typename K, typename V>
    void HashMap<K, V>::Delete(const K& key)
    {
        uint32_t idx = GetKeyHash(key);
        HashNode<K, V>* delNode = this->m_Data[idx];
        HashNode<K, V>* prevNode = nullptr;

        while (delNode != nullptr)
        {
            if (delNode->key == key)
            {
                if (prevNode == nullptr)
                {
                    this->m_Data[idx] = delNode->next;
                }
                else
                {
                    prevNode->next = delNode->next;
                }

                delete delNode;
                this->m_Size--;
                LOG_DEBUG("Deleted element successfully, new size is %u", this->m_Size);
                return;
            }
            prevNode = delNode;
            delNode = delNode->next;
        }

        LOG_ERROR("Can't delete, key not found");
    }

    template <typename K, typename V>
    DynamicArray<V> HashMap<K, V>::GetValues() const
    {
        DynamicArray<V> values(this->m_Size);
        uint32_t index = 0;

        for (uint32_t i = 0; i < this->m_Capacity; i++)
        {
            HashNode<K, V>* node = this->m_Data[i];
            while (node != nullptr)
            {
                values.Add(node->value);
                node = node->next;
            }
        }

        return values;
    }

    template <typename K, typename V>
    DynamicArray<K> HashMap<K, V>::GetKeys() const
    {
        DynamicArray<K> keys(this->m_Capacity);

        for (uint32_t i = 0; i < this->m_Capacity; i++)
        {
            HashNode<K, V>* node = this->m_Data[i];
            while (node != nullptr)
            {
                keys.Add(node->key);
                node = node->next;
            }
        }

        return keys;
    }

    template <typename K, typename V>
    void HashMap<K, V>::Print()
    {
        LOG_DEBUG("This is a HashMap");
    }

    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMap<K, V>::CreateIterator()
    {
        DynamicArray<std::pair<K*, V*>> arr(this->m_Size);

        for (uint32_t i = 0; i < this->m_Capacity; i++)
        {
            HashNode<K, V>* node = this->m_Data[i];
            while (node != nullptr)
            {
                arr.Add({ &node->key, &node->value });
                node = node->next;
            }
        }

        return std::make_unique<HashMapIterator<K, V>>(arr);
    }

    template <typename K, typename V>
    HashMap<K, V>& HashMap<K, V>::operator=(const HashMap<K, V>& map)
    {
        this->m_Capacity = map.m_Capacity;
        this->m_Data = map.m_Data;

        LOG_INFO("HashMap COPIED successfully");
        return *this;
    }

    template <typename K, typename V>
    HashMap<K, V>& HashMap<K, V>::operator=(HashMap<K, V>&& map)
    {
        this->m_Capacity = map.m_Capacity;
        this->m_Data = std::move(map.m_Data);
        map.m_Capacity = 0;
        map.m_Data.Clear();

        LOG_INFO("HashMap MOVED successfully");
        return *this;
    }
    //////////////
    // HASH MAP //
    //////////////


    ////////////////////////////
    // HASH FUNCTION ABSTRACT //
    ////////////////////////////
    template <typename K>
    struct HashFunction
    {
        uint32_t operator()(const K& key) const
        {
            LOG_FATAL("HashFunction for type '%s' doesn't exist", typeid(K).name());
            exit(1);

            return 0;
        }
    };
    ////////////////////////////
    // HASH FUNCTION ABSTRACT //
    ////////////////////////////


    ///////////////////////////////////
    // HASH FUNCTION IMPLEMENTATIONS //
    ///////////////////////////////////

    // INT //
    template <>
    struct HashFunction<int>
    {
        uint32_t operator()(int key) const
        {
            return static_cast<uint32_t>(key);
        }
    };
    // INT //

    // FLOAT //
    template <>
    struct HashFunction<float>
    {
        uint32_t operator()(float key) const
        {
            return *reinterpret_cast<uint32_t*>(&key); // this might be a horrible idea to use, just in case someone uses it
        }
    };
    // FLOAT //

    // CHAR //
    template <>
    struct HashFunction<char>
    {
        uint32_t operator()(char key) const
        {
            return static_cast<uint32_t>(key);
        }
    };
    // CHAR //

    // STRING //
    template<>
    struct HashFunction<const char*>
    {
        uint32_t operator()(const char* key) const
        {
            // this isnt a std library worthy hash function
            // this is only for demonstration purposes only
            // make another one using std::string as shown in TUTORIAL section
            uint32_t hash = 0;
            uint32_t size = (uint32_t)strlen(key);

            for (uint32_t i = 0; i < size; ++i)
            {
                hash = (hash * 31) + key[i];
            }

            return hash;
        }
    };
    // STRING //

    // TUTORIAL //
    //
    //  TODO: put his tutorial in the docs
    //
    // To hash your own type of key, you need to implement your own specialization of the HashFunction template.
    // Like this:
    //
    // template <>
    // struct HashFunction<TYPE>
    // {
    //     uint32_t operator()(const TYPE& key) const
    //     {
    //         uint32_t hash = 0;
    //         // implementation lies here
    //         return hash;
    //     }
    // };
    //
    // TUTORIAL //

    ///////////////////////////////////
    // HASH FUNCTION IMPLEMENTATIONS //
    ///////////////////////////////////


    //////////////
    // ITERATOR //
    //////////////

    template <typename K, typename V>
    class HashMapIterator : public Iterator<std::pair<K*, V*>>
    {
    public:
        HashMapIterator(DynamicArray<std::pair<K*, V*>> data) : m_Data(data) {}
        ~HashMapIterator() = default;

    public:
        void Reset() override { m_Index = 0; }
        const std::pair<K*, V*>& GetCurrent() override { return this->m_Data[m_Index]; }
        void Next() override { m_Index++; }
        bool IsAtEnd() override { return m_Index == m_Data.GetSize();}
        std::unique_ptr<Iterator<std::pair<K*, V*>>> Clone() override { return std::make_unique<HashMapIterator<K, V>>(m_Data); }

    public:
        std::pair<K*, V*>& operator*() override { return this->m_Data[m_Index]; }
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator++() override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator++(int) override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator+(uint32_t idx) override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator=(std::unique_ptr<Iterator<std::pair<K*, V*>>> it) override { return Clone(); }

    private:
        DynamicArray<std::pair<K*, V*>> m_Data;
        uint32_t m_Index = 0;
    };

    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapIterator<K, V>::operator++()
    {
        Next();
        return Clone();
    }
    
    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapIterator<K, V>::operator++(int)
    {
        auto old = Clone();
        Next();
        return old;
    }

    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapIterator<K, V>::operator+(uint32_t idx)
    {
        auto it = std::make_unique<HashMapIterator<K, V>>(m_Data);
        it->m_Index = this->m_Index;
        it->m_Index += idx;
    
        if (it->m_Index >= it->m_Data.GetSize())
        {
            it->m_Index = it->m_Data.GetSize();
        }

        return it;
    }


    template <typename K, typename V>
    class HashMapReverseIterator : public ReverseIterator<std::pair<K*, V*>>
    {
    public:
        HashMapReverseIterator(DynamicArray<std::pair<K*, V*>> data) : m_Data(data) { m_Index = m_Data.GetSize() - 1; }
        ~HashMapReverseIterator() = default;

    public:
        void Reset() override { this->m_Index = m_Data.GetSize() - 1; }
        const std::pair<K*, V*>& GetCurrent() override { return this->m_Data[m_Index]; }
        void Prev() override { if (this->m_Index == 0 ) { m_Index = this->m_Data.GetSize(); return; } this->m_Index--; }
        bool IsAtBegin() override { return m_Index == m_Data.GetSize();}
        std::unique_ptr<Iterator<std::pair<K*, V*>>> Clone() override { return std::make_unique<HashMapReverseIterator<K, V>>(this->m_Data); }

    public:
        std::pair<K*, V*>& operator*() override { return this->m_Data[this->m_Index]; }
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator++() override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator++(int) override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator+(uint32_t idx) override;
        std::unique_ptr<Iterator<std::pair<K*, V*>>> operator=(std::unique_ptr<Iterator<std::pair<K*, V*>>> it) override { return Clone(); }

    private:
        DynamicArray<std::pair<K*, V*>> m_Data;
        uint32_t m_Index;
    };

    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapReverseIterator<K, V>::operator++()
    {
        Prev();
        return Clone();
    }
    
    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapReverseIterator<K, V>::operator++(int)
    {
        auto old = Clone();
        Prev();
        return old;
    }

    template <typename K, typename V>
    std::unique_ptr<Iterator<std::pair<K*, V*>>> HashMapReverseIterator<K, V>::operator+(uint32_t idx)
    {
        auto it = std::make_unique<HashMapReverseIterator<K, V>>(this->m_Data);
        it->m_Index = this->m_Index;

        if (it->m_Index < idx)
        {
            it->m_Index = it->m_Data.GetSize();
        }
        else
        {
            it->m_Index -= idx;
        }

        return it;
    }

    //////////////
    // ITERATOR //
    //////////////
}