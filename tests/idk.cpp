#include <iostream>
#include <SFML/Graphics.hpp>
#include "matrix.h"

#define PI 3.1415926535897932384626433


int main(int argc, char const* argv[])
{

  const double windowx = 800.0;
  const double windowy = 800.0;
  sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Matrix");

  sf::CircleShape p;
  p.setRadius(2.0f);
  p.setFillColor(sf::Color::Red);

  Matrix<1, 2> val = { {0,1} };
  //Matrix<2, 2> R = { {1 / sqrt(2),-1 / sqrt(2)},{1 / sqrt(2),1 / sqrt(2)} };

  double angle = PI / 2;


  //Matrix<2, 2> R = { {0,-1},{1,0} };

  Matrix<3, 3> m = Matrix<3, 3>::identityMatrix();

  std::cout << m;

  sf::Clock clock;
  clock.restart();
  while (window.isOpen())
  {
    // float dt = 0.f;
    sf::Event evt;
    while (window.pollEvent(evt))
    {
      if (evt.type == sf::Event::Closed)
      {
        window.close();
      }
    }
    //dt = clock.restart().asSeconds();
    window.clear();
    float sc = 150.f;


    p.setPosition(windowx / 2.0, windowy / 2.0);
    p.setFillColor(sf::Color::White);
    window.draw(p);

    p.setPosition(windowx / 2 + val[0][0] * sc, windowy / 2 + val.entries[0][1] * sc);

    p.setFillColor(sf::Color::Red);
    window.draw(p);


    Matrix<2, 2> CCW = Matrix<2, 2>::rotate2(angle);  // Counter-Clockwise
    Matrix<2, 2> CW = Matrix<2, 2>::rotate2cw(angle); // Clockwise

    Matrix<1, 2> ccwrotated = {};
    ccwrotated = val * CW;

    ccwrotated.entries.at(1);

    p.setFillColor(sf::Color::Blue);

    sf::Vector2 z = { windowx / 2.0 + ccwrotated.entries[0][0] * sc, windowy / 2.0 + ccwrotated.entries[0][1] * sc };
    p.setPosition({ (float)z.x, (float)z.y });
    p.setRadius(1.0);
    window.draw(p);

    Matrix<1, 2> cwrotated = {};
    cwrotated = val * CCW;
    p.setPosition(z.x + cwrotated.entries[0][0] * sc / 2.0, z.y + cwrotated.entries[0][1] * sc / 2.0);
    p.setRadius(2.0);
    p.setFillColor(sf::Color::Green);
    //window.draw(p);

    using mat1x2 = Matrix<1, 2>;
    mat1x2 sd = { {0,0} };

    angle = PI;


    Matrix<1, 2> outerccw = {};
    outerccw = val * CW;
    p.setPosition((z.x) + outerccw.entries[0][0] * sc / 2.0, (z.y) + outerccw.entries[0][1] * sc / 2.0);
    p.setRadius(2.0);
    p.setFillColor(sf::Color::Yellow);
    //window.draw(p);

    Matrix<1, 2> honestlyjustfuckingaroundatthispoint = {};
    honestlyjustfuckingaroundatthispoint = val * CCW;
    p.setPosition(((z.x) + outerccw.entries[0][0] * sc / 2.0) + honestlyjustfuckingaroundatthispoint.entries[0][0] * sc / 4.0, ((z.y) + outerccw.entries[0][1] * sc / 2.0) + honestlyjustfuckingaroundatthispoint.entries[0][1] * sc / 4.0);
    p.setRadius(1.0);
    p.setFillColor(sf::Color::Red);
    //window.draw(p);



    //angle += 0.001;
    //angle >= 360.0 ? angle = 0 : angle += 0.001;
    window.display();
  }
  std::cout << "notbroken";

  return 0;
}