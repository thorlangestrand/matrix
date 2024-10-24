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

  double scale = 100;

  Path _p = { {-scale,scale}, {scale,scale}, {-scale,-scale}, {scale,-scale}, {-scale,scale},{-scale,-scale}, {0 * scale,-2 * scale}, {scale,-scale}, {scale,scale} };
  _p.translate({ midx,midy });

  Path _p2 = { {-scale / 2,scale / 2}, {scale / 2,scale / 2}, {-scale / 2,-scale / 2}, {scale / 2,-scale / 2}, {-scale / 2,scale / 2},{-scale / 2,-scale / 2}, {0 * scale / 2,-2 * scale / 2}, {scale / 2,-scale / 2}, {scale / 2,scale / 2} };
  Path _p3 = { {-scale / 2,scale / 2}, {scale / 2,scale / 2}, {-scale / 2,-scale / 2}, {scale / 2,-scale / 2}, {-scale / 2,scale / 2},{-scale / 2,-scale / 2}, {0 * scale / 2,-2 * scale / 2}, {scale / 2,-scale / 2}, {scale / 2,scale / 2} };
  Path _p4 = { {-scale / 2,scale / 2}, {scale / 2,scale / 2}, {-scale / 2,-scale / 2}, {scale / 2,-scale / 2}, {-scale / 2,scale / 2},{-scale / 2,-scale / 2}, {0 * scale / 2,-2 * scale / 2}, {scale / 2,-scale / 2}, {scale / 2,scale / 2} };
  Path _p5 = { {-scale / 2,scale / 2}, {scale / 2,scale / 2}, {-scale / 2,-scale / 2}, {scale / 2,-scale / 2}, {-scale / 2,scale / 2},{-scale / 2,-scale / 2}, {0 * scale / 2,-2 * scale / 2}, {scale / 2,-scale / 2}, {scale / 2,scale / 2} };
  _p2.translate({ midx - 100,midy + 100 });
  _p3.translate({ midx + 100,midy + 100 });
  _p4.translate({ midx + 100,midy - 100 });
  _p5.translate({ midx - 100,midy - 100 });
  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) { if (evt.type == sf::Event::Closed) { window.close(); } }

    window.clear();
    _p.draw(window, angle, { midx,midy });
    _p2.draw(window, angle, { midx,midy });
    _p3.draw(window, angle, { midx,midy });
    _p4.draw(window, angle, { midx,midy });
    _p5.draw(window, angle, { midx,midy });
    window.display();
    angle -= 0.0001;
  }

  std::cout << "notbroken";

  return 0;
}