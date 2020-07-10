#pragma once
#include "Vector.h"
#include <iostream>
template <unsigned int columns, unsigned int rows>
class Matrix
{
private:
	float _matrixValues[columns*rows];

public:
	Matrix() :_matrixValues()
	{
		//std::cout << "Empty constuctor" << std::endl;	
		for (unsigned int i = 0; i < columns*rows; i++)
			_matrixValues[i] = 0;
	}
		
	Matrix(const float values[columns*rows])
	{
		//std::cout << "Array constructor" << std::endl;
		for (int i = 0; i < columns*rows; i++)
		{
			_matrixValues[i] = values[i];
		}
	}

	Matrix(const Matrix& other)
	{
		for (unsigned int i = 0; i < columns*rows; i++)
			_matrixValues[i] = other._matrixValues[i];
	}

	float* operator[] (const unsigned int& column)
	{
		if (column < columns)
			return &(_matrixValues[rows*column]);
		else
			return nullptr;
	}

	const float* operator[] (const unsigned int& column) const
	{
		if (column < columns)
			return &(_matrixValues[rows*column]);
		else
			return nullptr;
	}

	//Matrix& operator=(const Matrix& other)
	//{
	//	for (unsigned int i = 0; i < columns*rows; i++)
	//		_matrixValues[i] = other._matrixValues[i];
	//	return *this;
	//}

	Matrix operator+(const float& value)
	{
		float a[rows*columns] = { 0 };
		for (unsigned int i = 0; i < rows * columns; i++)
		{
			a[i] = _matrixValues[i] + value;
		}
		return { a };
	}

	Matrix operator-(const float& value)
	{
		float a[rows*columns] = { 0 };
		for (unsigned int i = 0; i < rows * columns; i++)
		{
			a[i] = _matrixValues[i] - value;
		}
		return Matrix(a);
	}

	Matrix operator*(const float& value)
	{
		float a[rows*columns] = { 0 };
		for (unsigned int i = 0; i < rows * columns; i++)
		{
			a[i] = _matrixValues[i] * value;
		}
		return { a };
	}

	Matrix operator/(const float& value)
	{
		float a[rows*columns] = { 0 };
		for (unsigned int i = 0; i < rows * columns; i++)
		{
			a[i] = _matrixValues[i] / value;
		}
		return { a };
	}

	Vector<rows> operator*(const Vector<columns>& other)
	{
		Vector<rows> result;
		for (unsigned int i = 0; i < rows; i++)
		{
			float sum = 0;
				for (unsigned int j = 0; j < columns; j++)
				{
					sum += other[j] * _matrixValues[i*rows + j];
				}
			result[i] = sum;
		}
		return result;
	}

	template<unsigned int oColumns>
	Matrix<oColumns, rows> operator*(const Matrix<oColumns, columns>& other) const
	{
		Matrix mat;
		//float array[rows*columns];
		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j <oColumns; j++)
			{
				float sum = 0;
				for (unsigned int k = 0; k < columns; k++)
					sum += this->_matrixValues[i*columns + k] * other[k][j];
				mat[i][j] = sum;
				//array[i*columns+j] = sum;
			}
		}
		return mat;
		//return Matrix(array);
	}

	float Determinant() const
	{
		static_assert(rows == columns, "Determinant cannot be evaluated for the non square matrices");
		return 0.0f;
	}

	void Print()
	{
		std::cout << "[ ";
		for (unsigned int i = 0; i < rows*columns; i++)
			std::cout << this->_matrixValues[i] << " , ";
		std::cout << "]" << std::endl;
	}

	~Matrix()
	{
		//std::cout << "Destructor" << std::endl;
	}
};

typedef Matrix<2, 2> mat2;
typedef Matrix<3, 3> mat3;
typedef Matrix<4, 4> mat4;