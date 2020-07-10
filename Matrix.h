#pragma once

#include <iostream>
#include "Vector.h"

template<typename _T, unsigned int _columns, unsigned int _rows>
class Matrix
{
private:
	_T _matrixValues[_columns * _rows];

public:
	Matrix()
	{
		memset(_matrixValues, 0, _columns * _rows * sizeof(_T));
	}

	Matrix(const _T arrayValues[_rows*_columns])
	{
		memcpy(_matrixValues, arrayValues, _columns * _rows * sizeof(_T));
	}

	Matrix(const Matrix& other)
	{
		memcpy(_matrixValues, other._matrixValues, _columns * _rows * sizeof(_T));
	}

	inline _T* operator[](const unsigned int& rowIndex) { return rowIndex < _rows ? &(_matrixValues[rowIndex * _columns]) : nullptr; }
	inline const _T* operator[](const unsigned int& columnIndex) const { return columnIndex < _columns ? &(_matrixValues[columnIndex * _rows]) : nullptr; }

	Matrix operator+(const _T& value) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] + value;
		return Matrix(temp);
	}

	Matrix operator-(const _T& value) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] - value;
		return Matrix(temp);
	}

	/*
	Matrix operator*(const _T& value) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] * value;
		return Matrix(temp);
	}
	*/

	Matrix Multiply(const _T& value) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] * value;
		return Matrix(temp);
	}

	Matrix operator/(const _T& value) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] / value;
		return Matrix(temp);
	}

	Matrix operator+(const Matrix& other) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] + other._matrixValues[i];
		return Matrix(temp);
	}

	Matrix operator-(const Matrix& other) const
	{
		_T temp[_columns*_rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] - other._matrixValues[i];
		return Matrix(temp);
	}

	/*
	Matrix operator*(const Matrix& other) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] * other._matrixValues[i];
		return Matrix(temp);
	}
	*/

	Matrix operator/(const Matrix& other) const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _columns * _rows; i++)
			temp[i] = _matrixValues[i] / other._matrixValues[i];
		return Matrix(temp);
	}

	Matrix<_T, _rows, _columns> Transpose() const
	{
		_T temp[_columns * _rows];
		for (unsigned int i = 0; i < _rows; i++)
			for (unsigned int j = 0; j < _columns; j++)
				temp[i + j * _rows] = _matrixValues[i * _columns + j];
		return Matrix<_T, _rows, _columns>(temp);
	}

	template<unsigned int o_columns>
	Matrix<_T, o_columns, _rows> operator*(const Matrix<_T, o_columns, _columns>& other) const
	{
		_T temp[o_columns * _rows];
		for (unsigned int i = 0; i < _rows; i++)
		{
			for (unsigned int j = 0; j < o_columns; j++)
			{
				_T sum = 0;
				for (unsigned int k = 0; k < _columns; k++)
					sum += _matrixValues[i*_columns + k] * other._matrixValues[k * _columns + j];
				temp[i * o_columns + j] = sum;
			}
		}
		return Matrix(temp);
	}

	Matrix<_T, _columns - 1, _rows - 1> SubMatrix(const unsigned int& deleteColumn, const unsigned int& deleteRow) const
	{
		if (!((deleteColumn < _columns) || (deleteRow < _rows)))
			return Matrix<_T, _columns - 1, _rows - 1>();

		_T temp[(_columns - 1) * (_rows - 1)];

		unsigned int sequence[(_columns - 1) * (_rows - 1)];
		unsigned int missing = (_columns - 1) * (_rows - 1);
		unsigned int _i = 0;
		while (missing)
		{
			if (!((_i / _columns) == deleteRow) && !((_i % _columns) == deleteColumn))
			{
				sequence[(_columns - 1) * (_rows - 1) - missing] = _i;
				missing--;
			}
			_i++;
		}

		for (unsigned int i = 0; i < (_columns - 1) * (_rows - 1); i++)
			temp[i] = _matrixValues[sequence[i]];
		return Matrix < _T, _columns - 1, _rows - 1>(temp);
	}

	template<typename _T, unsigned int _columns, unsigned int _rows>
	friend _T Determinant(const Matrix<_T, _columns, _rows>& matrix);
	/*{
		static_assert(_columns == _rows, "Determinant cannot be evaluated for the non square matrices");
		_T temp = 0;
		for (unsigned int i = 0; i < _columns; i++)
		{
			if (i % 2)
				temp -= _matrixValues[i] * SubMatrix(i, 0).Determinant();
			else
				temp += _matrixValues[i] * SubMatrix(i, 0).Determinant();
		}
		return temp;
	}*/

	Vector<_T, _rows> operator*(const Vector<_T, _columns>& other)
	{
		_T temp[_rows];
		for (unsigned int i = 0; i < _rows; i++)
		{
			float sum = 0;
			for (unsigned int j = 0; j < _columns; j++)
				sum += other[j] * _matrixValues[i * _columns + j];
			temp[i] = sum;
		}
		return Vector<_T, _rows>(temp);
	}

	Vector<_T, _rows> GetColumnVector(const unsigned int& column) const
	{
		if (column < _columns)
		{
			_T temp[_rows];
			for (unsigned int i = 0; i < _rows; i++)
				temp[i] = _matrixValues[i*_columns + column];
			return Vector<_T, _rows>(temp);
		}
		else
			return Vector<_T, _rows>();
	}

	void SetColumnVector(const unsigned int& column, const Vector<_T, _rows>& vec)
	{
		for (unsigned int i = 0; i < _rows; i++)
			_matrixValues[i*_columns + column] = vec[i];
	}

	inline void SetRowVector(const unsigned int& row, const Vector<_T, _columns>& vec)
	{
		memcpy(&_matrixValues[row*_columns], &vec[0], _columns * sizeof(_T));
	}

	inline Vector<_T, _columns> GetRowVector(const unsigned int& row) const
	{
		return row < _rows ? Vector<_T, _columns>(&_matrixValues[row*_columns]) : Vector<_T, _columns>();
	}

	void ApplyToMatrix(void(*function)(_T&))
	{
		for (unsigned int i = 0; i < _columns * _rows; i++)
			function(_matrixValues[i]);
	}

	void ApplyToMatrixRow(const unsigned int& row, void(*function)(_T&))
	{
		if(row < _rows)
			for (unsigned int i = 0; i < _columns; i++)
				function(_matrixValues[row*_columns + i]);
	}

	void ApplyToMatrixColumn(const unsigned int& column, void(*function)(_T&))
	{
		if (column < _columns)
			for (unsigned int i = 0; i < _rows; i++)
				function(_matrixValues[i*_columns + column]);
	}
};

typedef Matrix<float, 2, 2> mat2;
typedef Matrix<float, 3, 3> mat3;
typedef Matrix<float, 4, 4> mat4;

typedef Matrix<int, 2, 2> mat2i;
typedef Matrix<int, 3, 3> mat3i;
typedef Matrix<int, 4, 4> mat4i;

template<typename _T, unsigned int _columns, unsigned int  _rows>
_T Determinant(const Matrix<_T, _columns, _rows>& matrix)
{
	static_assert(_columns == _rows, "Determinant cannot be evaluated for the non square matrices");

	_T temp = 0;
	for (unsigned int i = 0; i < _columns; i++)
	{
		if (i % 2)
			temp -= matrix._matrixValues[i] * Determinant(matrix.SubMatrix(i, 0));
		else
			temp += matrix._matrixValues[i] * Determinant(matrix.SubMatrix(i, 0));
	}
	return temp;
}

template<typename _T>
inline _T Determinant(const Matrix<_T, 2, 2>& matrix)
{
	return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}