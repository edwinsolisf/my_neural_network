#pragma once

#include <iostream>
#include <array>

class Matrix4
{
private:
	std::array<int, 16> _data;

public:
	Matrix4(const std::array<int,16>& _array)
	{
		std::cout << "mat4 constructed" << std::endl;
		_data = _array;
	}

	Matrix4(std::array<int, 16>&& _array)
	{
		std::cout << "mat4 array moved" << std::endl;
		_data = std::move(_array);
		_array.fill(0);
	}

	Matrix4(const Matrix4& other)
	{
		std::cout << "mat4 copied" << std::endl;
		_data = other._data;
	}

	Matrix4(Matrix4&& other) noexcept
	{
		std::cout << "mat4 moved" << std::endl;
		_data = std::move(other._data);
		other._data.fill(0);
	}

	Matrix4 Add(const Matrix4& other)
	{
		std::array<int, 16> temp = other._data;
		for (int i = 0; i < 16; i++)
			temp[i] += this->_data[i];
		return { std::move(temp) };
	}
};