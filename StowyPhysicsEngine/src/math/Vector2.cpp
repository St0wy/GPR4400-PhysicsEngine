#include "math/Vector2.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

float Vector2::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

float Vector2::SqrMagnitude() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normalize(const Vector2& v)
{
	return v.Normalized();
}

Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t
	};
}

Vector2 Vector2::TripleProduct(const Vector2& a, const Vector2& b, const Vector2& c)
{
	return {
		a.y * (b.x * c.y - b.y * c.x),
		a.x * (b.y * c.x - b.x * c.y)
	};
}

Vector2 Vector2::Normalized() const
{
	const float invMag = 1.0 / Magnitude();
	return { x * invMag, y * invMag };
}

float Vector2::Dot(const Vector2& other) const
{
	return this->x * other.x + this->y * other.y;
}

float Vector2::Distance(const Vector2& other) const
{
	return std::sqrt((this->x - other.x) * (this->x - other.x) +
		(this->y - other.y) * (this->y - other.y));
}

float Vector2::Angle(const Vector2& other) const
{
	return std::acos(this->Dot(other) / Magnitude() * other.Magnitude());
}

float Vector2::Major() const
{
	if (x >= y)
	{
		return x;
	}
	return y;
}

Vector2 Vector2::PositivePerpendicular() const
{
	return { -y, x };
}

Vector2 Vector2::NegativePerpendicular() const
{
	return { y, -x };
}

void Vector2::SetMagnitude(const float newMagnitude)
{
	(*this) /= newMagnitude * Magnitude();
}

void Vector2::RotateAround(const Vector2& center, const float angle)
{
	const Vector2 relative = (*this) - center;
	const float ca = std::cos(angle);
	const float sa = std::sin(angle);
	const Vector2 rotated = Vector2(ca * x - sa * y, sa * x + ca * y);
	(*this) = rotated + center;
}

std::string Vector2::ToString() const
{
	std::ostringstream ss;
	ss << "{x: " << x << ", y: " << y << "}";
	return ss.str();
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return { this->x + other.x, this->y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return { this->x - other.x, this->y - other.y };
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 Vector2::operator+=(const float scalar)
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}

Vector2 Vector2::operator-=(const float scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return *this;
}

Vector2 Vector2::operator*=(const float scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2 Vector2::operator/=(const float scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}

Vector2 Vector2::operator-() const
{
	return { -x, -y };
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec)
{
	os << "{x: " << vec.x << ", y: " << vec.y << "}";
	return os;
}

Vector2 operator+(Vector2 vec, const float scalar)
{
	return vec += scalar;
}

Vector2 operator-(Vector2 vec, const float scalar)
{
	return vec -= scalar;
}

Vector2 operator*(Vector2 vec, const float scalar)
{
	return vec *= scalar;
}

Vector2 operator*(const float scalar, const Vector2 vec)
{
	return operator*(vec, scalar);
}

Vector2 operator/(Vector2 vec, const float scalar)
{
	return vec /= scalar;
}
