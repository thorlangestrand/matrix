#ifndef VEC2
#define VEC2
#include <stdint.h>
#include <math.h>

template <typename T = double>
class vector2
{
public:
  T x, y;
private:
  // Magnitude
  double mag(vector2& v) { return (sqrt(v.x * v.x + v.y * v.y)); }

public:

  // Operators
  void operator = (vector2& v) { this->x = v.x; this->y = v.y; };

  // Unary minus
  vector2 operator - () const { return vector2(-this->x, -this->y); }


  // Prefix increment
  vector2 operator ++ () { this->x++; this->y++; return *this; }
  // Prefix decrement
  vector2 operator -- () { this->x--; this->y--; return *this; }

  // Postfix increment
  void operator ++ (int) { this->x++; this->y++; }
  // Postfix decrement
  void operator -- (int) { this->x--; this->y--; }

  bool operator == (vector2& v) { return (this->x == v.x && this->y == v.y); }

  // Checks magnitude
  bool operator < (vector2& v) { return (this->mag() < this->mag(v)); }
  bool operator <= (vector2& v) { return (this->mag() <= this->mag(v)); }
  bool operator > (vector2& v) { return (this->mag() > this->mag(v)); }
  bool operator >= (vector2& v) { return (this->mag() >= this->mag(v)); }

  vector2 operator + (vector2& v) { return vector2(this->x + v.x, this->y + v.y); }
  vector2& operator += (vector2 v) { this->x += v.x; this->y += v.y; return *this; }

  vector2 operator + (T i) { return vector2(this->x + i, this->y + i); }
  vector2& operator += (T i) { this->x += i; this->y += i; return *this; }

  vector2 operator - (vector2& v) { return vector2(this->x - v.x, this->y - v.y); }
  vector2& operator -= (vector2 v) { this->x -= v.x; this->y -= v.y; return *this; }

  vector2 operator - (T i) { return vector2(this->x - i, this->y - i); }
  vector2& operator -= (T i) { this->x -= i; this->y -= i; return *this; }

  vector2 operator * (vector2& v) { return vector2(this->x * v.x, this->y * v.y); }
  vector2& operator *= (vector2 v) { this->x *= v.x; this->y *= v.y; return *this; }

  vector2 operator * (T i) { return vector2(this->x * i, this->y * i); }
  vector2& operator *= (T i) { this->x *= i; this->y *= i; return *this; }

  vector2 operator / (vector2& v) { return vector2(this->x / v.x, this->y / v.y); }
  vector2& operator /= (vector2 v) { this->x /= v.x; this->y /= v.y; return *this; }

  vector2 operator / (T i) { return vector2(this->x / i, this->y / i); }
  vector2& operator /= (T i) { this->x /= i; this->y /= i; return *this; }

  vector2 operator ^ (vector2& v) { return vector2(pow(this->x, v.x), pow(this->y, v.y)); }
  vector2& operator ^= (vector2 v) { this->x = pow(this->x, v.x);this->y = pow(this->y, v.y); return *this; }

  vector2 operator ^ (T i) { return vector2(pow(this->x, i), pow(this->y, i)); }
  vector2& operator ^= (T i) { this->x = pow(this->x, i);this->y = pow(this->y, i); return *this; }

  friend std::ostream& operator << (std::ostream& out, vector2 v) { out << "{ " << v.x << "," << v.y << " }"; return out; }

  // Methods
  inline double dot(vector2& v) { return this->x * v.x + this->y + v.y; }
  double mag() { return (sqrt(this->x * this->x + this->y * this->y)); }
  static inline double dot(vector2& v1, vector2& v2) { return v1.x * v2.x + v1.y * v2.y; }

  // Constructor
  vector2() {};
  vector2(T _x, T _y) { this->x = _x; this->y = _y; };
  ~vector2() {};

};

// If you for some reason wanted to use it with floats or ints,
// you could, this is just default
using vec2 = vector2<double>;



#endif //VEC2