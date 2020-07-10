#pragma once

#include <iostream>

#if 1
#define PRINT(x) std::cout << x << std::endl
#else
#define PRINT(x) 
#endif
class mat
{
private:
	int _data[1000];

public:
	mat()
		:_data()
	{
	}

	mat(const int* _array)
	{
		PRINT("construct with array");
		memcpy(_data, _array, 1000 * sizeof(int));
	}

	mat(const mat& other)
	{
		PRINT("copy with object");
		memcpy(_data, other._data, 1000 * sizeof(int));
	}

	/*mat(mat&& other)
	{
		PRINT("move with object");
		for(int i = 0; i < 1000; i++)
			_data[i] = std::move(other._data[i]);
	}
*/
	~mat()
	{
		PRINT("destroyed");
	}

	mat Add(const mat& other)
	{
		mat temp;
		memcpy(temp._data, other._data, sizeof(int) * 1000);
		for (int i = 0; i < 1000; i++)
			temp._data[i] += this->_data[i];

		return std::move(temp);
	}

	
};