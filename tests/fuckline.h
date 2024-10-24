#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics/VertexArray.hpp>


// Forward declarations
template<typename T>
class vector2;
template<int R, int C, typename T >
class Matrix;

//using Point2D<double> = Point2D<double>;

class Line : public sf::VertexArray
{
private:
  Point2D<double> begin, end;
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

    Point2D<double> beginRotated = begin.rotatePointPivot2D(angle, pivot);
    Point2D<double> endRotated = end.rotatePointPivot2D(angle, pivot);

    Line ret(beginRotated, endRotated, s);
    return ret;
  }

  inline Line rotate(double angle, sf::Color s = sf::Color::Blue)
  {
    Point2D<double> beginRotated = begin.rotatePoint2D(angle);
    Point2D<double> endRotated = end.rotatePoint2D(angle);

    Line ret(beginRotated, endRotated, s);
    return ret;
  }
  Line(Point2D<double> _begin, Point2D<double> _end, sf::Color _lc);

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
Line::Line(Point2D<double> _begin, Point2D<double> _end, sf::Color _lc = sf::Color::Blue) : sf::VertexArray(sf::LinesStrip, 2)
{
  this->begin = _begin;
  this->end = _end;
  this->color = _lc;

  (*this)[0].position = { (float)_begin[0][0], (float)_begin[0][1] };
  (*this)[0].color = _lc;
  (*this)[1].position = { (float)_end[0][0], (float)_end[0][1] };
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