// ModernCppHashTable.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "HashTable.h"

using Key = std::string;
int stupid_hashing(Key key, int max_index)
{
	return key.size();
}

int basic_hash(Key key, int max_index)
{
	unsigned long hash = 5381;

	for(auto c : key)
		hash = ((hash << 5) + hash) + (c - 'a'); /* hash * 33 + c */

	std::cout << "hash : " << hash << std::endl;
	return hash;
}

int main()
{
	constexpr auto hash_size = 3;
	HashTable<int, hash_size, std::string>* table = new HashTable<int, hash_size, std::string>(basic_hash);
	
	std::array<std::pair<Key, int> , 6> pairs = {
		std::pair<Key , int>("Ma var 1",1),
		std::pair<Key , int>("Ma var 2",2),
		std::pair<Key , int>("The var 3",3),
		std::pair<Key , int>("var 4",4),
		std::pair<Key , int>("var 5",5),
		std::pair<Key , int>("var 6",6)
	};

	for (auto& pair : pairs)
	{
		table->push(pair.first, pair.second);
	}
	
	std::function<void(decltype(table) , Key)> show = [](auto table , auto key)
	{
		auto value = table->get(key);
		if (value != nullptr)
			std::cout << *value << std::endl;
	};

	show(table, "Ma var 1");
	show(table, "Ma var 2");
	show(table, "The var 3");
	show(table, "WrongKey");
	show(table, "var 4");
	show(table, "var 5");
	show(table, "var 6");

	//std::array<int , 6> vars = { 10 , 20 , 30 , 40 , 50 , 60 }; // auto does not work here since list initializer are const which is a problem when hashtable try to store it in a vector
	//auto keys = {"Ma var 1" , "Ma var 2" , "The var 3" , "var 4" , "var 5" , "var 6"};

	/*
	for (auto its = std::make_pair(keys.begin(), vars.begin());
		its.first != keys.end();
		its.first++,its.second++)
	{
		table->push(*(its.first), *(its.second));
	}
	*/
}