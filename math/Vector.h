#pragma once
#include <math.h>

template <unsigned int n>
class Vector
{
private:
	float _vectorValues[n];
public:

	Vector() :_vectorValues()
	{
		for (unsigned int i = 0; i < n; i++)
			_vectorValues[i] = 0;
	}

	Vector(const Vector& other)
	{
		for (unsigned int i = 0; i < n; i++)
			_vectorValues[i] = other._vectorValues[i];
	}

	Vector(const float& value)
	{
		for (unsigned int i = 0; i < n; i++)
			_vectorValues[i] = value;
	}

	Vector(const float vectorValues[n])
	{
		for (unsigned int i = 0; i < n; i++)
		{
			_vectorValues[i] = vectorValues[i];
		}
	}

	
	Vector  operator+(const Vector& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] + other._vectorValues[i];
		return { a };
	}

	Vector  operator-(const Vector& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] - other._vectorValues[i];
		return { a };
	}

	Vector  operator*(const Vector& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] * other._vectorValues[i];
		return { a };
	}

	Vector  operator/(const Vector& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] / other._vectorValues[i];
		return { a };
	}


	Vector  operator+(const float& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] + other;
		return { a };
	}

	Vector  operator-(const float& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] - other;
		return { a };
	}

	Vector  operator*(const float& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] * other;
		return { a };
	}

	Vector  operator/(const float& other)
	{
		float a[n] = { 0 };
		for (unsigned int i = 0; i < n; i++)
			a[i] = _vectorValues[i] / other;
		return { a };
	}

	inline Vector  operator-() { return Vector() - (*this); }

	inline Vector  Direction() const { return (*this) / Magnitude(); }
		
	inline float& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const float& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	float  DotProduct(const Vector& other)
	{
		float sum = 0.0f;
		for (unsigned int i = 0; i < n; i++)
			sum += _vectorValues[i] * other._vectorValues[i];
		return sum;
	}

	float Magnitude() const
	{
		float sum = 0.0f;
		for (unsigned int i = 0; i < n; i++)
			sum += _vectorValues[i] * _vectorValues[i];
		return sqrtf(sum);
	}


};

typedef Vector<2> vec2;
typedef Vector<3> vec3;
typedef Vector<4> vec4;

template<>
class Vector<4>
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
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}

	Vector(const float vectorValues[4])
	{
		x = vectorValues[0];
		y = vectorValues[1];
		z = vectorValues[2];
		w = vectorValues[3];
	}

	Vector(const Vector& other)
	{
		for (unsigned int i = 0; i < 4; i++)
			_vectorValues[i] = other._vectorValues[i];
	}

	Vector(const float& _x, const float& _y, const float& _z, const float& _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	Vector(const Vector<3>& other, const float& _w);

	inline Vector operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z + other.z, w + other.w); }

	inline Vector operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z, w - other.w); }

	inline Vector operator*(const Vector& other) const { return Vector(x * other.x, y * other.y, z * other.z, w * other.w); }

	inline Vector operator/(const Vector& other) const { return Vector(x / other.x, y / other.y, z / other.z, w / other.w); }


	inline Vector operator+(const float& other) const { return Vector(x + other, y + other, z + other, w + other); }

	inline Vector operator-(const float& other) const { return Vector(x - other, y - other, z - other, w - other); }

	inline Vector operator*(const float& other) const { return Vector(x * other, y * other, z * other, w * other); }

	inline Vector operator/(const float& other) const { return Vector(x / other, y / other, z / other, w / other); }

	inline float& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const float& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector operator-() { return Vector() - (*this); }

	inline Vector Direction() const { return Vector((*this) / Magnitude()); }

	inline float DotProduct(const Vector& other) const { return ((x * other.x) + (y * other.y) + (z * other.z) + (w * other.w)); }

	inline float Magnitude() const { return sqrtf((x*x) + (y*y) + (z*z) + (w*w)); }

	Vector<3> ToVec3() const;
};


template<>
class Vector<3>
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
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector(const float vectorValues[3])
	{
		x = vectorValues[0];
		y = vectorValues[1];
		z = vectorValues[2];
	}

	Vector(const Vector& other)
	{
		for (unsigned int i = 0; i < 3; i++)
			_vectorValues[i] = other._vectorValues[i];
	}

	Vector(const float& _x, const float& _y, const float& _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vector(const Vector<2>& other, const float& _z);

	inline Vector  operator+(const Vector& other) const { return Vector(x + other.x, y + other.y, z + other.z); }

	inline Vector  operator-(const Vector& other) const { return Vector(x - other.x, y - other.y, z - other.z); }

	inline Vector  operator*(const Vector& other) const { return Vector(x * other.x, y * other.y, z * other.z); }

	inline Vector  operator/(const Vector& other) const { return Vector(x / other.x, y / other.y, z / other.z); }


	inline Vector  operator+(const float& other) const { return Vector(x + other, y + other, z + other); }

	inline Vector  operator-(const float& other) const { return Vector(x - other, y - other, z - other); }

	inline Vector  operator*(const float& other) const { return Vector(x * other, y * other, z * other); }

	inline Vector  operator/(const float& other) const { return Vector(x / other, y / other, z / other); }

	inline float& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const float& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector  operator-() { return Vector() - (*this); }

	inline Vector Direction() const { return Vector((*this) / Magnitude()); }

	inline float  DotProduct(const Vector& other) const { return ((x*other.x) + (y*other.y) + (z*other.z)); }

	Vector CrossProduct(const Vector& other) const
	{
		float _x, _y, _z;
		_x = y * other.z - z * other.y;
		_y = z * other.x - x * other.z;
		_z = x * other.y - y * other.x;
		return { _x, _y, _z };
	}

	inline float  Magnitude() const { return sqrtf((x*x) + (y*y) + (z*z)); }

	Vector<2> ToVec2() const;
};


template<>
class Vector<2>
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
		x = 0.0f;
		y = 0.0f;
	}

	Vector(const float vectorValues[2])
	{
		x = vectorValues[0];
		y = vectorValues[1];
	}

	Vector(const Vector& other)
	{
		for (unsigned int i = 0; i < 2; i++)
			_vectorValues[i] = other._vectorValues[i];
	}

	Vector(const float& _x, const float& _y)
	{
		x = _x;
		y = _y;
	}

	inline Vector  operator+(const Vector& other) const { return Vector(x + other.x, y + other.y); }

	inline Vector  operator-(const Vector& other) const { return Vector(x - other.x, y - other.y); }

	inline Vector  operator*(const Vector& other) const { return Vector(x * other.x, y * other.y); }

	inline Vector  operator/(const Vector& other) const { return Vector(x / other.x, y / other.y); }


	inline Vector  operator+(const float& other) const { return Vector(x + other, y + other); }

	inline Vector  operator-(const float& other) const { return Vector(x - other, y - other); }

	inline Vector  operator*(const float& other) const { return Vector(x * other, y * other); }

	inline Vector  operator/(const float& other) const { return Vector(x / other, y / other); }

	inline float& operator[](const unsigned int& index) { return _vectorValues[index]; }
	inline const float& operator[](const unsigned int& index) const { return _vectorValues[index]; }

	inline Vector operator-() { return Vector() - (*this); }

	inline Vector Direction() const { return Vector((*this) / Magnitude()); }

	inline float  DotProduct(const Vector& other) const { return ((x*other.x) + (y*other.y)); }

	inline Vector<3> CrossProduct(const Vector& other) const { return Vector<3>(0.0f, 0.0f, ((x*other.y) - (y*other.x))); }

	inline float  Magnitude() const { return sqrtf((x*x) + (y*y)); }
};