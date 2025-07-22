#pragma once

#include "DataStructure.h"
#include "DynamicArray.h"

namespace ds
{
    template <typename K> struct HashFunction;
    template <typename K, typename V> class HashMapIterator;
    // template <typename K, typename V> class HashMapReverseIterator; // TODO: implement reverse iterator

    //////////////
    // HASH MAP //
    //////////////
    template <typename K, typename V>
    class HashMap : public DataStructure<V>, public Iterable<V>
    {
        friend class HashMapIterator<K, V>;

    private:
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
        virtual std::unique_ptr<Iterator<V>> CreateIterator() override { return std::make_unique<HashMapIterator<K, V>>(this); }

    public:
        uint32_t GetCapacity() const { return m_Capacity; }
        DynamicArray<V> GetValues() const;
        DynamicArray<K> GetKeys() const;
        uint32_t GetKeyHash(const K& key) const { return m_Hasher(key) % m_Capacity; }

    public:
        HashMap& operator=(const HashMap& map) = default;
        HashMap& operator=(HashMap&& map) = default;

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
        this->m_Data = map.m_Data;

        LOG_INFO("HashMap COPIED successfully");
    }

    template <typename K, typename V>
    HashMap<K, V>::HashMap(HashMap<K, V>&& map)
    {
        this->m_Capacity = map.m_Capacity;
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

                    LOG_DEBUG("Inserting key '%s' was successful, key already exists, size remains the same", typeid(key).name());
                    return;
                }
                prevNode = curNode;
                curNode = curNode->next;
            }

            // if key doesn't exist, then insert at the end of the linked list
            prevNode->next = newNode;
        }

        this->m_Size++;
        LOG_DEBUG("Inserting key '%s' was succesfull, new size is %u", typeid(key).name(), this->m_Size);
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
                LOG_DEBUG("Got element with key '%s' successfully", typeid(key).name());
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
                LOG_DEBUG("Deleted element with key '%s' successfully, new size is %u", typeid(key).name(), this->m_Size);
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
        DynamicArray<K> keys(this->m_Size);

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

    // TODO: implement
    template <typename K, typename V>
    class HashMapIterator : public Iterator<V>
    {
    public:
        HashMapIterator(HashMap<K, V>* map) {}
        ~HashMapIterator() = default;

    public:
        void Reset() override {}
        const V& GetCurrent() override { return m_Data[m_Index]->value; }
        const K& GetKey() override { return m_Data[m_Index]->key; }
        void Next() override {}
        bool IsAtEnd() override { return false;}
        std::unique_ptr<Iterator<V>> Clone() override { return std::make_unique<HashMapIterator<K, V>>(nullptr); }

    public:
        V& operator*() override { return m_Data[m_Index]->value; }
        std::unique_ptr<Iterator<V>> operator++() override { return std::make_unique<HashMapIterator<K, V>>(nullptr); }
        std::unique_ptr<Iterator<V>> operator++(int) override { return std::make_unique<HashMapIterator<K, V>>(nullptr); }
        std::unique_ptr<Iterator<V>> operator+(uint32_t idx) override { return std::make_unique<HashMapIterator<K, V>>(nullptr); }
        std::unique_ptr<Iterator<V>> operator=(std::unique_ptr<Iterator<V>> it) override { return std::make_unique<HashMapIterator<K, V>>(nullptr); }

    private:
        DynamicArray<typename HashMap<K, V>::template HashNode<K, V>*> m_Data;
        uint32_t m_Index = 0;
    };

    

    //////////////
    // ITERATOR //
    //////////////
}