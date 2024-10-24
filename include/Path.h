#ifndef PATH_H
#define PATH_H

#include "Line.h"
#include "scopedtimer.h"

class Path
{
private:

public:
  vec2 centre = { 0,0 };
  std::vector<Line> path;


  /**
   * @brief
   * Draw path to screen
   *
   * @param w       Valid SFML render target
   */
  void draw(sf::RenderTarget& w) { for (Line& l : path) { w.draw(l); } }



  /**
   * @brief
   * Rotate around self based on angle and draw to screen
   * @param w
   * @param angle
   * @return cum
   */
  void draw(sf::RenderTarget& w, double angle)
  {
    for (Line& l : path) { Line _z = l.rotate(angle, centre); w.draw(_z); }
  }

  // Translate to coordinates
  void translate(vec2 _v)
  {
    for (Line& l : path) { l.translate(_v); }       // Translate line segments
    this->centre.x += _v.x; this->centre.y += _v.y; // Translate central point
  }

  /**
   * Get the beginning point of the line at given index
   * @param _i
   * @return vec2
   */
  vec2 getPoint(uint64_t _i) { return path[_i].begin; }

  Path();
  Path(std::initializer_list<vec2> _v);
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
    path.push_back(l);
  }
}

Path::~Path()
{
}


#endif //PATH_H