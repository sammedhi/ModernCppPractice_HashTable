#pragma once
#include <array>
#include <vector>
#include <functional>

template <typename T , std::size_t Size , typename Key>
class HashTable
{
public:
	HashTable(int (*hash_function)(Key , int max_index)) noexcept;
	~HashTable();

	void push(Key , T& elem);
	T* get(Key);

private:
	std::array<std::vector < std::pair<T* , int>> , Size > m_array;
	std::function<int(Key, int max_index)> m_hashFunction;
	
};

template<typename T, std::size_t Size, typename Key>
inline HashTable<T, Size, typename Key>::HashTable(int (*hash_function)(Key , int max_index)) noexcept
{
	m_hashFunction = hash_function;
}

template<typename T, std::size_t Size, typename Key>
inline HashTable<T, Size, typename Key>::~HashTable()
{
}

template<typename T, std::size_t Size, typename Key>
inline void HashTable<T, Size, Key>::push(Key key ,T& elem)
{
	int hash_index = m_hashFunction(key, Size);
	m_array[hash_index % Size].push_back( std::pair<T* , int>(&elem , hash_index) );
}

template<typename T, std::size_t Size, typename Key>
inline T* HashTable<T, Size, Key>::get(Key key)
{
	int hash_index = m_hashFunction(key, Size);

	auto output_vector = m_array[hash_index % Size];

	for (auto it = output_vector.begin(); it != output_vector.end(); it++)
		if (it->second == hash_index)
			return it->first;
	return nullptr;
}


