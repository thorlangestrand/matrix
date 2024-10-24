#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics/VertexArray.hpp>
#include <iostream>
#include "vec2.h"
#include "matrix.h"

class Line : public sf::VertexArray
{
private:
  sf::Color color = sf::Color::Blue;
public:
  vec2 begin, end;
  Line(vec2 _begin, vec2 _end, sf::Color _lc);
  Line(sf::PrimitiveType s, size_t size);
  /**
   * @brief
   *
   * Rotate a line given by 2 points by angle around pivot
   * and return new line with rotated coordinates
   *
   * @param angle         Angle to be rotated by (Radians)
   * @param pivot         Pivot point (Lefthanded coordinate system)
   * @return Line         Drawable rotated line
   */
  inline Line rotate(double angle, vector2<double> pivot, bool ccw = true)
  {
    vec2 beginRotated = Matrix<1, 2>::rotatePointPivot2D(begin, angle, pivot, ccw);

    vec2 endRotated = Matrix<1, 2>::rotatePointPivot2D(end, angle, pivot, ccw);

    Line ret(beginRotated, endRotated, this->color);
    return ret;
  }

  /**
   * @brief
   *
   * Rotate a line given by 2 points by angle around pivot
   * and mutate self state
   * 
   * 
   * The issue where it spergs out here comes from the fact
   * that in the previous method we're starting from 0 every time
   * and rotating based on current angle, whereas with this method
   * we're attempting to rotate the already previously rotated angle using the
   * same method
   *
   * @param angle       Angle to be rotated by (Radians)
   * @param pivot       Pivot point (Lefthanded coordinate system)
   * @return Line&      Reference to this object
   */
  inline Line& rotate_s(double angle, vec2 pivot, bool ccw = true)
  {
    vec2 beginRotated = Matrix<1, 2>::rotatePointPivot2D(begin, angle, pivot, ccw);

    vec2 endRotated = Matrix<1, 2>::rotatePointPivot2D(end, angle, pivot, ccw);

    this->begin = beginRotated; this->end = endRotated;



    this->updatePostion();
    return *this;

  }


  inline Line rotate(double angle, bool ccw = true)
  {
    vec2 beginRotated = Matrix<1, 2 >::rotatePoint2D(begin, angle, ccw);
    vec2 endRotated = Matrix<1, 2 >::rotatePoint2D(end, angle, ccw);

    Line ret(beginRotated, endRotated, this->color);
    return ret;
  }

  inline Line& _rotate(double angle, bool ccw = true)
  {
    vec2 beginRotated = Matrix<1, 2 >::rotatePoint2D(begin, angle, ccw);
    vec2 endRotated = Matrix<1, 2 >::rotatePoint2D(end, angle, ccw);
    this->begin = beginRotated; this->end = endRotated;
    return *this;
  }

  void operator = (std::initializer_list<std::initializer_list<double>> _v)
  {
    //std::cout << _v.size() << " " << _v.begin()->size() << " " << (_v.end() - 1)->size() << "\n";
    if (_v.size() != 2 || _v.begin()->size() != 2 || (_v.end() - 1)->size() != 2)
    {
      std::cout
        << "Error, param count mismatch in list initialization of line\nExpected 2x2, received"
        << _v.size() << "x" << ((_v.end() - 1)->size() != 2 ? (_v.end() - 1)->size() : _v.begin()->size())
        << "\nExiting...";
      exit(1);
    }

    // fuck it hardcode time i'm tired
    //{{3,2},{5,2}}

    auto it = _v.begin();
    auto z = it->begin();
    //std::cout << *z;
    this->begin.x = *z;
    z++;
    //std::cout << *z;
    this->begin.y = *z;
    it++;
    z = it->begin();
    //std::cout << *z;
    this->end.x = *z;
    z++;
    //std::cout << *z;
    this->end.y = *z;
    std::cout << "\n";
    std::cout << this->begin.x << " " << this->begin.y << "  " << this->end.x << " " << this->end.y << "\n";
  }


  void translate(vec2 _v)
  {
    this->begin.x += _v.x; this->end.x += _v.x;
    this->begin.y += _v.y; this->end.y += _v.y;
  }


  inline void updatePostion()
  {
    (*this)[0].position = { (float)this->begin.x, (float)this->begin.y };
    (*this)[1].position = { (float)this->end.x, (float)this->end.y };
  }

  Line();
  ~Line();
};

/**
 * @brief Construct a new Line:: Line object
 *
 * @param _begin
 * @param _end
 * @param _lc
 */
Line::Line(vec2 _begin, vec2 _end, sf::Color _lc = sf::Color::Blue) : sf::VertexArray(sf::LinesStrip, 2)
{
  this->begin = _begin;
  this->end = _end;
  this->color = _lc;

  (*this)[0].position = { (float)_begin.x, (float)_begin.y };
  (*this)[0].color = _lc;
  (*this)[1].position = { (float)_end.x, (float)_end.y };
  (*this)[1].color = _lc;
}


Line::Line() :sf::VertexArray(sf::LinesStrip, 2)
{}

Line::Line(sf::PrimitiveType s, size_t size) : sf::VertexArray(s, size)
{}

Line::~Line()
{}

Line newLine(Matrix<1, 2> p1, Matrix<1, 2> p2)
{
  return Line(sf::LinesStrip, 2);
}


#endif //LINE_H