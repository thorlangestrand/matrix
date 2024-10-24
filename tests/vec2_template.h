#ifndef VEC2
#define VEC2
#include <stdint.h>
#include <math.h>

template <typename T = double>
class vec2
{
public:
  T x, y;
private:
  // Magnitude
  double mag(vec2& v) { return (sqrt(v.x * v.x + v.y * v.y)); }

public:

  // Operators
  void operator = (vec2& v) { this->x = v.x; this->y = v.y; };

  // Unary minus
  vec2 operator - () const { return vec2(-this->x, -this->y); }


  // Prefix increment
  vec2 operator ++ () { this->x++; this->y++; return *this; }
  // Prefix decrement
  vec2 operator -- () { this->x--; this->y--; return *this; }

  // Postfix increment
  void operator ++ (int) { this->x++; this->y++; }
  // Postfix decrement
  void operator -- (int) { this->x--; this->y--; }

  bool operator == (vec2& v) { return (this->x == v.x && this->y == v.y); }

  // Checks magnitude
  bool operator < (vec2& v) { return (this->mag() < this->mag(v)); }
  bool operator <= (vec2& v) { return (this->mag() <= this->mag(v)); }
  bool operator > (vec2& v) { return (this->mag() > this->mag(v)); }
  bool operator >= (vec2& v) { return (this->mag() >= this->mag(v)); }

  vec2 operator + (vec2& v) { return vec2(this->x + v.x, this->y + v.y); }
  vec2& operator += (vec2 v) { this->x += v.x; this->y += v.y; return *this; }

  vec2 operator + (T i) { return vec2(this->x + i, this->y + i); }
  vec2& operator += (T i) { this->x += i; this->y += i; return *this; }

  vec2 operator - (vec2& v) { return vec2(this->x - v.x, this->y - v.y); }
  vec2& operator -= (vec2 v) { this->x -= v.x; this->y -= v.y; return *this; }

  vec2 operator - (T i) { return vec2(this->x - i, this->y - i); }
  vec2& operator -= (T i) { this->x -= i; this->y -= i; return *this; }

  vec2 operator * (vec2& v) { return vec2(this->x * v.x, this->y * v.y); }
  vec2& operator *= (vec2 v) { this->x *= v.x; this->y *= v.y; return *this; }

  vec2 operator * (T i) { return vec2(this->x * i, this->y * i); }
  vec2& operator *= (T i) { this->x *= i; this->y *= i; return *this; }

  vec2 operator / (vec2& v) { return vec2(this->x / v.x, this->y / v.y); }
  vec2& operator /= (vec2 v) { this->x /= v.x; this->y /= v.y; return *this; }

  vec2 operator / (T i) { return vec2(this->x / i, this->y / i); }
  vec2& operator /= (T i) { this->x /= i; this->y /= i; return *this; }

  vec2 operator ^ (vec2& v) { return vec2(pow(this->x, v.x), pow(this->y, v.y)); }
  vec2& operator ^= (vec2 v) { this->x = pow(this->x, v.x);this->y = pow(this->y, v.y); return *this; }

  vec2 operator ^ (T i) { return vec2(pow(this->x, i), pow(this->y, i)); }
  vec2& operator ^= (T i) { this->x = pow(this->x, i);this->y = pow(this->y, i); return *this; }

  friend std::ostream& operator << (std::ostream& out, vec2 v) { out << "{ " << v.x << "," << v.y << " }"; return out; }

  // Methods
  inline double dot(vec2& v) { return this->x * v.x + this->y + v.y; }
  double mag() { return (sqrt(this->x * this->x + this->y * this->y)); }
  static inline double dot(vec2& v1, vec2& v2) { return v1.x * v2.x + v1.y * v2.y; }

  // Constructor
  vec2() {};
  vec2(T _x, T _y) { this->x = _x; this->y = _y; };
  ~vec2() {};

};





#endif //VEC2