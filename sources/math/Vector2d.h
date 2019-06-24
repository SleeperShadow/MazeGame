#pragma once
#include <iostream>

struct Vector2D
{
  float x;
  float y;

  Vector2D() = default;
  Vector2D(float x, float y);
  explicit Vector2D(int x, int y);

  friend Vector2D& operator+(Vector2D& v, Vector2D const& other);
  friend Vector2D& operator-(Vector2D& v, Vector2D const& other);
  friend Vector2D& operator*(Vector2D& v, Vector2D const& other);
  friend Vector2D& operator/(Vector2D& v, Vector2D const& other);

  Vector2D& operator+=(Vector2D const& other);
  Vector2D& operator-=(Vector2D const& other);
  Vector2D& operator*=(Vector2D const& other);
  Vector2D& operator/=(Vector2D const& other);

  Vector2D& operator*(int i);
  Vector2D& operator*=(int i);
  Vector2D& zero();

  friend std::ostream& operator<<(std::ostream& os, Vector2D const& v);
  friend std::istream& operator>>(std::istream& is, Vector2D& v);

private:
  Vector2D& add(Vector2D const& other);
  Vector2D& subtract(Vector2D const& other);
  Vector2D& mult(Vector2D const& other);
  Vector2D& div(Vector2D const& other);
};
