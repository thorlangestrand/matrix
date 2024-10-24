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
  Path _p2 = { {-scale / 2,scale / 2}, {scale / 2,scale / 2}, {-scale / 2,-scale / 2}, {scale / 2,-scale / 2}, {-scale / 2,scale / 2},{-scale / 2,-scale / 2}, {0 * scale / 2,-2 * scale / 2}, {scale / 2,-scale / 2}, {scale / 2,scale / 2} };
  _p.translate({ midx,midy });
  while (window.isOpen())
  {
    sf::Event evt;
    while (window.pollEvent(evt)) {
      if (evt.type == sf::Event::Closed) { window.close(); }
      if (evt.type == sf::Event::KeyPressed)
      {
        switch (evt.key.code) {
        case sf::Keyboard::Left:
        case sf::Keyboard::A: {
          angle += 0.05;
          break;
        }
        case sf::Keyboard::Right:
        case sf::Keyboard::D: {
          angle -= 0.05;
          break;
        }
        case sf::Keyboard::Up:
        case sf::Keyboard::W: {
          // Do something cool
          // Make move forward with up key, we have current angle
          //std::cout << sin(angle) << " " << cos(angle) << std::endl;
          // Hmm that's tricky. Need to translate to self position which means self TRUE position which means pollution
          // Which means full backup
          // Public center, center of path where everything is based around
          // Translate point, calculate everything based on point position
          //_p.translate({ -cos(angle), -sin(angle) });

          _p.translate({ -sin(angle) * 10, -cos(angle) * 10 });
          break;
        }
        case sf::Keyboard::Down:
        case sf::Keyboard::S: {
          _p.translate({ sin(angle) * 10, cos(angle) * 10 });
          break;
        }
        case sf::Keyboard::Escape: {
          window.close();
          break;
        }
        default: {
          break;
        }

        }
      }
    }

    window.clear();
    _p.draw(window, angle);
    _p2.draw(window, angle, _p.centre + scale);
    _p2.draw(window, angle, _p.centre - scale);
    _p2.draw(window, angle, { _p.centre.x - scale, _p.centre.y + scale });
    _p2.draw(window, angle, { _p.centre.x + scale, _p.centre.y - scale });


    window.display();
    //angle -= 0.0001;
  }

  std::cout << "notbroken";

  return 0;
}