#ifndef TARGET_H
#define TARGET_H
#include <SFML/Graphics.hpp>

class Target
{
public:
  double x, y, r;
  double a = 25;

public:
  // Initializer list constructor
  Target(double _x, double _y, double _r)
    : x(_x), y(_y), r(_r){}
  ~Target();
};


Target::~Target()
{
}





#endif //TARGET_H