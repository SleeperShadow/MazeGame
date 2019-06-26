#include "Vector2d.h"
#include <cmath>

Vector2D::Vector2D(float _x, float _y)
  : x(_x)
  , y(_y)
{}

Vector2D::Vector2D(int _x, int _y)
  : x(static_cast<float>(_x))
  , y(static_cast<float>(_y))
{}

Vector2D::Vector2D(unsigned int x, unsigned int y)
  : Vector2D(static_cast<float>(x), static_cast<float>(y))
{}

Vector2D&
operator+(Vector2D& v, Vector2D const& other)
{
  return v.add(other);
}

Vector2D&
operator-(Vector2D& v, Vector2D const& other)
{
  return v.subtract(other);
}

Vector2D& operator*(Vector2D& v, Vector2D const& other)
{
  return v.mult(other);
}

Vector2D&
operator/(Vector2D& v, Vector2D const& other)
{
  return v.div(other);
}

std::ostream&
operator<<(std::ostream& os, Vector2D const& v)
{
  os << "( " << v.x << ", " << v.y << " )";
  return os;
}

std::istream&
operator>>(std::istream& is, Vector2D& v)
{
  is >> v.x >> v.y;
  return is;
}

Vector2D&
Vector2D::operator+=(Vector2D const& other)
{
  return add(other);
}

Vector2D&
Vector2D::operator-=(Vector2D const& other)
{
  return subtract(other);
}

Vector2D&
Vector2D::operator*=(Vector2D const& other)
{
  return mult(other);
}

Vector2D&
Vector2D::operator/=(Vector2D const& other)
{
  return div(other);
}

Vector2D& Vector2D::operator*(int i)
{
  x *= i;
  y *= i;

  return *this;
}

Vector2D&
Vector2D::operator*=(int i)
{
  return operator*(i);
}

Vector2D&
Vector2D::zero()
{
  return Vector2D::operator*(0);
}

double Vector2D::length() const
{
    return sqrt(x*x + y* y);
}

double
Vector2D::angle(Vector2D const& other) const
{
  auto dot = x * other.x + y * other.y;
  auto len1 = length();
  auto len2 = other.length();

  auto cos = dot / (len1 * len2);
  auto sin = 1.0 - cos* cos; 

  return asin(sin) * 180 / 3.14f;
}

Vector2D&
Vector2D::add(Vector2D const& other)
{
  x += other.x;
  y += other.y;
  return *this;
}

Vector2D&
Vector2D::subtract(Vector2D const& other)
{
  x -= other.x;
  y -= other.y;
  return *this;
}

Vector2D&
Vector2D::mult(Vector2D const& other)
{
  x *= other.x;
  y *= other.y;
  return *this;
}

Vector2D&
Vector2D::div(Vector2D const& other)
{
  x /= other.x;
  y /= other.y;
  return *this;
}
