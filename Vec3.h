#pragma once
template <class T>
class Vec3
{
public:
	T x, y, z;
	T& r = x;
	T& g = y;
	T& b = z;

	Vec3()
		: x(0),
		y(0),
		z(0)
	{}

	Vec3(T p_x, T p_y, T p_z)
		: x(p_x),
		y(p_y),
		z(p_z)
	{}

	Vec3(const Vec3<T>& vec)
		: x(vec.x),
		y(vec.y),
		z(vec.z)
	{}

	Vec3(const Vec3<T>&& vec)
		: x(vec.x),
		y(vec.y),
		z(vec.z)
	{}

	inline Vec3<T> operator=(const Vec3<T>& vec)
	{
		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	inline Vec3<T> operator-() const
	{
		return Vec3<T>(-x, -y, -z);
	}

	inline Vec3<T> operator+=(const Vec3<T>& vec)
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		return *this;
	}

	inline Vec3<T> operator-=(const Vec3<T>& vec)
	{
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;

		return *this;
	}

	inline Vec3<T> operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	inline Vec3<T> operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	inline float dot(const Vec3<T>& vec) const
	{
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	inline Vec3<T> cross(const Vec3<T>& vec) const
	{
		return Vec3<T>(y * vec.z - z * vec.y,
			           x * vec.z - z * vec.x,
			           x * vec.y - y * vec.x);
	}

	inline float GetMagnitude()
	{
		return sqrt(GetSquaredMagnitude());
	}

	inline float GetSquaredMagnitude()
	{
		return x * x + y * y + z * z;
	}

	inline Vec3<T>& Normalize()
	{
		*this /= (*this).GetMagnitude();

		return *this;
	}
};

typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

template <typename T>
inline Vec3<T> operator+(const Vec3<T>& vec1, const Vec3<T>& vec2)
{
	return Vec3<T>(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

template <typename T>
inline Vec3<T> operator-(const Vec3<T>& vec1, const Vec3<T>& vec2)
{
	return Vec3<T>(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

template <typename T>
inline Vec3<T> operator*(const float scalar, const Vec3<T>& vec)
{
	return Vec3<T>(vec.x * scalar,
				   vec.y * scalar,
	               vec.z * scalar);
}

template <typename T>
inline Vec3<T> operator*(const Vec3<T>& vec, const float scalar)
{
	return Vec3<T>(vec.x * scalar,
		           vec.y * scalar,
		           vec.z * scalar);
}

template <typename T>
inline Vec3<T> operator/(const float scalar, const Vec3<T>& vec)
{
	return Vec3<T>(vec.x / scalar,
				   vec.y / scalar,
	               vec.z / scalar);
}

template <typename T>
inline Vec3<T> operator/(const Vec3<T>& vec, const float scalar)
{
	return Vec3<T>(vec.x / scalar,
		           vec.y / scalar,
		           vec.z / scalar);
}