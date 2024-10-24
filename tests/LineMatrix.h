#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics/VertexArray.hpp>


// Forward declarations
template<typename T>
class vector2;
template<int R, int C, typename T >
class Matrix;

using Point = Matrix<1, 2>;

class Line : public sf::VertexArray
{
private:
  Point begin, end;
  sf::Color color = sf::Color::Blue;
public:

  /**
   * @brief
   * Rotate a line given by 2 points by angle around pivot
   * @param angle         Angle to be rotated by (Radians)
   * @param pivot         Pivot point (Lefthanded coordinate system)
   * @return Line         Drawable rotated line
   */
  inline Line rotate(double angle, vector2<double> pivot, sf::Color s = sf::Color::Blue)
  {
    Point beginRotated = begin.rotatePointPivot2D(angle, pivot);
    Point endRotated = end.rotatePointPivot2D(angle, pivot);

    Line ret(beginRotated, endRotated, s);
    return ret;
  }

  inline Line rotate(double angle, sf::Color s = sf::Color::Blue)
  {
    Point beginRotated = begin.rotatePoint2D(angle);
    Point endRotated = end.rotatePoint2D(angle);

    Line ret(beginRotated, endRotated, s);
    return ret;
  }
  Line(Point _begin, Point _end, sf::Color _lc);

  /*     Point prop1a = { {lv[0][0] , lv[0][1] - 50 } };
      Point prop1b = { {lv[0][0] , lv[0][1] + 50 } };


      Point prop1av = prop1a.rotatePointPivot2D(angle * 1.25, { lv[0][0], lv[0][1] }, true);
      Point prop1bv = prop1b.rotatePointPivot2D(angle * 1.25, { lv[0][0], lv[0][1] }, true);

      line[0].position = { prop1av[0][0],prop1av[0][1] };
      line[0].color = sf::Color::Red;
      line[1].position = { prop1bv[0][0],prop1bv[0][1] };
      line[1].color = sf::Color::Red; */







  Line();
  ~Line();
  Line(sf::PrimitiveType s, size_t size);
};

/**
 * @brief Construct a new Line:: Line object
 * 
 * @param _begin 
 * @param _end 
 * @param _lc 
 */
Line::Line(Point _begin, Point _end, sf::Color _lc = sf::Color::Blue) : sf::VertexArray(sf::LinesStrip, 2)
{
  this->begin = _begin;
  this->end = _end;
  this->color = _lc;

  (*this)[0].position = { _begin[0][0], _begin[0][1] };
  (*this)[0].color = _lc;
  (*this)[1].position = { _end[0][0], _end[0][1] };
  (*this)[1].color = _lc;






}


Line::Line() :sf::VertexArray(sf::LinesStrip, 2)
{}









Line::Line(sf::PrimitiveType s, size_t size) : sf::VertexArray(s, size)
{
}

Line::~Line()
{

}

Line newLine(Matrix<1, 2> p1, Matrix<1, 2> p2)
{
  return Line(sf::LinesStrip, 2);
}




#endif //LINE_H