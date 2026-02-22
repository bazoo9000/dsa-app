#pragma once

#include "../../dsa_pch.h"
#include "Logger/Logger.h"

// TODO: split into more cache managers of specific type, ridiculously restrictive
// Uses LRU Cache
template <typename T>
class CacheManager
{
private:
	struct CacheNode
	{
		std::string key;
		T value;
		CacheNode* next = nullptr;
		CacheNode* prev = nullptr;

		CacheNode(std::string key, T value, CacheNode* next = nullptr, CacheNode* prev = nullptr)
			: key(key), value(value), next(next), prev(prev)
		{
		}
	};

public:
	// If capacity is left at 0, then it's limitless cache
	CacheManager(uint32_t capacity = 0);
	~CacheManager();

public:
	void Cache(std::string key, T value);
	bool IsCached(std::string key);
	std::vector<std::string> GetMissingKeys(std::vector<std::string> keys);
	T* Get(std::string key);
	void Clear();

private:
	void deleteLast();
	void prioritise(CacheNode* usedNode);

private:
	// hash map for easy access
	// doubly linked list for reordering and managing LRU cache
	// since we use pointers to data, its only allocated once
	// deleted nodes will be marked as NULL
	// also no raw pointers, managing them will be an absolute nightmare (too bad)
	std::unordered_map<std::string, CacheNode*> m_CacheMap;
	CacheNode* m_Head; // TODO: remake linked lists so it can also use pointers to its data
	CacheNode* m_Tail;
	uint32_t m_Capacity;
};


template <typename T>
CacheManager<T>::CacheManager(uint32_t capacity)
	: m_Capacity(capacity)
{
	m_Head = nullptr;
	m_Tail = nullptr;
}

template <typename T>
CacheManager<T>::~CacheManager()
{
	m_Capacity = 0;
	Clear();
}

template<typename T>
void CacheManager<T>::Cache(std::string key, T value)
{
	if (IsCached(key))
	{
		LOG_GUI_ERROR("Can't cache, '%s' key already exists in cache", key.c_str());
		return;
	}

	if (m_Capacity != 0 && m_CacheMap.size() >= m_Capacity)
	{
		LOG_GUI_DEBUG("Max capacity of cache reached, deleting last element");
		deleteLast();
	}

	CacheNode* newNode = new CacheNode(key, value);
	if (m_Tail == nullptr)
	{
		m_Head = m_Tail = newNode; // in case there was no element in the list
	}
	else
	{
		newNode->next = m_Head;
		m_Head->prev = newNode;
		m_Head = newNode;
	}

	m_CacheMap[key] = newNode;
	LOG_GUI_DEBUG("'%s' cached succesfully", key.c_str());
}

template<typename T>
bool CacheManager<T>::IsCached(std::string key)
{
	return (m_CacheMap.find(key) != m_CacheMap.end());
}

template<typename T>
inline std::vector<std::string> CacheManager<T>::GetMissingKeys(std::vector<std::string> keys)
{
	std::vector<std::string> missed;

	for (auto key : keys)
	{
		if (!IsCached(key))
		{
			missed.push_back(key);
		}
	}

	return missed;
}

template<typename T>
T* CacheManager<T>::Get(std::string key)
{
	if (!IsCached(key))
	{
		LOG_GUI_ERROR("'%s' is not cached", key.c_str());
		return nullptr;
	}
	else if (m_CacheMap.at(key) == nullptr)
	{
		LOG_GUI_ERROR("'%s' has no data, it was deleted", key.c_str());
		return nullptr;
	}
	else
	{
		prioritise(m_CacheMap.at(key));
		return &m_CacheMap.at(key)->value;
	}
}

template<typename T>
void CacheManager<T>::Clear()
{
	for (auto it = m_CacheMap.begin(); it != m_CacheMap.end(); it++)
	{
		CacheNode* crt = it->second;
		delete crt;
	}

	m_CacheMap.clear();

	m_Head = nullptr;
	m_Tail = nullptr;
}

template<typename T>
void CacheManager<T>::deleteLast()
{
	if (m_Tail == nullptr)
	{
		LOG_GUI_ERROR("Can't delete, cache is empty");
		return;
	}

	CacheNode* delNode = m_Tail;
	
	if (delNode == m_Head)
	{
		m_Head = m_Tail = nullptr;
	}
	else
	{
		m_Tail = m_Tail->prev;
		m_Tail->next = nullptr;
	}

	m_CacheMap.erase(delNode->key);

	LOG_GUI_DEBUG("'%s' deleted", delNode->key.c_str());

	delete delNode;
}

template<typename T>
void CacheManager<T>::prioritise(CacheNode* usedNode)
{
	if (usedNode == nullptr || usedNode == m_Head) return;

	if (usedNode->prev) usedNode->prev->next = usedNode->next;
	if (usedNode->next) usedNode->next->prev = usedNode->prev;

	if (usedNode == m_Tail) m_Tail = usedNode->prev;

	usedNode->prev = nullptr;
	usedNode->next = m_Head;

	if (m_Head != nullptr) m_Head->prev = usedNode;

	m_Head = usedNode;

	if (m_Tail == nullptr) m_Tail = usedNode;
}
