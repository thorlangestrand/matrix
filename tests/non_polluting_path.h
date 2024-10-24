#ifndef PATH_H
#define PATH_H

#include "Line.h"


class Path
{
private:

public:
  // A path is comprised of many points
  // Line between each point leading to the next
  // If enclosed path, last point leads to first
  std::vector<Line> path;

  // Debug, points
  std::vector<vec2> points;

  /**
   * @brief
   *
   * void draw();
   * void rotate(angle); Rotate around centre try to keep everything intact
   * void rotate(pivot); Rotate around point try to keep everything intact
   *
   * 300 200 600 400
   * 500 400 800 900
   * 800 900 300 200
   *
   *
   *    7
   * 36   48
   * 15   29
   *
   *
   *
   *
   *
   */

  Path();
  Path(std::initializer_list<vec2> _v);
  void draw(sf::RenderTarget& w, double angle = 0, vec2 translation_pivot = { 700,700 }, vec2 rotation_pivot = { 700,700 })
  {
    // Important to pass by value here as passing by reference would pollute the original
    for (Line l : path)
    {
      l.translate(translation_pivot);
      w.draw(l.rotate(angle, rotation_pivot));
    }

    sf::CircleShape p;
    p.setRadius(1.0f);
    p.setFillColor(sf::Color::Red);

    // Debugging
    for (vec2& _v : points) { p.setPosition({ (float)_v.x + (float)translation_pivot.x,(float)_v.y + (float)translation_pivot.y }); w.draw(p); }
  };

  // Translate to coordinates
  void translate(vec2 _v)
  {
    for (Line& l : path)
    {
      l.translate(_v);
    }
    for (vec2& p : points) { p.x += _v.x; p.y += _v.y; }
  }

  ~Path();
};







Path::Path()
{
}

Path::Path(std::initializer_list<vec2> _v)
{

  for (std::initializer_list<vec2>::iterator it = _v.begin(); it != _v.end(); it++)
  {

    // Bit terse, create new line between current point and either next point or beginning if enclosed
    Line l{ (*it), std::next(it) == _v.end() ? (*_v.begin()) : (*std::next(it)) };
    points.push_back(*it);
    path.push_back(l);
  }
}

Path::~Path()
{
}


#endif //PATH_H