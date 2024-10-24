#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"
#include "Line.h"
#define PI 3.1415926535897932384626433


#define mat3x3 Matrix<3,3>

using v2 = vector2<double>;

int main(int argc, char const* argv[])
{
  const double windowx = 1400.0;
  const double windowy = 1400.0;
  const double midx = windowx / 2.0;
  const double midy = windowy / 2.0;

  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  double angle = 0;

  sf::CircleShape p; p.setRadius(1.0f); p.setFillColor(sf::Color::Red); p.setPosition(midx, midy);

  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) { if (evt.type == sf::Event::Closed) { window.close(); } }

    window.clear();

    // Line that rotates around center
    Line l = { {midx - 100, midy}, {midx + 100,midy}, sf::Color::Red };
    Line baseRotated = l.rotate(0, { midx,midy }, false);
    // Line that rotates around line l's beginning
    Line lr = { {baseRotated.begin.x, baseRotated.begin.y - 50}, {baseRotated.begin.x, baseRotated.begin.y + 50} ,sf::Color::Cyan };
    Line lrRotated = lr.rotate(angle * 1.25, { baseRotated.begin.x,baseRotated.begin.y }, false);
    // Line that rotates around line l's end
    Line lp = { {baseRotated.end.x, baseRotated.end.y - 50}, {baseRotated.end.x,baseRotated.end.y + 50} ,sf::Color::Cyan };
    Line lpRotated = lp.rotate(angle * 1.25, { baseRotated.end.x, baseRotated.end.y });

    // Helikopter blades get blades too because why not

    Line ia = { {lrRotated.begin.x,lrRotated.begin.y - 25},{lrRotated.begin.x,lrRotated.begin.y + 25}, sf::Color::Magenta };
    Line ib = { {lrRotated.end.x,lrRotated.end.y - 25},{lrRotated.end.x,lrRotated.end.y + 25}, sf::Color::Magenta };
    Line ic = { {lpRotated.begin.x,lpRotated.begin.y - 25},{lpRotated.begin.x,lpRotated.begin.y + 25}, sf::Color::Magenta };
    Line id = { {lpRotated.end.x,lpRotated.end.y - 25},{lpRotated.end.x,lpRotated.end.y + 25}, sf::Color::Magenta };

    window.draw(ia.rotate(angle * 1.50, { lrRotated.begin.x,lrRotated.begin.y }, false));
    window.draw(ib.rotate(angle * 1.50, { lrRotated.end.x,lrRotated.end.y }, false));
    window.draw(ic.rotate(angle * 1.50, { lpRotated.begin.x,lrRotated.begin.y }, false));
    window.draw(id.rotate(angle * 1.50, { lpRotated.end.x,lrRotated.end.y }, false));
    window.draw(baseRotated); window.draw(lrRotated); window.draw(lpRotated);
    window.draw(p);
    window.display();
    angle += 0.001;
  }

  std::cout << "notbroken";

  return 0;
}