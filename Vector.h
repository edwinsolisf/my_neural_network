#pragma once

#include <iostream>
#include <cmath>
const int null = 0;
template<typename _T, unsigned int _size>
class Vector
{
private:
	_T _vectorValues[_size];

public:
	Vector()
	{
		memset(_vectorValues, 0, _size * sizeof(_T));
	}

	Vector(const _T arrayValues[_size])
	{
		memcpy(_vectorValues, arrayValues, _size * sizeof(_T));
	}

	Vector(const _T& value)
	{
		for (unsigned int i = 0; i < _size; i++)
			_vectorValues[i] = value;
	}

	Vector(const Vector& other)
	{
		memcpy(_vectorValues, other._vectorValues, _size * sizeof(_T));
	}

	Vector operator+(const _T& value) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] + value;
		return Vector(temp);
	}

	Vector operator-(const _T& value) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] - value;
		return Vector(temp);
	}

	Vector operator*(const _T& value) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] * value;
		return Vector(temp);
	}

	Vector operator/(const _T& value) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] / value;
		return Vector(temp);
	}

	Vector operator+(const Vector& other) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] + other._vectorValues[i];
		return Vector(temp);
	}

	Vector operator-(const Vector& other) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] - other._vectorValues[i];
		return Vector(temp);
	}

	Vector operator*(const Vector& other) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] * other._vectorValues[i];
		return Vector(temp);
	}

	Vector operator/(const Vector& other) const
	{
		_T temp[_size];
		for (unsigned int i = 0; i < _size; i++)
			temp[i] = _vectorValues[i] / other._vectorValues[i];
		return Vector(temp);
	}

	inline Vector operator-() const { return Vector() - (*this); }
	inline _T& operator[](const unsigned int& index) { return index < _size ? _vectorValues[index] : (_T&)null; }
	inline const _T& operator[](const unsigned int& index) const { return index < _size ? _vectorValues[index] : (_T&)null; }
	
	_T DotProduct(const Vector& other) const
	{
		_T temp = 0;
		for (unsigned int i = 0; i < _size; i++)
			temp += _vectorValues[i] * other._vectorValues[i];
		return temp;
	}

	inline _T Magnitude() const { return sqrt(DotProduct(*this)); }
	inline Vector Direction() const { return (*this) / Magnitude(); }

	void ApplyToVector(void(*function)(_T&))
	{
		for (unsigned int i = 0; i < _size; i++)
			function(_vectorValues[i]);
	}
};

typedef Vector<float, 2> vec2;
typedef Vector<float, 3> vec3;
typedef Vector<float, 4> vec4;

typedef Vector<int, 2> vec2i;
typedef Vector<int, 3> vec3i;
typedef Vector<int, 4> vec4i;

template<typename _T>
class Vector<_T, 4>
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float _vectorValues[4];
		};
	};

	Vector()
	{
		memset(_vectorValues, 0, 4 * sizeof(_T));
	}

	Vector(const _T arrayValues[4])
	{
		memcpy(_vectorValues, arrayValues, 4 * sizeof(_T));
	}

	Vector(const Vector& other)
	{
		memcpy(_vectorValues, other._vectorValues, 4 * sizeof(_T));
	}

	Vector(const _T& _x, const _T& _y, const _T& _z, const _T& _w)
		:x(_x), y(_y), z(_z), w(_w)
	{
	}

	Vector(const Vector<_T, 3>& other, const _T& _w);

	inline Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }
	inline Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }
	inline Vector operator*(const Vector& other) const { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }
	inline Vector operator/(const Vector& other) const { return Vector(x / other.x, y / other.y, z / other.z, w / other.w); }

	inline Vector operator+(const _T& value) const { return Vector(x + value, y + value, z + value, w + value); }
	inline Vector operator-(const _T& value) const { return Vector(x - value, y - value, z - value, w - value); }
	inline Vector operator*(const _T& value) const { return Vector(x * value, y * value, z * value, w * value); }
	inline Vector operator/(const _T& value) const { return Vector(x / value, y / value, z / value, w / value); }

	inline Vector operator-() { return Vector() - (*this); }
	inline _T& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const _T& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector Direction() const { return (*this) / Magnitude(); }
	inline _T DotProduct(const Vector& other) const { return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w); }
	inline _T Magnitude() const { return sqrt((x*x) + (y*y) + (z*z) + (w*w)); }

	Vector<_T, 3> ToVec3() const;

	void ApplyToVector(void(*function)(_T&))
	{
		for (unsigned int i = 0; i < 4; i++)
			function(_vectorValues[i]);
	}
};

template<typename _T>
class Vector<_T, 3>
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		struct
		{
			float _vectorValues[3];
		};
	};

	Vector()
	{
		memset(_vectorValues, 0, 3 * sizeof(_T));
	}

	Vector(const _T arrayValues[3])
	{
		memcpy(_vectorValues, arrayValues, 3 * sizeof(_T));
	}

	Vector(const Vector& other)
	{
		memcpy(_vectorValues, other._vectorValues, 3 * sizeof(_T));
	}

	Vector(const _T& _x, const _T& _y, const _T& _z)
		:x(_x), y(_y), z(_z)
	{
	}

	Vector(const Vector<_T, 2>& other, const _T& _z);

	inline Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z + other.z); }
	inline Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z); }
	inline Vector operator*(const Vector& other) const { return Vector(x * other.x, y * other.y, z * other.z); }
	inline Vector operator/(const Vector& other) const { return Vector(x / other.x, y / other.y, z / other.z); }

	inline Vector operator+(const _T& value) const { return Vector(x + value, y + value, z + value); }
	inline Vector operator-(const _T& value) const { return Vector(x - value, y - value, z - value); }
	inline Vector operator*(const _T& value) const { return Vector(x * value, y * value, z * value); }
	inline Vector operator/(const _T& value) const { return Vector(x / value, y / value, z / value); }

	inline Vector operator-() { return Vector() - (*this); }
	inline _T& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const _T& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector Direction() const { return (*this) / Magnitude(); }
	inline _T DotProduct(const Vector& other) const { return (x * other.x) + (y * other.y) + (z * other.z); }
	inline _T Magnitude() const { return sqrt((x*x) + (y*y) + (z*z)); }

	inline Vector CrossProduct(const Vector& other) const { return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x); }

	Vector<_T, 2> ToVec2() const;

	void ApplyToVector(void(*function)(_T&))
	{
		for (unsigned int i = 0; i < 3; i++)
			function(_vectorValues[i]);
	}
};

template<typename _T>
class Vector<_T, 2>
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		struct
		{
			float _vectorValues[2];
		};
	};

	Vector()
	{
		memset(_vectorValues, 0, 2 * sizeof(_T));
	}

	Vector(const _T arrayValues[2])
	{
		memcpy(_vectorValues, arrayValues, 2 * sizeof(_T));
	}

	Vector(const Vector& other)
	{
		memcpy(_vectorValues, other._vectorValues, 2 * sizeof(_T));
	}

	Vector(const _T& _x, const _T& _y)
		:x(_x), y(_y)
	{
	}

	inline Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); }
	inline Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); }
	inline Vector operator*(const Vector& other) const { return Vector(x * other.x, y * other.y); }
	inline Vector operator/(const Vector& other) const { return Vector(x / other.x, y / other.y); }

	inline Vector operator+(const _T& value) const { return Vector(x + value, y + value); }
	inline Vector operator-(const _T& value) const { return Vector(x - value, y - value); }
	inline Vector operator*(const _T& value) const { return Vector(x * value, y * value); }
	inline Vector operator/(const _T& value) const { return Vector(x / value, y / value); }

	inline Vector operator-() { return Vector() - (*this); }
	inline _T& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const _T& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector Direction() const { return (*this) / Magnitude(); }
	inline _T DotProduct(const Vector& other) const { return (x * other.x) + (y * other.y); }
	inline _T Magnitude() const { return sqrt((x*x) + (y*y)); }

	inline Vector<_T, 3> CrossProduct(const Vector& other) const { return Vector<_T, 3>(0, 0, x * other.y - y * other.x); }

	void ApplyToVector(void(*function)(_T&))
	{
		for (unsigned int i = 0; i < 2; i++)
			function(_vectorValues[i]);
	}
};