#pragma once
#include <iostream>

//#if 0
//#define PRINT(x) std::cout << x << std::endl
//#else
//#define PRINT(x) 
//#endif

class Node
{
private:
	int* _data;
	unsigned int _count;

public:

	Node(const unsigned int& count)
		:_count(count)
	{
		_data = new int[_count] {};
		PRINT("constructed");
	}

	Node(const Node& other)
	{
		_count = other._count;
		_data = new int[_count];
		memcpy(_data, other._data, _count);
		PRINT("copied");
	}

	inline int& operator[](const unsigned int& index) { return _data[index]; }

	Node(Node&& other) noexcept
	{
		_count = other._count;
		_data = other._data;

		other._count = 0;
		other._data = nullptr;
		PRINT("moved");
	}

	Node Add(const Node& other)
	{
		Node temp(_count);
		memcpy(temp._data, other._data, _count);
		
		for (int i = 0; i < _count; i++)
			temp._data[i] += _data[i];

		return temp;
	}

	~Node()
	{
		delete _data;
	}
};