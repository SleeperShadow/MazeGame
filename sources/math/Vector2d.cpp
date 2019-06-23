#include "Vector2d.h"

Vector2D::Vector2D(float _x, float _y)
  : x(_x)
  , y(_y)
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
