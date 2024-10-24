#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"

#define PI 3.1415926535897932384626433


int main(int argc, char const* argv[])
{

  const double windowx = 800.0;
  const double windowy = 800.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  sf::CircleShape p;
  p.setRadius(2.0f);
  p.setFillColor(sf::Color::Red);

  Matrix<1, 2> val = { {0,1} };

  double angle = 0;

  double sc = 150.0;
  double sc2 = 300.0;

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

    //window.clear();


    p.setPosition(midx, midy); p.setFillColor(sf::Color::White); window.draw(p);

    rotOutput = val * Matrix<2, 2>::rotate2cw(angle);std::cout << rotOutput;
    p.setPosition(midx + rotOutput[0][0] * (sc + cos(angle) * sc2), midy + rotOutput[0][1] * (sc + sin(angle) * sc2)); p.setFillColor(sf::Color::Red); window.draw(p);

    angle += PI / 2;
    rotOutput = val * Matrix<2, 2>::rotate2cw(angle);std::cout << rotOutput;
    p.setPosition(midx + rotOutput[0][0] * (sc + cos(angle) * sc2), midy + rotOutput[0][1] * (sc + sin(angle) * sc2)); p.setFillColor(sf::Color::Yellow); window.draw(p);

    angle += PI / 2;
    rotOutput = val * Matrix<2, 2>::rotate2cw(angle);std::cout << rotOutput;
    p.setPosition(midx + rotOutput[0][0] * (sc + cos(angle) * sc2), midy + rotOutput[0][1] * (sc + sin(angle) * sc2)); p.setFillColor(sf::Color::Green); window.draw(p);

    angle += PI / 2;
    rotOutput = val * Matrix<2, 2>::rotate2cw(angle); std::cout << rotOutput;
    p.setPosition(midx + rotOutput[0][0] * (sc + cos(angle) * sc2), midy + rotOutput[0][1] * (sc + sin(angle) * sc2)); p.setFillColor(sf::Color::Blue); window.draw(p);
    angle += PI / 2;
    angle += 0.001;
    window.display();
  }
  std::cout << "notbroken";

  return 0;
}