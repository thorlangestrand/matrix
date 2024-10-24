#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include "Path.h"
#include "Line.h"

#define PI 3.1415926535897932384626433


int main(int argc, char const* argv[])
{
  const double windowx = 1400.0;
  const double windowy = 1400.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  double angle = 0;

  sf::CircleShape p; p.setRadius(1.0f); p.setFillColor(sf::Color::Red); p.setPosition(midx, midy);

  Path _p = { {-100,100}, {100,100}, {-100,-100}, {100,-100}, {-100,100},{-100,-100}, {0,-200}, {100,-100}, {100,100} };
  _p.translate({ midx,midy });

  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) { if (evt.type == sf::Event::Closed) { window.close(); } }

    window.clear();
    _p.draw(window, angle, { midx,midy });
    window.display();
    angle -= 0.0001;
  }

  std::cout << "notbroken";

  return 0;
}