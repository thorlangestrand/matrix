#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"

#define PI 3.1415926535897932384626433

struct v2 {
  double x, y;
};

/* class line : public sf::Rect {

} */


int main(int argc, char const* argv[])
{


  const double windowx = 1400.0;
  const double windowy = 1400.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  sf::CircleShape p1;
  p1.setRadius(1.0f);
  p1.setFillColor(sf::Color::Red);




  v2 leftAnchor = { midx  , midy + 200 };
  v2 rightAnchor = { midx + 300, midy - 100 };




  Matrix<1, 2> val = { {1,1} };

  double angle = 2 / PI;

  double sc = 150.0;
  double sc2 = 300.0;

  double xshift = 100;
  double yshift = 100;

  p1.setPosition(midx + xshift, midy + yshift);
  using mat1x2 = Matrix<1, 2>;
  mat1x2 rotOutput;

  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt))
    {
      if (evt.type == sf::Event::Closed)
      {
        window.close();
      }
    }

    window.clear();
    window.draw(p1);


    double s = sin(angle);
    double c = cos(angle);

    leftAnchor.x -= xshift;
    leftAnchor.y -= yshift;

    double leftnewx = leftAnchor.x * c - leftAnchor.y * s;
    double leftnewy = leftAnchor.y * s - leftAnchor.x * c;

    leftAnchor.x = leftnewx + xshift;
    leftAnchor.y = leftnewy + yshift;

    rightAnchor.x -= xshift;
    rightAnchor.y -= yshift;

    double rightnewx = rightAnchor.x * c - rightAnchor.y * s;
    double rightnewy = rightAnchor.y * s - rightAnchor.x * c;

    rightAnchor.x = rightnewx + xshift;
    rightAnchor.y = rightnewy + yshift;





    sf::VertexArray line(sf::LinesStrip, 2);
    line[0].position = { leftAnchor.x, leftAnchor.y };
    line[0].color = sf::Color::Blue;
    line[1].position = { rightAnchor.x, rightAnchor.y };
    line[1].color = sf::Color::Blue;


    window.draw(line);
    std::cout << leftAnchor.x << " " << leftAnchor.y << "\n";
    std::cout << rightAnchor.x << " " << rightAnchor.y << "\n";
    window.display();
  }

  std::cout << "notbroken";

  return 0;
}