#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include <cassert>
#define PI 3.1415926535897932384626433


/* class line : public sf::Rect {

} */
#define mat3x3 Matrix<3,3>

int main(int argc, char const* argv[])
{

  assert(3 + 2 == 5);
  const double windowx = 1400.0;
  const double windowy = 1400.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  sf::CircleShape p1;
  p1.setRadius(1.0f);
  p1.setFillColor(sf::Color::Red);
  std::cout << Matrix<3, 3>::identityMatrix();
  double angle = 0;// PI / 2;

  /*   double sc = 150.0;
    double sc2 = 300.0; */
  double xshift = 100;
  double yshift = 100;
  p1.setPosition(midx + xshift, midy + yshift);

  using Point = Matrix<1, 2>;
  Point rotOutput;

  Point la = { {midx - 100, midy} };
  Point ra = { {midx + 100, midy} };

  std::vector<Point> li = { la,ra };

  mat3x3 z;
  std::cout << z;

  int amtPoints = 2;


  sf::CircleShape p;
  p.setRadius(1.0f);
  p.setFillColor(sf::Color::Red);
  p.setPosition(midx, midy);
  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) { if (evt.type == sf::Event::Closed) { window.close(); } }

    window.clear();
    window.draw(p1);

    // Translate back to origin {0,0}
/*     Point ls = { {la[0][0] - midx, la[0][1] - midy} };
    Point rs = { {ra[0][0] - midx, ra[0][1] - midy} };

    // Rotate around origin
    Point lv = ls * Matrix<2, 2>::rotate2cw(angle);
    Point rv = rs * Matrix<2, 2>::rotate2cw(angle);

    // Translate back to rotation point
    lv[0][0] += midx;
    lv[0][1] += midy;
    rv[0][0] += midx;
    rv[0][1] += midy; */

    Point lv = la.rotatePointPivot2D(angle, { midx,midy }, false);
    Point rv = ra.rotatePointPivot2D(angle, { midx,midy }, false);

    // Line that rotates around center
    sf::VertexArray line(sf::LinesStrip, amtPoints);
    for (int i = 0; i < amtPoints; i++)
    {
      line[i].position = { (float)li[i].rotatePointPivot2D(angle, { midx,midy },false)[0][0], (float)li[i].rotatePointPivot2D(angle, { midx,midy },false)[0][1] };
      line[i].color = sf::Color::Blue;
    }
    window.draw(line);

    // I want a line to fucking rotate around each point on the line rotating around the
    // center lmao

    // Propeller lmao
    Point prop1a = { {lv[0][0] , lv[0][1] - 50 } };
    Point prop1b = { {lv[0][0] , lv[0][1] + 50 } };


    Point prop1av = prop1a.rotatePointPivot2D(angle * 1.25, { lv[0][0], lv[0][1] }, true);
    Point prop1bv = prop1b.rotatePointPivot2D(angle * 1.25, { lv[0][0], lv[0][1] }, true);

    line[0].position = { prop1av[0][0],prop1av[0][1] };
    line[0].color = sf::Color::Red;
    line[1].position = { prop1bv[0][0],prop1bv[0][1] };
    line[1].color = sf::Color::Red;
    window.draw(line);

    Point prop2a = { {rv[0][0], rv[0][1] - 50} };
    Point prop2b = { {rv[0][0], rv[0][1] + 50} };

    Point prop2av = prop2a.rotatePointPivot2D(angle * 1.25, { rv[0][0], rv[0][1] }, true);
    Point prop2bv = prop2b.rotatePointPivot2D(angle * 1.25, { rv[0][0], rv[0][1] }, false);

    line[0].position = { prop2av[0][0],prop2av[0][1] };
    line[0].color = sf::Color::Green;
    line[1].position = { prop2bv[0][0],prop2bv[0][1] };
    line[1].color = sf::Color::Green;

    window.draw(line);
    // Neat, prints function where it was called, probably insanely useful if implemented properly
    //std::cout << __PRETTY_FUNCTION__ << ": "<< prop2a;

    // Add line class

    //Point prop1 = lv.rotatePointPivot2D(angle * 1.25, { lv[0][0],lv[0][1] });

    //Point prop2 = rv.rotatePointPivot2D(angle * 1.25, { lv[0][0],lv[0][1] }); 



    window.draw(p);
    window.display();
    angle += 0.001;
  }

  std::cout << "notbroken";

  return 0;
}